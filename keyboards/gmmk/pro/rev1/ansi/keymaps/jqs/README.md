v1
- Show layer activity on right LED via colors
- turn off all LEDs when inactive
- Locks (Caps, Scroll, Num) on left side
- Layer 1 + Z - LED toggle


v2
- [done 2026-07-31] KC_CCCV - one key copy paste (mike1808)
  - on Fn+C: tap = paste (Ctrl+V), hold = copy (Ctrl+C)
- [done 2026-07-31] type heatmap (white)
  - custom effect (rgb_matrix_user.inc) and the power-on DEFAULT: all keys
    solid red, typing heats keys toward white, cooling back to red
  - it is last in the effect cycle; Fn+Up wraps to plain Solid Color (static
    red, no heat), Fn+Down comes back
- Layer keys (Fn & Numpad) light up when layer is selected
  - deferred; numpad layer may be replaced by an actual GMMK Numpad

Defaults after any EEPROM reset: red base (hue 0) + white typing heatmap.
Caps Lock still overrides everything to white; side LEDs follow the knob
color (Ctrl/Shift/Alt + knob = hue/sat/brightness).

NOTE (VIA gotcha): with VIA enabled the board runs the keymap stored in
EEPROM, not the compiled one. After changing keys in keymap.c, flash via
bootmagic so the EEPROM re-initializes: start `make ...:flash`, then unplug,
hold ESC, plug back in (resets EEPROM + enters bootloader in one step).
