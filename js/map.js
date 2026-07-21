// Ported 1:1 from map/map.cub — same grid, colors and player start as the C game.
const CUB_MAP = {
  floorColor: [89, 151, 8],
  ceilingColor: [77, 143, 172],
  grid: [
    "        1111111111111111111111111",
    "        1000000000100000000000001",
    "        1011000001110000002000001",
    "        1001000000000000000000001",
    "111111111011000001110000000000001",
    "100000000011000001110111110111111",
    "11110111111111011100000010001",
    "1111011101111101 101010010001",
    "11000000110101011100000010001",
    "10002000000000000000000000201",
    "100000000000000011010100100011",
    "11000001110101011111011110N0011",
    "11110111 1110101 1011110100011",
    "11111111 1111111 111111111111",
  ],
};

// walkable tile chars, same rule as move.c: ft_strchr("0SWEN", tile)
const WALKABLE = new Set(["0", "S", "W", "E", "N"]);
// tiles a ray passes through without stopping, same rule as setup_hit: ft_strchr("02NSWE", tile)
const RAY_TRANSPARENT = new Set(["0", "2", "N", "S", "W", "E"]);

function charAt(grid, x, y) {
  const row = grid[x];
  if (row === undefined || y < 0 || y >= row.length) return " ";
  return row[y];
}

function isWalkable(grid, x, y) {
  return WALKABLE.has(charAt(grid, x, y));
}

function isRayTransparent(grid, x, y) {
  return RAY_TRANSPARENT.has(charAt(grid, x, y));
}

// x = row index, y = column index — matches the original cub->map[x][y] convention.
function buildMapState(source) {
  const grid = source.grid;
  const sprites = [];
  let player = null;

  for (let x = 0; x < grid.length; x++) {
    const row = grid[x];
    for (let y = 0; y < row.length; y++) {
      const c = row[y];
      if (c === "2") {
        sprites.push({ x: x + 0.5, y: y + 0.5, answered: false });
      } else if (c === "N" || c === "S" || c === "W" || c === "E") {
        player = playerFromChar(c, x, y);
      }
    }
  }

  return {
    grid,
    height: grid.length,
    floorColor: source.floorColor,
    ceilingColor: source.ceilingColor,
    sprites,
    player,
  };
}

function playerFromChar(c, x, y) {
  const dirs = {
    N: { xDir: -1, yDir: 0, xFlat: 0, yFlat: 0.66 },
    S: { xDir: 1, yDir: 0, xFlat: 0, yFlat: -0.66 },
    W: { xDir: 0, yDir: -1, xFlat: -0.66, yFlat: 0 },
    E: { xDir: 0, yDir: 1, xFlat: 0.66, yFlat: 0 },
  };
  const d = dirs[c];
  return {
    x: x + 0.5,
    y: y + 0.5,
    xDir: d.xDir,
    yDir: d.yDir,
    xFlat: d.xFlat,
    yFlat: d.yFlat,
  };
}
