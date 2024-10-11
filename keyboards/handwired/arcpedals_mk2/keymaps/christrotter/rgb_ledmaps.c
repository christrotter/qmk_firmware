// Copyright 2021 Mikael Manukyan <arm.localhost@gmail.com>
// Copyright 2023 Chris Trotter (@christrotter)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "rgb_ledmaps.h"
#include "arcpedals_mk2.h"
#include "print.h"
#include "keymap.h"

__attribute__((weak)) bool rgb_matrix_indicators_keymap(void) { return true; }
__attribute__((weak)) bool rgb_matrix_indicators_advanced_keymap(uint8_t led_min, uint8_t led_max) { return true; }
bool process_record_user_rgb_matrix(uint16_t keycode, keyrecord_t *record) { return true; }
bool rgb_matrix_indicators_user(void) { return rgb_matrix_indicators_keymap(); }


void set_rgb_ledmap(uint8_t first_led, uint8_t last_led, int val, int layer) {
    const ledmap *l = &(ledmaps[layer]);

    for (int i = first_led; i <= last_led; i++) {
        HSV hsv = {
            .h = (*l)[i][0],
            .s = (*l)[i][1],
            .v = val,
        };
        if (hsv.h || hsv.s) {
            RGB rgb = hsv_to_rgb(hsv);
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        }
    }
}

void set_rgb_range(uint8_t first_led, uint8_t last_led, int hue, int sat, int val) {
    for (int i = first_led; i <= last_led; i++) {
        HSV hsv = {
            .h = hue,
            .s = sat,
            .v = RGB_INDICATOR_BRIGHTNESS,
        };
        if (hsv.h || hsv.s) {
            RGB rgb = hsv_to_rgb(hsv);
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        }
    }
}

void set_rgb_array(uint8_t ledArray[], int hue, int sat, int val) {
    for (int i = 0; i <= 23; i++) {
        HSV hsv = {
            .h = hue,
            .s = sat,
            .v = RGB_INDICATOR_BRIGHTNESS,
        };
        if (hsv.h || hsv.s) {
            RGB rgb = hsv_to_rgb(hsv);
            rgb_matrix_set_color(ledArray[i], rgb.r, rgb.g, rgb.b);
        }
    }
}

// this is not great, but then I'm not great with C
static uint8_t layerIndicatorLeds[] = {16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39};

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (is_keyboard_left()) {
        // set LEFT per-key leds by ledmap
        set_rgb_ledmap(0, 7, rgb_matrix_get_val(), get_highest_layer(layer_state | default_layer_state));
    } else {
        // set RIGHT per-key leds by ledmap
        set_rgb_ledmap(8, 15, rgb_matrix_get_val(), get_highest_layer(layer_state | default_layer_state));

        // set trackball module leds to layer colour
        switch(get_highest_layer(layer_state|default_layer_state)) {
            case 0:
                set_rgb_array(layerIndicatorLeds, HSV_SPRINGGREEN);
                break;
            case 1:
                set_rgb_array(layerIndicatorLeds, HSV_PINK);
                break;
            case 2:
                set_rgb_array(layerIndicatorLeds, HSV_ORANGE);
                break;
            case 3:
                set_rgb_array(layerIndicatorLeds, HSV_RED);
                break;
            default:
                break;
        }
    }
    return rgb_matrix_indicators_advanced_keymap(led_min, led_max);
}
