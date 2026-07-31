// White-over-solid typing heatmap: every key shows the configured matrix color
// (default: red) and heat desaturates it toward white at the same brightness,
// fading back as the key cools. Uses the stock TYPING_HEATMAP's framebuffer,
// spread, and decay; heat is fed from process_record_user in keymap.c — core
// only feeds heat while the stock effect's mode is active.
RGB_MATRIX_EFFECT(WHITE_HEATMAP)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static uint16_t white_heatmap_decrease_timer;
static bool     white_heatmap_decrease;

static bool WHITE_HEATMAP(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    if (params->init) {
        rgb_matrix_set_color_all(0, 0, 0);
        memset(g_rgb_frame_buffer, 0, sizeof g_rgb_frame_buffer);
    }

    // Only re-evaluate the decay timer on the first iteration of a frame
    // (frames can span several iterations under RGB_MATRIX_LED_PROCESS_LIMIT).
    if (params->iter == 0) {
        white_heatmap_decrease = timer_elapsed(white_heatmap_decrease_timer) >= RGB_MATRIX_TYPING_HEATMAP_DECREASE_DELAY_MS;
        if (white_heatmap_decrease) {
            white_heatmap_decrease_timer = timer_read();
        }
    }

    uint8_t count = 0;
    for (uint8_t row = 0; row < MATRIX_ROWS && count < RGB_MATRIX_LED_PROCESS_LIMIT; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS && RGB_MATRIX_LED_PROCESS_LIMIT; col++) {
            if (g_led_config.matrix_co[row][col] >= led_min && g_led_config.matrix_co[row][col] < led_max) {
                count++;
                uint8_t val = g_rgb_frame_buffer[row][col];
                if (!HAS_ANY_FLAGS(g_led_config.flags[g_led_config.matrix_co[row][col]], params->flags)) continue;

                uint8_t whiteness = (qadd8(170, val) - 170) * 3; // heat curve: val 0..85+ -> 0..255
                hsv_t   hsv = {rgb_matrix_config.hsv.h, scale8(rgb_matrix_config.hsv.s, 255 - whiteness), rgb_matrix_config.hsv.v};
                rgb_t rgb = rgb_matrix_hsv_to_rgb(hsv);
                rgb_matrix_set_color(g_led_config.matrix_co[row][col], rgb.r, rgb.g, rgb.b);

                if (white_heatmap_decrease) {
                    g_rgb_frame_buffer[row][col] = qsub8(val, 1);
                }
            }
        }
    }

    return rgb_matrix_check_finished_leds(led_max);
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
