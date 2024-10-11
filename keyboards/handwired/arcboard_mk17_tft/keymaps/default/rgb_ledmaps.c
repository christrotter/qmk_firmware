/* Copyright 2021 Mikael Manukyan <arm.localhost@gmail.com>
 * Copyright 2023 Chris Trotter <ctrotter@gmail.com> (@christrotter)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "rgb_ledmaps.h"
#include "arcboard_mk17_tft.h"

#if defined(POINTING_DEVICE_ENABLE) && defined(DRAGSCROLL_ENABLE)
    #include "keymap.h"
#endif

__attribute__((weak)) bool rgb_matrix_indicators_keymap(void) { return true; }
__attribute__((weak)) bool rgb_matrix_indicators_advanced_keymap(uint8_t led_min, uint8_t led_max) { return true; }

void set_rgb_range(uint8_t first_led, uint8_t last_led, int val, int layer) {
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

void set_rgb_led(int index, int hue, int sat, int val) {
    HSV hsv = {
        .h = hue,
        .s = sat,
        .v = 30,
    };
    if (hsv.h || hsv.s) {
        RGB rgb = hsv_to_rgb(hsv);
        rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
    }
}

bool process_record_user_rgb_matrix(uint16_t keycode, keyrecord_t *record) { return true; }
bool rgb_matrix_indicators_user(void) { return rgb_matrix_indicators_keymap(); }

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    for (uint8_t i = led_min; i <= led_max; i++) {
        if (is_keyboard_left()) {
            if (HAS_FLAGS(g_led_config.flags[i], 0x04)) {
                set_rgb_range(RGB_KEYS_L_MIN, RGB_KEYS_L_MAX, rgb_matrix_get_val(), get_highest_layer(layer_state | default_layer_state));
            }
            switch(get_highest_layer(layer_state|default_layer_state)) {
                case 0:
                    if (HAS_FLAGS(g_led_config.flags[i], 0x01)) {
                        set_rgb_led(i, HSV_CYAN);
                    }
                    if (HAS_FLAGS(g_led_config.flags[i], 0x02)) {
                        set_rgb_led(i, HSV_RED);
                    }
                    if (HAS_FLAGS(g_led_config.flags[i], 0x08)) {
                        set_rgb_led(i, HSV_PURPLE);
                    }
                    break;
                case 1:
                    if (HAS_FLAGS(g_led_config.flags[i], 0x01)) {
                        set_rgb_led(i, HSV_BLUE);
                    }
                    if (HAS_FLAGS(g_led_config.flags[i], 0x02)) {
                        set_rgb_led(i, HSV_PURPLE);
                    }
                    if (HAS_FLAGS(g_led_config.flags[i], 0x08)) {
                        set_rgb_led(i, HSV_PINK);
                    }
                    break;
                default:
                    break;
            }
        } else {
            if (HAS_FLAGS(g_led_config.flags[i], 0x04)) {
                set_rgb_range(RGB_KEYS_R_MIN, RGB_KEYS_R_MAX, rgb_matrix_get_val(), get_highest_layer(layer_state | default_layer_state));
            }
            switch(get_highest_layer(layer_state|default_layer_state)) {
                case 0:
                    if (HAS_FLAGS(g_led_config.flags[i], 0x01)) {
                        set_rgb_led(i, HSV_GREEN);
                    }
                    if (HAS_FLAGS(g_led_config.flags[i], 0x02)) {
                        set_rgb_led(i, HSV_GOLD);
                    }
                    if (HAS_FLAGS(g_led_config.flags[i], 0x08)) {
                        set_rgb_led(i, HSV_CYAN);
                    }
                    break;
                case 1:
                    if (HAS_FLAGS(g_led_config.flags[i], 0x01)) {
                        set_rgb_led(i, HSV_CHARTREUSE);
                    }
                    if (HAS_FLAGS(g_led_config.flags[i], 0x02)) {
                        set_rgb_led(i, HSV_ORANGE);
                    }
                    if (HAS_FLAGS(g_led_config.flags[i], 0x08)) {
                        set_rgb_led(i, HSV_RED);
                    }
                    break;
                default:
                    break;
            }
        }
    }
    bool is_shifted = (get_mods() | get_weak_mods()) & MOD_MASK_SHIFT;
    if (is_shifted) {
        for (uint8_t i = led_min; i <= led_max; i++) {
            if (HAS_FLAGS(g_led_config.flags[i], 0x08)) {
                set_rgb_led(i, INDICATOR_SHIFT);
            }
        }
    } else {
        for (uint8_t i = led_min; i <= led_max; i++) {
            if (HAS_FLAGS(g_led_config.flags[i], 0x08)) {
                set_rgb_led(i, INDICATOR_BG);
            }
        }
    }
    return rgb_matrix_indicators_advanced_keymap(led_min, led_max);
}
