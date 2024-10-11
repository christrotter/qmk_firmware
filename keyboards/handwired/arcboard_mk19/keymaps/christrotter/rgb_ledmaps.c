// Copyright 2021 Mikael Manukyan <arm.localhost@gmail.com>
// Copyright 2023 Chris Trotter (@christrotter)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "rgb_ledmaps.h"
#include "arcboard_mk19.h"

#if defined(POINTING_DEVICE_ENABLE) && defined(DRAGSCROLL_ENABLE)
    #include "keymap.h"
#endif

bool process_record_user_rgb_matrix(uint16_t keycode, keyrecord_t *record) { return true; }

void set_rgb_ledmap(uint16_t first_led, uint16_t last_led, int val, int layer) {
    const ledmap *l = &(ledmaps[layer]);
    for (int i = first_led; i <= last_led; i++) {
        // RGB_TOT_IND_L is 'how many right indicator leds between left and right key ranges, in the context of the led-flag section of g_led_config'
        // cuz, ledmaps doesn't think there are any indicator leds, it believes you only have l.key-range + r.key-range = total addressable leds
        if (!(is_keyboard_left())) {
            i = i - RGB_TOT_IND_L;
        }
        HSV hsv = {
            .h = (*l)[i][0],
            .s = (*l)[i][1],
            .v = val,
        };
        if (!(is_keyboard_left())) {
            i = i + RGB_TOT_IND_L;
        } // revert i to fit the 'in reality' led sequence
        if (hsv.h || hsv.s) {
            RGB rgb = hsv_to_rgb(hsv);
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        }
    }
}

// set_rgb_range(RGB_FAL1_MIN, RGB_FAL1_MAX, FAL1_L0);
void set_rgb_range(uint16_t first_led, uint16_t last_led, int hue, int sat, int val, int val_override) {
    if (val_override) {
        val = val_override;
    } else {
        val = 75;
    }
    for (int i = first_led; i <= last_led; i++) {
        HSV hsv = {
            .h = hue,
            .s = sat,
            .v = val, // 120 is ok for outer uf, but inner needs brighter, and the led strip at 120 is wayyyy too bright
        };
        if (hsv.h || hsv.s) {
            RGB rgb = hsv_to_rgb(hsv);
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        }
    }
}

