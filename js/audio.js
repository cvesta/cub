// Small synthesized SFX kit — no audio files to fetch/cache, works fully offline in the PWA.
function createAudioKit() {
  let ctx = null;

  function ensureContext() {
    if (!ctx) {
      const Ctx = window.AudioContext || window.webkitAudioContext;
      if (!Ctx) return null;
      ctx = new Ctx();
    }
    if (ctx.state === "suspended") ctx.resume().catch(() => {});
    return ctx;
  }

  function tone({ freq, duration = 0.12, type = "sine", gain = 0.16, glideTo = null, delay = 0 }) {
    const c = ensureContext();
    if (!c) return;
    const t0 = c.currentTime + delay;
    const osc = c.createOscillator();
    const amp = c.createGain();
    osc.type = type;
    osc.frequency.setValueAtTime(freq, t0);
    if (glideTo) osc.frequency.exponentialRampToValueAtTime(glideTo, t0 + duration);
    amp.gain.setValueAtTime(0, t0);
    amp.gain.linearRampToValueAtTime(gain, t0 + 0.012);
    amp.gain.exponentialRampToValueAtTime(0.0001, t0 + duration);
    osc.connect(amp).connect(c.destination);
    osc.start(t0);
    osc.stop(t0 + duration + 0.02);
  }

  return {
    unlock: ensureContext,
    tap() {
      tone({ freq: 340, duration: 0.05, type: "square", gain: 0.05 });
    },
    footstep() {
      tone({ freq: 90, duration: 0.06, type: "triangle", gain: 0.05, glideTo: 60 });
    },
    disputeFound() {
      tone({ freq: 520, duration: 0.14, type: "sine", gain: 0.14, glideTo: 700 });
      tone({ freq: 700, duration: 0.16, type: "sine", gain: 0.1, delay: 0.08 });
    },
    pick() {
      tone({ freq: 260, duration: 0.09, type: "square", gain: 0.09 });
    },
    finish() {
      [523, 659, 784, 1046].forEach((f, i) => tone({ freq: f, duration: 0.22, type: "sine", gain: 0.12, delay: i * 0.09 }));
    },
  };
}
