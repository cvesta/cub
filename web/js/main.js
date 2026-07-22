(function () {
  const appEl = document.getElementById("app");
  const screens = {
    start: document.getElementById("screen-start"),
    character: document.getElementById("screen-character"),
    game: document.getElementById("screen-game"),
    end: document.getElementById("screen-end"),
  };

  function showScreen(name) {
    Object.values(screens).forEach((s) => s.classList.remove("active"));
    screens[name].classList.add("active");
  }

  const canvas = document.getElementById("game-canvas");
  const hudScore = document.getElementById("hud-score");
  const hudTeamChip = document.getElementById("hud-team");
  const hudTeamLabel = document.getElementById("hud-team-label");

  const quizOverlay = document.getElementById("quiz-overlay");
  const quizController = createQuizController(
    quizOverlay,
    document.getElementById("quiz-question"),
    document.getElementById("quiz-options"),
    document.getElementById("quiz-result"),
    onDisputeResolved
  );

  const characterPicker = createCharacterPicker(
    document.querySelector(".team-cards"),
    document.getElementById("character-continue"),
    startGame
  );

  const controls = createControls(
    document.getElementById("stick-zone"),
    document.getElementById("stick-knob"),
    document.getElementById("look-zone")
  );

  const audio = createAudioKit();

  document.addEventListener("click", (e) => {
    const el = e.target.closest(".btn, .team-card, .quiz-option");
    if (!el) return;
    audio.unlock();
    if (el.classList.contains("quiz-option")) audio.pick();
    else audio.tap();
    if (navigator.vibrate) navigator.vibrate(el.classList.contains("quiz-option") ? 12 : 8);
  });

  let textures = null;
  let raycasterState = null;
  let usedDisputeIndexes = new Set();
  let spriteDisputeMap = new Map(); // sprite object -> dispute index
  let pendingSprite = null;
  let tally = { m: 0, f: 0 };
  let rafId = null;
  let team = null;
  let bobPhase = 0;

  document.getElementById("start-play").addEventListener("click", () => {
    showScreen("character");
  });

  document.getElementById("end-replay").addEventListener("click", () => {
    startGame(team);
  });

  document.getElementById("end-menu").addEventListener("click", () => {
    stopLoop();
    showScreen("start");
  });

  function startGame(pickedTeam) {
    team = pickedTeam;
    appEl.classList.remove("team-m", "team-f");
    appEl.classList.add(`team-${team}`);
    hudTeamChip.classList.remove("team-m", "team-f");
    hudTeamChip.classList.add(`team-${team}`);
    hudTeamLabel.textContent = TEAMS[team].label;

    const mapState = buildMapState(CUB_MAP);
    usedDisputeIndexes = new Set();
    spriteDisputeMap = new Map();
    tally = { m: 0, f: 0 };
    pendingSprite = null;

    if (!textures) textures = buildTextureSet();
    raycasterState = createRaycasterState(canvas, mapState, textures);
    resizeRaycaster(raycasterState);

    updateHud();
    showScreen("game");
    startLoop();
  }

  function updateHud() {
    if (!raycasterState) return;
    const total = raycasterState.mapState.sprites.length;
    const answered = total - raycasterState.mapState.sprites.filter((s) => !s.answered).length;
    hudScore.textContent = `${answered}/${total}`;
  }

  const SPRITE_TRIGGER_DIST = 1.15;

  function checkSpriteProximity() {
    if (quizController.isOpen() || pendingSprite) return;
    const p = raycasterState.player;
    for (const sprite of raycasterState.mapState.sprites) {
      if (sprite.answered) continue;
      const d = Math.hypot(sprite.x - p.x, sprite.y - p.y);
      if (d < SPRITE_TRIGGER_DIST) {
        pendingSprite = sprite;
        const { index, dispute } = pickDispute(usedDisputeIndexes);
        usedDisputeIndexes.add(index);
        audio.disputeFound();
        if (navigator.vibrate) navigator.vibrate([10, 40, 10]);
        quizController.open(dispute);
        break;
      }
    }
  }

  function onDisputeResolved(side) {
    tally[side] += 1;
    if (pendingSprite) pendingSprite.answered = true;
    pendingSprite = null;
    updateHud();

    const total = raycasterState.mapState.sprites.length;
    const remaining = raycasterState.mapState.sprites.filter((s) => !s.answered).length;
    if (remaining === 0) {
      setTimeout(() => finishGame(total), 300);
    }
  }

  function finishGame(total) {
    stopLoop();
    document.getElementById("end-score").textContent = `${total}/${total}`;
    const leader = tally.m === tally.f ? "Ничья" : tally.m > tally.f ? "Чаще побеждало Мужское" : "Чаще побеждало Женское";
    document.getElementById("end-label").textContent =
      `Споров решено: ${total}. ${leader} (${tally.m} : ${tally.f}).`;
    showScreen("end");
    audio.finish();
    if (navigator.vibrate) navigator.vibrate([15, 60, 15, 60, 30]);
    spawnConfetti();
  }

  const CONFETTI_COLORS = ["#c98a4b", "#3f7c8c", "#b85c76", "#eef1f5"];

  function spawnConfetti() {
    if (window.matchMedia && window.matchMedia("(prefers-reduced-motion: reduce)").matches) return;
    const endScreen = screens.end;
    for (let i = 0; i < 26; i++) {
      const piece = document.createElement("div");
      piece.className = "confetti-piece";
      piece.style.left = `${Math.random() * 100}%`;
      piece.style.background = CONFETTI_COLORS[i % CONFETTI_COLORS.length];
      const duration = 1.6 + Math.random() * 1.2;
      const delay = Math.random() * 0.4;
      piece.style.animationDuration = `${duration}s`;
      piece.style.animationDelay = `${delay}s`;
      endScreen.appendChild(piece);
      setTimeout(() => piece.remove(), (duration + delay) * 1000 + 100);
    }
  }

  function startLoop() {
    stopLoop();
    let last = performance.now();
    function tick(now) {
      const dt = Math.min(64, now - last);
      last = now;
      step(dt);
      rafId = requestAnimationFrame(tick);
    }
    rafId = requestAnimationFrame(tick);
  }

  function stopLoop() {
    if (rafId !== null) {
      cancelAnimationFrame(rafId);
      rafId = null;
    }
  }

  const BOB_SPEED = 0.011; // phase advance per ms while moving at full stick push
  const BOB_AMPLITUDE = 7; // px

  function step(dt) {
    let moving = false;
    if (!quizController.isOpen()) {
      const move = controls.getMoveVector();
      const look = controls.consumeLookDelta();
      rotatePlayer(raycasterState, look);
      updatePlayerMovement(raycasterState, move);
      checkSpriteProximity();
      const intensity = Math.min(1, Math.hypot(move.forward, move.strafe));
      moving = intensity > 0.05;
      if (moving) {
        const prevPhase = bobPhase;
        bobPhase += dt * BOB_SPEED * intensity;
        if (Math.floor(prevPhase / Math.PI) !== Math.floor(bobPhase / Math.PI)) {
          audio.footstep();
          if (navigator.vibrate) navigator.vibrate(4);
        }
      }
    }
    const bobTarget = moving ? Math.sin(bobPhase) * BOB_AMPLITUDE : 0;
    canvas.style.transform = `translateY(${bobTarget.toFixed(1)}px) scale(1.01)`;
    renderFrame(raycasterState);
  }

  window.addEventListener("resize", () => {
    if (raycasterState) resizeRaycaster(raycasterState);
  });

  if ("serviceWorker" in navigator) {
    window.addEventListener("load", () => {
      navigator.serviceWorker.register("service-worker.js").catch(() => {});
    });
  }
})();
