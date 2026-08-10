# GMMK Numpad bring-up

The lost Numpad was found, and the keymap-source layout changed at the same
time: all keymaps now live in the **Katnick repo at `~/Katnick/keyb/`** and are
symlinked into the QMK tree (see the table in
[build_and_flash.md](build_and_flash.md)). The old
`keyboards/gmmk/pro/rev1/ansi/keymaps/jqs.old/` backup dir is untracked and can
be deleted once the symlinked setup has proven itself.

## Hardware notes

- `keyboards/gmmk/numpad` — WB32F3G71 MCU (not STM32), 31 per-key LEDs, one
  rotary encoder (push = normal matrix key), and an analog **slider** on an ADC
  pin that stock firmware exposes as a MIDI fader.
- Flashing uses `wb32-dfu-updater_cli` (brew), not dfu-util.

## Keymap design (`~/Katnick/keyb/gmmk_numpad/jqs/`)

- **Lighting**: same red-base + white typing heatmap as the Pro — the custom
  effect file is shared (copied) and is the power-on default. NumLock-off
  warning: top-left key (LED 0) glows white.
- **Encoder**: zoom dial — rotate = Ctrl+`-`/Ctrl+`=`, push = Ctrl+0 reset.
  Chosen to complement the Pro's volume knob rather than duplicate it.
- **Slider**: kept stock's MIDI fader contract (channel 2, CC 0x3E) so any
  host-side mapping tutorial for the stock board applies. Improved over stock:
  only transmits on actual movement (deadband 2) instead of spamming; stock's
  odd `0x7F +` offset (which overflows past MIDI's 0–127 range) replaced with a
  plain 0–127 value.
- **No VIA**: numpad remaps are rare; skipping VIA means keymap edits flash
  directly with no EEPROM-reset step.
- Fn layer mirrors the Pro's philosophy: hue/sat/val up on 7/8/9, down on
  4/5/6, effect controls on `/` `*` `-`, NumLock on Fn+0, bootloader on Fn+`.`.

## Lessons from first flash

- **First flash from Glorious CORE**: hold Enter + `+` while plugging in USB —
  bootmagic (hold NUM) only exists once QMK is on the board.
- **Encoder taps need pacing**: `tap_code16(C(KC_EQL))` from an encoder
  callback reached hosts as a bare `=` — the mod and key land too close
  together. Fix: `#define TAP_CODE_DELAY 10` + hold Ctrl as a real mod around a
  plain `tap_code()`. Applies to any future encoder that sends modified keys.
- Terminals strip Ctrl from punctuation (no control code for `=`), so the
  shell printing `=`/`-` is normal even when zoom works everywhere else.

## Verification

- `make gmmk/numpad:jqs` builds clean (42 KB bin).
- Pro keymap rebuilt identically through its new Katnick symlink.
- Confirmed on hardware: red/white heatmap, NumLock indicator, zoom encoder
  with Ctrl+0 reset push, MIDI slider.
