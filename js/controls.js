// Touch input, analogous to t_keypress + move.c but continuous/analog instead of discrete keys.
function createControls(stickZoneEl, stickKnobEl, lookZoneEl) {
  const state = {
    move: { forward: 0, strafe: 0 },
    lookDelta: 0,
  };

  let stickPointerId = null;
  let stickCenter = { x: 0, y: 0 };
  let stickMaxRadius = 1;

  function stickReset() {
    stickPointerId = null;
    state.move.forward = 0;
    state.move.strafe = 0;
    stickKnobEl.style.transform = "translate(-50%, -50%)";
  }

  stickZoneEl.addEventListener("pointerdown", (e) => {
    if (stickPointerId !== null) return;
    stickPointerId = e.pointerId;
    stickZoneEl.setPointerCapture(e.pointerId);
    const rect = stickZoneEl.getBoundingClientRect();
    stickCenter = { x: rect.left + rect.width / 2, y: rect.top + rect.height / 2 };
    stickMaxRadius = rect.width / 2 - 20;
    updateStick(e.clientX, e.clientY);
  });

  stickZoneEl.addEventListener("pointermove", (e) => {
    if (e.pointerId !== stickPointerId) return;
    updateStick(e.clientX, e.clientY);
  });

  function endStick(e) {
    if (e.pointerId !== stickPointerId) return;
    stickReset();
  }
  stickZoneEl.addEventListener("pointerup", endStick);
  stickZoneEl.addEventListener("pointercancel", endStick);

  function updateStick(clientX, clientY) {
    let dx = clientX - stickCenter.x;
    let dy = clientY - stickCenter.y;
    const dist = Math.hypot(dx, dy);
    if (dist > stickMaxRadius) {
      dx = (dx / dist) * stickMaxRadius;
      dy = (dy / dist) * stickMaxRadius;
    }
    stickKnobEl.style.transform = `translate(${dx - 28}px, ${dy - 28}px)`;
    state.move.forward = clampUnit(-dy / stickMaxRadius);
    state.move.strafe = clampUnit(dx / stickMaxRadius);
  }

  let lookPointerId = null;
  let lastLookX = 0;

  lookZoneEl.addEventListener("pointerdown", (e) => {
    if (lookPointerId !== null) return;
    lookPointerId = e.pointerId;
    lookZoneEl.setPointerCapture(e.pointerId);
    lastLookX = e.clientX;
  });

  lookZoneEl.addEventListener("pointermove", (e) => {
    if (e.pointerId !== lookPointerId) return;
    const dx = e.clientX - lastLookX;
    lastLookX = e.clientX;
    state.lookDelta += dx * LOOK_SENSITIVITY;
  });

  function endLook(e) {
    if (e.pointerId !== lookPointerId) return;
    lookPointerId = null;
  }
  lookZoneEl.addEventListener("pointerup", endLook);
  lookZoneEl.addEventListener("pointercancel", endLook);

  return {
    getMoveVector() {
      return state.move;
    },
    consumeLookDelta() {
      const d = state.lookDelta;
      state.lookDelta = 0;
      return d;
    },
  };
}

function clampUnit(v) {
  return Math.max(-1, Math.min(1, v));
}
