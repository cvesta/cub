const TEAMS = {
  m: { label: "Мужское", short: "М" },
  f: { label: "Женское", short: "Ж" },
};

function createCharacterPicker(cardsEl, continueBtn, onPick) {
  let selected = localStorage.getItem("cub-team");
  if (selected && !TEAMS[selected]) selected = null;

  const cards = Array.from(cardsEl.querySelectorAll(".team-card"));

  function refresh() {
    cards.forEach((c) => c.classList.toggle("selected", c.dataset.team === selected));
    continueBtn.disabled = !selected;
  }

  cards.forEach((card) => {
    card.addEventListener("click", () => {
      selected = card.dataset.team;
      localStorage.setItem("cub-team", selected);
      refresh();
    });
  });

  continueBtn.addEventListener("click", () => {
    if (selected) onPick(selected);
  });

  refresh();

  return {
    getSelected: () => selected,
  };
}
