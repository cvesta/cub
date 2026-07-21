// DDA raycasting engine ported from raycast.c / monitor_raycast.c / setup.c / move.c / motion.c.
// Same grid convention as the C game: x = row, y = column, map[x][y].

const MOVE_SPEED = 0.06; // per-frame tile fraction at full joystick push, same order of magnitude as cub->ray.mvspeed
const LOOK_SENSITIVITY = 0.0045; // radians per swipe pixel

function createRaycasterState(canvas, mapState, textures) {
  const offscreen = document.createElement("canvas");
  return {
    canvas,
    ctx: canvas.getContext("2d"),
    offscreen,
    octx: offscreen.getContext("2d"),
    mapState,
    textures,
    width: 0,
    height: 0,
    imageData: null,
    buf: null,
    zbuffer: null,
    player: { ...mapState.player },
  };
}

function resizeRaycaster(state) {
  const canvas = state.canvas;
  const dpr = Math.min(window.devicePixelRatio || 1, 2);
  const cssW = canvas.clientWidth || window.innerWidth;
  const cssH = canvas.clientHeight || window.innerHeight;
  canvas.width = Math.round(cssW * dpr);
  canvas.height = Math.round(cssH * dpr);

  const internalW = Math.max(160, Math.min(420, Math.round(cssW * 0.55)));
  const internalH = Math.max(120, Math.round(internalW * (cssH / cssW)));

  state.width = internalW;
  state.height = internalH;
  state.offscreen.width = internalW;
  state.offscreen.height = internalH;
  state.imageData = state.octx.createImageData(internalW, internalH);
  state.buf = state.imageData.data;
  state.zbuffer = new Float64Array(internalW);
}

function setPixel(buf, width, x, y, r, g, b) {
  const i = (y * width + x) * 4;
  buf[i] = r;
  buf[i + 1] = g;
  buf[i + 2] = b;
  buf[i + 3] = 255;
}

function renderFrame(state) {
  const { buf, width, height, mapState, textures, player, zbuffer } = state;
  const grid = mapState.grid;
  const [fr, fg, fb] = mapState.floorColor;
  const [cr, cg, cb] = mapState.ceilingColor;

  for (let x = 0; x < width; x++) {
    const xCam = (2 * x) / width - 1;
    let xRayDir = player.xDir + player.xFlat * xCam;
    let yRayDir = player.yDir + player.yFlat * xCam;
    if (xRayDir === 0) xRayDir = 1e-9;
    if (yRayDir === 0) yRayDir = 1e-9;

    let xMap = Math.floor(player.x);
    let yMap = Math.floor(player.y);

    const xDeltaD = Math.sqrt(1 + (yRayDir * yRayDir) / (xRayDir * xRayDir));
    const yDeltaD = Math.sqrt(1 + (xRayDir * xRayDir) / (yRayDir * yRayDir));

    let xStep, yStep, xSide, ySide;
    if (xRayDir < 0) {
      xStep = -1;
      xSide = (player.x - xMap) * xDeltaD;
    } else {
      xStep = 1;
      xSide = (xMap + 1.0 - player.x) * xDeltaD;
    }
    if (yRayDir < 0) {
      yStep = -1;
      ySide = (player.y - yMap) * yDeltaD;
    } else {
      yStep = 1;
      ySide = (yMap + 1.0 - player.y) * yDeltaD;
    }

    let hit = 0;
    let side = 0;
    let guard = 0;
    while (hit === 0 && guard++ < 256) {
      if (xSide < ySide) {
        xSide += xDeltaD;
        xMap += xStep;
        side = xStep === 1 ? 0 : 1;
      } else {
        ySide += yDeltaD;
        yMap += yStep;
        side = yStep === 1 ? 2 : 3;
      }
      if (!isRayTransparent(grid, xMap, yMap)) hit = 1;
    }

    let lenRay;
    if (side === 0 || side === 1) {
      lenRay = (xMap - player.x + (1 - xStep) / 2) / xRayDir;
    } else {
      lenRay = (yMap - player.y + (1 - yStep) / 2) / yRayDir;
    }
    lenRay = Math.max(lenRay, 1e-4);
    zbuffer[x] = lenRay;

    const heightLine = Math.floor(height / lenRay);
    let drawStart = Math.floor(-heightLine / 2 + height / 2);
    let drawEnd = Math.floor(heightLine / 2 + height / 2);
    if (drawStart < 0) drawStart = 0;
    if (drawEnd > height) drawEnd = height;

    let xWall;
    if (side === 0 || side === 1) {
      xWall = player.y + lenRay * yRayDir;
    } else {
      xWall = player.x + lenRay * xRayDir;
    }
    xWall -= Math.floor(xWall);

    const tex =
      side === 0 ? textures.south : side === 1 ? textures.north : side === 2 ? textures.east : textures.west;

    let xTex = Math.floor(xWall * tex.width);
    if (side === 0 && xRayDir > 0) xTex = tex.width - xTex - 1;
    if (side === 1 && yRayDir < 0) xTex = tex.width - xTex - 1;
    if (side === 2 && yRayDir < 0) xTex = tex.width - xTex - 1;
    if (side === 3 && yRayDir > 0) xTex = tex.width - xTex - 1;

    const step = tex.height / heightLine;
    let posTex = (drawStart - height / 2 + heightLine / 2) * step;

    for (let y = 0; y < drawStart; y++) setPixel(buf, width, x, y, cr, cg, cb);
    for (let y = drawEnd; y < height; y++) setPixel(buf, width, x, y, fr, fg, fb);

    for (let y = drawStart; y < drawEnd; y++) {
      const yTex = Math.floor(posTex) % tex.height;
      posTex += step;
      const ti = (((yTex + tex.height) % tex.height) * tex.width + xTex) * 4;
      setPixel(buf, width, x, y, tex.data[ti], tex.data[ti + 1], tex.data[ti + 2]);
    }
  }

  drawSprites(state);

  state.octx.putImageData(state.imageData, 0, 0);
  state.ctx.imageSmoothingEnabled = true;
  state.ctx.drawImage(state.offscreen, 0, 0, state.canvas.width, state.canvas.height);
}

