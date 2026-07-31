v1
- Show layer activity on right LED via colors
- turn off all LEDs when inactive
- Locks (Caps, Scroll, Num) on left side
- Layer 1 + Z - LED toggle


v2
- [done 2026-07-31] KC_CCCV - one key copy paste (mike1808)
  - on Fn+C: tap = paste (Ctrl+V), hold = copy (Ctrl+C)
- [done 2026-07-31] type heatmap (white)
  - custom effect (rgb_matrix_user.inc), last in the effect cycle:
    from Solid Color, one tap of Fn+Down wraps to it
- Layer keys (Fn & Numpad) light up when layer is selected
  - deferred; numpad layer may be replaced by an actual GMMK Numpad

Defaults: static red (solid color, hue 0) after any EEPROM reset.
Caps Lock still overrides everything to white; side LEDs follow the knob
color (Ctrl/Shift/Alt + knob = hue/sat/brightness).
