// Original, fictional household disputes in the spirit of a "who's right" talk show —
// no real people, hosts or episodes. Picking a side is just an opinion, there's no
// "correct" answer — the game only tracks how many disputes you weighed in on.
const DISPUTES = [
  {
    question: "Кто готовил — тот моет посуду, или моет тот, кто ел?",
    options: [
      { text: "Он: «Готовил — уже внёс свой вклад, мыть логично второму»", side: "m" },
      { text: "Она: «Готовил — значит доводит дело до конца сам»", side: "f" },
    ],
    reaction: "Спор с историей длиною в отношения.",
  },
  {
    question: "Термостат зимой: 19°C или 23°C?",
    options: [
      { text: "Он: «19 — свитер решает всё»", side: "m" },
      { text: "Она: «23 — дома должно быть как дома»", side: "f" },
    ],
    reaction: "Компромисс где-то около пледа.",
  },
  {
    question: "Кто выгуливает собаку в дождь?",
    options: [
      { text: "Он: «У кого график свободнее, тот и идёт»", side: "m" },
      { text: "Она: «Заводили вместе — значит, по очереди без исключений»", side: "f" },
    ],
    reaction: "Собака, кажется, не против остаться дома.",
  },
  {
    question: "Пульт от телевизора вечером — у кого?",
    options: [
      { text: "Он: «Кто первый лёг на диван, тот и выбирает»", side: "m" },
      { text: "Она: «Меняемся через день — иначе нечестно»", side: "f" },
    ],
    reaction: "Стриминг явно решил бы этот спор быстрее.",
  },
  {
    question: "Телефон за столом во время ужина — можно?",
    options: [
      { text: "Он: «Можно, если это по работе»", side: "m" },
      { text: "Она: «Стол — время без экранов, работа подождёт»", side: "f" },
    ],
    reaction: "Один короткий ужин без звонка ещё никого не разорил.",
  },
  {
    question: "Отпуск в этом году: горы или море?",
    options: [
      { text: "Он: «Горы — тишина и не сгоришь»", side: "m" },
      { text: "Она: «Море — потому что отпуск должен быть отпуском»", side: "f" },
    ],
    reaction: "В следующий раз — озеро, и все довольны.",
  },
  {
    question: "Навигатор говорит одно, память — другое. Кому верить?",
    options: [
      { text: "Он: «Навигатору, он не обижается, если не прав»", side: "m" },
      { text: "Она: «Памяти — мы тут уже ездили, я помню поворот»", side: "f" },
    ],
    reaction: "Опоздали оба, но с разной уверенностью в голосе.",
  },
  {
    question: "Будильник на выходных: во сколько?",
    options: [
      { text: "Он: «Пока не проснёмся сами — это и есть выходной»", side: "m" },
      { text: "Она: «В десять, иначе весь день насмарку»", side: "f" },
    ],
    reaction: "Компромисс нашли где-то у одиннадцати.",
  },
];

function createQuizController(overlayEl, questionEl, optionsEl, resultEl, onResolved) {
  let current = null;
  let locked = false;

  function open(dispute) {
    current = dispute;
    locked = false;
    questionEl.textContent = dispute.question;
    resultEl.textContent = "";
    optionsEl.innerHTML = "";

    dispute.options.forEach((opt) => {
      const btn = document.createElement("button");
      btn.className = "quiz-option";
      btn.dataset.side = opt.side;
      btn.innerHTML = `<span class="side">${TEAMS[opt.side].short}</span><span>${opt.text}</span>`;
      btn.addEventListener("click", () => pick(opt, btn));
      optionsEl.appendChild(btn);
    });

    overlayEl.classList.add("active");
  }

  function pick(opt, btnEl) {
    if (locked) return;
    locked = true;
    Array.from(optionsEl.children).forEach((b) => (b.style.opacity = b === btnEl ? "1" : "0.45"));
    resultEl.textContent = current.reaction;
    const resolvedSide = opt.side;
    setTimeout(() => {
      overlayEl.classList.remove("active");
      const dispute = current;
      current = null;
      onResolved(resolvedSide, dispute);
    }, 1100);
  }

  return {
    open,
    isOpen: () => current !== null,
  };
}

function pickDispute(usedIndexes) {
  const available = DISPUTES.map((_, i) => i).filter((i) => !usedIndexes.has(i));
  const pool = available.length ? available : DISPUTES.map((_, i) => i);
  const idx = pool[Math.floor(Math.random() * pool.length)];
  return { index: idx, dispute: DISPUTES[idx] };
}