function drawSprites(state) {
  const { buf, width, height, mapState, textures, player, zbuffer } = state;
  const tex = textures.sprite;
  const active = mapState.sprites.filter((s) => !s.answered);
  active.sort((a, b) => {
    const da = (a.x - player.x) ** 2 + (a.y - player.y) ** 2;
    const db = (b.x - player.x) ** 2 + (b.y - player.y) ** 2;
    return db - da;
  });

  const det = player.xFlat * player.yDir - player.xDir * player.yFlat;
  if (Math.abs(det) < 1e-9) return;
  const invDet = 1 / det;

  for (const sprite of active) {
    const dx = sprite.x - player.x;
    const dy = sprite.y - player.y;
    const transformX = invDet * (player.yDir * dx - player.xDir * dy);
    const transformY = invDet * (-player.yFlat * dx + player.xFlat * dy);
    if (transformY <= 0.05) continue;

    const screenX = Math.floor((width / 2) * (1 + transformX / transformY));
    const spriteSize = Math.min(2000, Math.abs(Math.floor(height / transformY)));

    const drawStartY = Math.max(0, Math.floor(-spriteSize / 2 + height / 2));
    const drawEndY = Math.min(height, Math.floor(spriteSize / 2 + height / 2));
    const drawStartX = Math.max(0, Math.floor(-spriteSize / 2 + screenX));
    const drawEndX = Math.min(width, Math.floor(spriteSize / 2 + screenX));

    for (let sx = drawStartX; sx < drawEndX; sx++) {
      if (transformY >= zbuffer[sx]) continue;
      const texX = Math.floor(((sx - (-spriteSize / 2 + screenX)) * tex.width) / spriteSize);
      for (let sy = drawStartY; sy < drawEndY; sy++) {
        const texY = Math.floor(((sy - drawStartY) * tex.height) / spriteSize);
        const ti = (texY * tex.width + texX) * 4;
        const alpha = tex.data[ti + 3];
        if (alpha < 64) continue;
        setPixel(buf, width, sx, sy, tex.data[ti], tex.data[ti + 1], tex.data[ti + 2]);
      }
    }
  }
}

// ---- movement, ported from move.c / motion.c ----

function tryMoveAxis(mapState, player, axis, delta) {
  if (axis === "x") {
    const nx = player.x + delta;
    if (isWalkable(mapState.grid, Math.floor(nx), Math.floor(player.y))) player.x = nx;
  } else {
    const ny = player.y + delta;
    if (isWalkable(mapState.grid, Math.floor(player.x), Math.floor(ny))) player.y = ny;
  }
}

// moveVec: {forward, strafe} each roughly in [-1, 1] from the joystick
function updatePlayerMovement(state, moveVec) {
  const { mapState, player } = state;
  const speed = MOVE_SPEED;

  if (moveVec.forward !== 0) {
    const amt = speed * moveVec.forward;
    tryMoveAxis(mapState, player, "x", player.xDir * amt);
    tryMoveAxis(mapState, player, "y", player.yDir * amt);
  }
  if (moveVec.strafe !== 0) {
    const amt = speed * moveVec.strafe;
    tryMoveAxis(mapState, player, "y", -player.xDir * amt);
    tryMoveAxis(mapState, player, "x", player.yDir * amt);
  }
}

function rotatePlayer(state, angle) {
  if (!angle) return;
  const p = state.player;
  const oldXDir = p.xDir;
  p.xDir = p.xDir * Math.cos(angle) - p.yDir * Math.sin(angle);
  p.yDir = oldXDir * Math.sin(angle) + p.yDir * Math.cos(angle);
  const oldXFlat = p.xFlat;
  p.xFlat = p.xFlat * Math.cos(angle) - p.yFlat * Math.sin(angle);
  p.yFlat = oldXFlat * Math.sin(angle) + p.yFlat * Math.cos(angle);
}
