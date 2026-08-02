# jqs firmware vs. stock GMMK Pro

What this firmware (`keyboards/gmmk/pro/rev1/ansi/keymaps/jqs/`) does differently
from stock. "Stock" here = QMK's default GMMK Pro keymap; the factory board
actually ships Glorious CORE firmware, which none of this resembles.

## Base layer — 2 key changes

| Position | Stock | jqs |
|---|---|---|
| Top-right (above knob) | PrtScr | **Del** |
| Right of Backspace | Del | **Home** |

Everything else on the base layer is standard ANSI, same as stock.

## Fn layer (hold Fn)

| Keys | Function |
|---|---|
| Fn+Esc | RGB effect on/off (stock: nothing) |
| Fn+F1–F4 | My Computer, Web Home, Calculator, Media Select (stock: same, on F1–F4) |
| Fn+F9–F12 | Prev / Next / Play / Stop (stock: these live on F5–F8) |
| Fn+Del | Debug toggle (stock: nothing) |
| Fn+`\` | Bootloader (same as stock) |
| Fn+Q / Fn+A | Side-LED base hue up / down |
| Fn+W / Fn+S | Saturation up / down |
| Fn+E / Fn+D | Brightness up / down (stock scatters RGB keys elsewhere) |
| **Fn+C** | **KC_CCCV — tap: paste, hold: copy** (custom keycode) |
| Fn+Space | NKRO toggle (stock: Fn+N) |
| Fn+Up / Fn+Down | Next / previous RGB effect |
| Fn+Left / Fn+Right | Effect speed down / up |

## The knob (stock: volume only, plus press = mute)

| While holding... | Rotation does |
|---|---|
| nothing | Volume (same as stock) |
| Ctrl | Side-LED hue |
| Shift | Side-LED saturation |
| Alt | Side-LED brightness |
| **Fn** | **Super Alt-Tab** — cycles windows, reverse = counter-clockwise; stop ~1 s to select |

Press is still mute.

## Lighting (stock: rainbow wave, keys + sides all one system)

- **Default effect**: custom "white heatmap over solid" — all keys solid red;
  typing heats keys toward white with neighbor spread, cooling back to red.
  (Implemented as a custom RGB Matrix effect in `rgb_matrix_user.inc`.)
- **Fn+Up** wraps from it to plain Solid Color (static red, no heat).
- **Caps Lock on**: entire board overrides to white.
- **Side LED strips**: decoupled from the key effect — they always show their
  own color, tuned live with the knob combos above.
- **Caps Word active**: Caps key + two upper-left side LEDs glow white.
- RGB idles off after 20 minutes and sleeps when the host suspends.

## Typing features (stock: none of these)

- **Caps Word**: press both Shifts together → capitalizes until the word ends
  (digits and `_` don't break it; 5 s idle timeout).
- **KC_CCCV** on Fn+C (see above).
- **NKRO on by default** (stock ships 6KRO with a toggle).
- **VIA support** compiled in (stock default keymap has none) — note the
  EEPROM gotcha in [build_and_flash.md](build_and_flash.md): key changes
  need a bootmagic-reset flash.
