// Procedural wall/sprite textures — the original .xpm files never shipped in this repo
// and wouldn't decode in a browser anyway, so each face gets a drawn brick pattern
// tinted by compass direction (keeps the same orientation cue the original textures gave).
const TEX_SIZE = 64;

function makeTextureCanvas(brick, mortar, size = TEX_SIZE) {
  const c = document.createElement("canvas");
  c.width = size;
  c.height = size;
  const ctx = c.getContext("2d");
  ctx.fillStyle = mortar;
  ctx.fillRect(0, 0, size, size);

  const rows = 8;
  const rowH = size / rows;
  ctx.fillStyle = brick;
  for (let r = 0; r < rows; r++) {
    const offset = r % 2 === 0 ? 0 : size / 4;
    const bricksPerRow = 4;
    const brickW = size / bricksPerRow;
    for (let b = -1; b < bricksPerRow + 1; b++) {
      const x = b * brickW + offset;
      ctx.fillRect(x + 2, r * rowH + 2, brickW - 4, rowH - 4);
    }
  }

  // subtle vertical light falloff so faces don't look completely flat
  const grad = ctx.createLinearGradient(0, 0, 0, size);
  grad.addColorStop(0, "rgba(255,255,255,0.08)");
  grad.addColorStop(1, "rgba(0,0,0,0.18)");
  ctx.fillStyle = grad;
  ctx.fillRect(0, 0, size, size);

  return c;
}

function canvasToTexture(canvas) {
  const ctx = canvas.getContext("2d");
  const img = ctx.getImageData(0, 0, canvas.width, canvas.height);
  return { width: canvas.width, height: canvas.height, data: img.data };
}

function makeSpriteTexture(ringColor) {
  const size = TEX_SIZE;
  const c = document.createElement("canvas");
  c.width = size;
  c.height = size;
  const ctx = c.getContext("2d");
  ctx.clearRect(0, 0, size, size);
  ctx.fillStyle = "rgba(0,0,0,0)";
  ctx.fillRect(0, 0, size, size);

  ctx.beginPath();
  ctx.arc(size / 2, size / 2, size * 0.42, 0, Math.PI * 2);
  ctx.fillStyle = ringColor;
  ctx.fill();

  ctx.fillStyle = "#0a0c10";
  ctx.font = `bold ${Math.round(size * 0.5)}px system-ui, sans-serif`;
  ctx.textAlign = "center";
  ctx.textBaseline = "middle";
  ctx.fillText("?", size / 2, size / 2 + size * 0.03);

  return canvasToTexture(c);
}

function buildTextureSet() {
  return {
    north: canvasToTexture(makeTextureCanvas("#3f7c8c", "#22424b")),
    south: canvasToTexture(makeTextureCanvas("#c98a4b", "#5c3d20")),
    east: canvasToTexture(makeTextureCanvas("#6b7280", "#33363c")),
    west: canvasToTexture(makeTextureCanvas("#b85c76", "#4c2732")),
    sprite: makeSpriteTexture("#c1493f"),
  };
}
