# v2 roadmap

The three features from the keymap README's "v2" list, with concrete steps on
modern (2026) QMK. All work happens in `keyboards/gmmk/pro/rev1/ansi/keymaps/jqs/`.

---

## 1. `KC_CCCV` — one-key copy/paste (hold = copy, tap = paste)

QMK core has no built-in CCCV; it's a small custom keycode (~20 lines in keymap.c).

1. Declare the keycode:
   ```c
   enum custom_keycodes { KC_CCCV = SAFE_RANGE };
   static uint16_t cccv_timer;
   ```
2. Handle it:
   ```c
   bool process_record_user(uint16_t keycode, keyrecord_t *record) {
       switch (keycode) {
           case KC_CCCV:
               if (record->event.pressed) {
                   cccv_timer = timer_read();
               } else {
                   if (timer_elapsed(cccv_timer) > TAPPING_TERM) {
                       tap_code16(LCTL(KC_C));   // held: copy
                   } else {
                       tap_code16(LCTL(KC_V));   // tapped: paste
                   }
               }
               return false;
       }
       return true;
   }
   ```
3. Put it on the map. Good candidates: layer-1 `C` position, or the knob press
   (layer-0 `KC_MUTE`) if volume-mute isn't missed.
4. Note: in VIA the key shows up as `CUSTOM(0)`/`USER00`, not by name.

Effort: small. No config changes.

---

## 2. Typing heatmap (white)

Phase 1 — stock heatmap (minutes):
- Modern QMK requires effects to be enabled explicitly. In `config.h` add:
  `#define ENABLE_RGB_MATRIX_TYPING_HEATMAP`
  (`RGB_MATRIX_FRAMEBUFFER_EFFECTS` and the decrease-delay tuning are already set.)
- Select it with the knob (`RM_NEXT` on layer 1) or force it in code with
  `rgb_matrix_mode(RGB_MATRIX_TYPING_HEATMAP)`.

Phase 2 — white variant (the actual v2 item):
The stock effect colors by heat-mapped hue, so it can't be made white via config.
Write a custom effect instead:
1. `rules.mk`: add `RGB_MATRIX_CUSTOM_USER = yes`
2. Create `rgb_matrix_user.inc` next to keymap.c. Register an effect
   (`RGB_MATRIX_EFFECT(WHITE_HEATMAP)`) modeled on
   `quantum/rgb_matrix/animations/typing_heatmap_anim.h`, but map heat to
   brightness with r = g = b (white) instead of shifting hue.
   The per-key heat values live in `g_rgb_frame_buffer[row][col]`.
3. Careful: the effect iterates matrix rows/cols; reuse the stock effect's
   led-index lookup so the side LEDs stay under the existing indicator logic.

Effort: phase 1 trivial; phase 2 an evening.

---

## 3. Layer keys light up when layer is active

Add to the existing `rgb_matrix_indicators_advanced_user()` (LED indices are in
the comment map in keymap.c — `FN` is LED 55):

```c
switch (get_highest_layer(layer_state)) {
    case 1:
        rgb_matrix_set_color(55, RGB_WHITE);   // FN key
        break;
    case 2:
        rgb_matrix_set_color(55, 255, 0, 0);   // numpad layer indicator
        break;
}
```

The "Numpad" half of this item needs the numpad layer to exist first — layer 2 is
currently empty scaffolding:
1. Fill layer 2 as a right-hand numpad (`7 8 9` on `U I O`, `4 5 6` on `J K L`,
   `1 2 3` on `M , .`, `0` on space, `KC_PDOT`/`KC_PENT` nearby).
2. Add a toggle: `TG(2)` somewhere reachable, e.g. layer-1 `N` or `KC_NUM` position.
3. Optionally light the whole numpad cluster (not just the FN key) while layer 2
   is active, and use the already-declared `numCaps[]` side LEDs as the Num
   indicator the array was named for.

Effort: small; purely keymap.c.