bool rgb_matrix_indicators_user() {
    bool is_shifted = (get_mods() | get_weak_mods()) & MOD_MASK_SHIFT;
    bool is_oneshot = (get_oneshot_mods() | get_mods()) & MOD_MASK_SHIFT;

    if (is_keyboard_left()) {
        // set LEFT per-key leds by ledmap
        set_rgb_ledmap(RGB_KEYS_L_START, RGB_KEYS_L_END, rgb_matrix_get_val(), get_highest_layer(layer_state | default_layer_state));

        if (is_shifted) {
            set_rgb_range(RGB_INDICATOR_L_START, RGB_INDICATOR_L_END, HSV_GREEN, INDICATOR_BRIGHTNESS);
        } else if (is_oneshot) {
            set_rgb_range(RGB_INDICATOR_L_START, RGB_INDICATOR_L_END, HSV_GREEN, INDICATOR_BRIGHTNESS);
        } else if (set_scrolling) {
            set_rgb_range(RGB_INDICATOR_L_START, RGB_INDICATOR_L_END, HSV_ORANGE, INDICATOR_BRIGHTNESS);
        } else {
            set_rgb_range(RGB_INDICATOR_L_START, RGB_INDICATOR_L_END, HSV_MOONLANDER, INDICATOR_IDLE_BRIGHTNESS);
        }

        switch(get_highest_layer(layer_state|default_layer_state)) {
            case 0:
                set_rgb_range(RGB_UF1_INNER_L_START, RGB_UF1_INNER_L_END, FAL1_IN_L0, UF_INNER_BRIGHTNESS);
                set_rgb_range(RGB_UF1_OUTER_L_START, RGB_UF1_OUTER_L_END, FAL1_OUT_L0, UF_OUTER_BRIGHTNESS);
                set_rgb_range(RGB_UF2_INNER_L_START, RGB_UF2_INNER_L_END, FAL2_IN_L0, UF_INNER_BRIGHTNESS);
                set_rgb_range(RGB_UF2_OUTER_L_START, RGB_UF2_OUTER_L_END, FAL2_OUT_L0, UF_OUTER_BRIGHTNESS);
                break;
            case 1:
                set_rgb_range(RGB_UF1_INNER_L_START, RGB_UF1_INNER_L_END, FAL1_IN_L1, UF_INNER_BRIGHTNESS);
                set_rgb_range(RGB_UF1_OUTER_L_START, RGB_UF1_OUTER_L_END, FAL1_OUT_L1, UF_OUTER_BRIGHTNESS);
                set_rgb_range(RGB_UF2_INNER_L_START, RGB_UF2_INNER_L_END, FAL2_IN_L1, UF_INNER_BRIGHTNESS);
                set_rgb_range(RGB_UF2_OUTER_L_START, RGB_UF2_OUTER_L_END, FAL2_OUT_L1, UF_OUTER_BRIGHTNESS);
                break;
            case 2:
                set_rgb_range(RGB_UF1_INNER_L_START, RGB_UF1_INNER_L_END, FAL1_IN_L2, UF_INNER_BRIGHTNESS);
                set_rgb_range(RGB_UF1_OUTER_L_START, RGB_UF1_OUTER_L_END, FAL1_OUT_L2, UF_OUTER_BRIGHTNESS);
                set_rgb_range(RGB_UF2_INNER_L_START, RGB_UF2_INNER_L_END, FAL2_IN_L2, UF_INNER_BRIGHTNESS);
                set_rgb_range(RGB_UF2_OUTER_L_START, RGB_UF2_OUTER_L_END, FAL2_OUT_L2, UF_OUTER_BRIGHTNESS);
                break;
            case 3:
                set_rgb_range(RGB_UF1_INNER_L_START, RGB_UF1_INNER_L_END, FAL1_IN_L3, UF_INNER_BRIGHTNESS);
                set_rgb_range(RGB_UF1_OUTER_L_START, RGB_UF1_OUTER_L_END, FAL1_OUT_L3, UF_OUTER_BRIGHTNESS);
                set_rgb_range(RGB_UF2_INNER_L_START, RGB_UF2_INNER_L_END, FAL2_IN_L3, UF_INNER_BRIGHTNESS);
                set_rgb_range(RGB_UF2_OUTER_L_START, RGB_UF2_OUTER_L_END, FAL2_OUT_L3, UF_OUTER_BRIGHTNESS);
                break;
            default:
                break;
        }   
    } else {
        // set RIGHT per-key leds by ledmap
        set_rgb_ledmap(RGB_KEYS_R_START, RGB_KEYS_R_END, rgb_matrix_get_val(), get_highest_layer(layer_state | default_layer_state));

        if (is_shifted) {
            set_rgb_range(RGB_INDICATOR_R_START, RGB_INDICATOR_R_END, HSV_GREEN, INDICATOR_BRIGHTNESS);
        } else if (is_oneshot) {
            set_rgb_range(RGB_INDICATOR_R_START, RGB_INDICATOR_R_END, HSV_GREEN, INDICATOR_BRIGHTNESS);
        } else if (set_scrolling) {
            set_rgb_range(RGB_INDICATOR_R_START, RGB_INDICATOR_R_END, HSV_ORANGE, INDICATOR_BRIGHTNESS);
        } else {
            set_rgb_range(RGB_INDICATOR_R_START, RGB_INDICATOR_R_END, HSV_MOONLANDER, INDICATOR_IDLE_BRIGHTNESS);
        }

        switch(get_highest_layer(layer_state|default_layer_state)) {
            case 0:
                set_rgb_range(RGB_UF1_INNER_R_START, RGB_UF1_INNER_R_END, FAL3_IN_L0, UF_INNER_BRIGHTNESS);
                set_rgb_range(RGB_UF1_OUTER_R_START, RGB_UF1_OUTER_R_END, FAL3_OUT_L0, UF_OUTER_BRIGHTNESS);
                set_rgb_range(RGB_UF2_INNER_R_START, RGB_UF2_INNER_R_END, FAL4_IN_L0, UF_INNER_BRIGHTNESS);
                set_rgb_range(RGB_UF2_OUTER_R_START, RGB_UF2_OUTER_R_END, FAL4_OUT_L0, UF_OUTER_BRIGHTNESS);
                break;
            case 1:
                set_rgb_range(RGB_UF1_INNER_R_START, RGB_UF1_INNER_R_END, FAL3_IN_L1, UF_INNER_BRIGHTNESS);
                set_rgb_range(RGB_UF1_OUTER_R_START, RGB_UF1_OUTER_R_END, FAL3_OUT_L1, UF_OUTER_BRIGHTNESS);
                set_rgb_range(RGB_UF2_INNER_R_START, RGB_UF2_INNER_R_END, FAL4_IN_L1, UF_INNER_BRIGHTNESS);
                set_rgb_range(RGB_UF2_OUTER_R_START, RGB_UF2_OUTER_R_END, FAL4_OUT_L1, UF_OUTER_BRIGHTNESS);
                break;
            case 2:
                set_rgb_range(RGB_UF1_INNER_R_START, RGB_UF1_INNER_R_END, FAL3_IN_L2, UF_INNER_BRIGHTNESS);
                set_rgb_range(RGB_UF1_OUTER_R_START, RGB_UF1_OUTER_R_END, FAL3_OUT_L2, UF_OUTER_BRIGHTNESS);
                set_rgb_range(RGB_UF2_INNER_R_START, RGB_UF2_INNER_R_END, FAL4_IN_L2, UF_INNER_BRIGHTNESS);
                set_rgb_range(RGB_UF2_OUTER_R_START, RGB_UF2_OUTER_R_END, FAL4_OUT_L2, UF_OUTER_BRIGHTNESS);
                break;
            case 3:
                set_rgb_range(RGB_UF1_INNER_R_START, RGB_UF1_INNER_R_END, FAL3_IN_L3, UF_INNER_BRIGHTNESS);
                set_rgb_range(RGB_UF1_OUTER_R_START, RGB_UF1_OUTER_R_END, FAL3_OUT_L3, UF_OUTER_BRIGHTNESS);
                set_rgb_range(RGB_UF2_INNER_R_START, RGB_UF2_INNER_R_END, FAL4_IN_L3, UF_INNER_BRIGHTNESS);
                set_rgb_range(RGB_UF2_OUTER_R_START, RGB_UF2_OUTER_R_END, FAL4_OUT_L3, UF_OUTER_BRIGHTNESS);
                break;
            default:
                break;
        }
    }
    return true;
}
