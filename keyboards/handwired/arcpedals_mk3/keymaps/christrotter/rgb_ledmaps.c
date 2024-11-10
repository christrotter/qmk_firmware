// Copyright 2021 Mikael Manukyan <arm.localhost@gmail.com>
// Copyright 2023 Chris Trotter (@christrotter)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "rgb_ledmaps.h"
#include "arcpedals_mk3.h"
#include "print.h"
#include "keymap.h"

__attribute__((weak)) bool rgb_matrix_indicators_keymap(void) { return true; }
__attribute__((weak)) bool rgb_matrix_indicators_advanced_keymap(uint8_t led_min, uint8_t led_max) { return true; }
bool process_record_user_rgb_matrix(uint16_t keycode, keyrecord_t *record) { return true; }
bool rgb_matrix_indicators_user(void) { return rgb_matrix_indicators_keymap(); }


// void set_rgb_ledmap(uint8_t first_led, uint8_t last_led, int val, int layer) {
//     const ledmap *l = &(ledmaps[layer]);
// 
//     for (int i = first_led; i <= last_led; i++) {
//         HSV hsv = {
//             .h = (*l)[i][0],
//             .s = (*l)[i][1],
//             .v = val,
//         };
//         if (hsv.h || hsv.s) {
//             RGB rgb = hsv_to_rgb(hsv);
//             rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
//         }
//     }
// }

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

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (is_keyboard_left()) {
        // set LEFT per-key leds by ledmap
        set_rgb_ledmap(RGB_START_LEDMAP_LEFT, RGB_END_LEDMAP_LEFT, RGB_LEDMAP_BRIGHTNESS, get_highest_layer(layer_state | default_layer_state));
        // set background colour  
        switch(get_highest_layer(layer_state|default_layer_state)) {
            case 0:
                set_rgb_range(RGB_INDICATOR_L_START, RGB_INDICATOR_L_END, HSV_CYAN, RGB_INDICATOR_BRIGHTNESS);
                break;
            case 1:
                set_rgb_range(RGB_INDICATOR_L_START, RGB_INDICATOR_L_END, HSV_GREEN, RGB_INDICATOR_BRIGHTNESS);
                break;
            case 2:
                set_rgb_range(RGB_INDICATOR_L_START, RGB_INDICATOR_L_END, HSV_ORANGE, RGB_INDICATOR_BRIGHTNESS);
                break;
            case 3:
                set_rgb_range(RGB_INDICATOR_L_START, RGB_INDICATOR_L_END, HSV_RED, RGB_INDICATOR_BRIGHTNESS);
                break;
            default:
                break;
        }
    } else {
        // set RIGHT per-key leds by ledmap
        set_rgb_ledmap(RGB_START_LEDMAP_RIGHT, RGB_END_LEDMAP_RIGHT, RGB_LEDMAP_BRIGHTNESS, get_highest_layer(layer_state | default_layer_state)); 
        switch(get_highest_layer(layer_state|default_layer_state)) {
            case 0:
                set_rgb_range(RGB_INDICATOR_R_START, RGB_INDICATOR_R_END, HSV_CYAN, RGB_INDICATOR_BRIGHTNESS);
                break;
            case 1:
                set_rgb_range(RGB_INDICATOR_R_START, RGB_INDICATOR_R_END, HSV_GREEN, RGB_INDICATOR_BRIGHTNESS);
                break;
            case 2:
                set_rgb_range(RGB_INDICATOR_R_START, RGB_INDICATOR_R_END, HSV_ORANGE, RGB_INDICATOR_BRIGHTNESS);
                break;
            case 3:
                set_rgb_range(RGB_INDICATOR_R_START, RGB_INDICATOR_R_END, HSV_RED, RGB_INDICATOR_BRIGHTNESS);
                break;
            default:
                break;
        } 
    }

    return rgb_matrix_indicators_advanced_keymap(led_min, led_max);
}
