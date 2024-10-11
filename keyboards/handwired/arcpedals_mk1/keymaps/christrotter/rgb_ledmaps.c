// Copyright 2021 Mikael Manukyan <arm.localhost@gmail.com>
// Copyright 2023 Chris Trotter (@christrotter)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "rgb_ledmaps.h"
#include "arcpedals_mk2.h"
#include "print.h"

#if defined(POINTING_DEVICE_ENABLE) && defined(DRAGSCROLL_ENABLE)
    #include "keymap.h"
#endif

__attribute__((weak)) bool rgb_matrix_indicators_keymap(void) { return true; }
__attribute__((weak)) bool rgb_matrix_indicators_advanced_keymap(uint8_t led_min, uint8_t led_max) { return true; }
bool process_record_user_rgb_matrix(uint16_t keycode, keyrecord_t *record) { return true; }
bool rgb_matrix_indicators_user(void) { return rgb_matrix_indicators_keymap(); }

// bool my_solid_reactive_with_CnoteIndicator(effect_params_t* params) {
//     RGB_MATRIX_USE_LIMITS(led_min, led_max);
//     uint16_t max_tick = 65535 / rgb_matrix_config.speed;
//     for (uint8_t i = led_min; i < led_max; i++) {
//         RGB_MATRIX_TEST_LED_FLAGS();
//         HSV hsv = rgb_matrix_config.hsv; // change this to our input
//         uint16_t tick = max_tick;
//         // Reverse search to find most recent key hit
//         for (int8_t j = g_last_hit_tracker.count - 1; j >= 0; j--) {
//             if (g_last_hit_tracker.x[j] == g_led_config.point[i].x && g_last_hit_tracker.y[j] == g_led_config.point[i].y && g_last_hit_tracker.tick[j] < tick) {
//                 tick = g_last_hit_tracker.tick[j];
//                 break;
//             }
//         }
//         uint16_t offset = scale16by8(tick, rgb_matrix_config.speed);
//         hsv.h += qsub8(130, offset);
//         RGB      rgb    = rgb_matrix_hsv_to_rgb(hsv);
//         rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
//     }
//     return led_max < RGB_MATRIX_LED_COUNT;
// }

// bool effect_runner_reactive_comments(effect_params_t* params, reactive_f effect_func) {
//     RGB_MATRIX_USE_LIMITS(led_min, led_max);
//     uint16_t max_tick = 65535 / qadd8(rgb_matrix_config.speed, 1);
//     // so this for loop goes through and looks for any key that has been hit
//     // if there's a hit, reset the tick for that key, break out of the loop, and
//     // set the colour accordingly
//     // we would want it to...
//     // do the search, find a key that has been hit
//     // use the 'tick' logic to force the brightness up 25% until the tick is neutralized
//     // this is a bad way of explaining it...
//     // but how is led_min/max related to keys being hit?
//     // ...there is code that basically runs through 'led_count'
//     // very much not understanding how keystroke == led in this world... g_last_hit_tracker.count
//     // last_hit_tracker
//     // it's this:
//     /*
//         typedef struct PACKED {
//             uint8_t  count;
//             uint8_t  x[LED_HITS_TO_REMEMBER];
//             uint8_t  y[LED_HITS_TO_REMEMBER];
//             uint8_t  index[LED_HITS_TO_REMEMBER];
//             uint16_t tick[LED_HITS_TO_REMEMBER];
//         } last_hit_t;
//     so: last_hit_t g_last_hit_tracker;
//     means everywhere we see g_last_hit_tracker it's actually g_last_hit_tracker.x|y|index|tick[number of hits to remember]
//     so each hit has an xy coord (g_led_config), an index position, and a tick
//     and: last_hit_buffer is also a last_hit_t; so same array type
//     ok here we go, in rgb_matrix.c, there is process_rgb_matrix and in there...
//     : if (pressed)
//     then...
//     rgb_matrix_map_row_column_to_led(row, col, led);
//     which looks at: uint8_t led_index = g_led_config.matrix_co[row][column];
//     ...but all that returns is: return led_count;
//     so this is a lot of code that is entirely locked to g_led_config...
//     and all it does is iterate through your actual led count...
//     but, for all that, it does seem to be working in the background.  so we can write functionality around g_last_hit_tracker.tick[0] type stuff
//     */
//     for (uint8_t i = led_min; i < led_max; i++) {
//         RGB_MATRIX_TEST_LED_FLAGS();
//         uint16_t tick = max_tick;
//         // Reverse search to find most recent key hit
//         for (int8_t j = g_last_hit_tracker.count - 1; j >= 0; j--) {
//             if (g_last_hit_tracker.index[j] == i && g_last_hit_tracker.tick[j] < tick) {
//                 tick = g_last_hit_tracker.tick[j];
//                 break;
//             }
//         }
//         uint16_t offset = scale16by8(tick, qadd8(rgb_matrix_config.speed, 1));
//         RGB      rgb    = rgb_matrix_hsv_to_rgb(effect_func(rgb_matrix_config.hsv, offset));
//         rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
//     }
//     return rgb_matrix_check_finished_leds(led_max);
// }
//
// bool effect_runner_reactive_pop(effect_params_t* params, reactive_f effect_func) {
//     RGB_MATRIX_USE_LIMITS(led_min, led_max);
//     uint16_t max_tick = 65535 / qadd8(rgb_matrix_config.speed, 1);
//     for (uint8_t i = led_min; i < led_max; i++) {
//         RGB_MATRIX_TEST_LED_FLAGS();
//         uint16_t tick = max_tick;
//         // Reverse search to find most recent key hit
//         for (int8_t j = g_last_hit_tracker.count - 1; j >= 0; j--) {
//             if (g_last_hit_tracker.index[j] == i && g_last_hit_tracker.tick[j] < tick) {
//                 tick = g_last_hit_tracker.tick[j];
//                 break;
//             }
//         }
//         uint16_t offset = scale16by8(tick, qadd8(rgb_matrix_config.speed, 1));
//
//         // so what is this doing... 'do some funky math magic on our hs and v'
//         // pass in hsv values from config
//         // pass in 'offset' value
//         // effect_func does stuff
//         // convert to rgb
//         // a massaged hsv value (can't find a def for rgb_matrix_hsv_to_rgb beyond 'hsv to rgb', return rgb values)
//         // into that function that returns rgb, aka, what to set the led to
//         // we pass... the base hsv value...and 'offset'
//         // 'effect_func' mashes the hsv values with offset and you get your modified hsv
//         //
//         RGB      rgb    = rgb_matrix_hsv_to_rgb(effect_func(rgb_matrix_config.hsv, offset));
//         // so what if we replaced this with 'just mess with the value'
//
//         // apply funkified colours
//         rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
//     }
//     return rgb_matrix_check_finished_leds(led_max);
// }

void set_rgb_ledmap(uint8_t first_led, uint8_t last_led, int val, int layer) {
    const ledmap *l = &(ledmaps[layer]);
    // static uint8_t leftOneIndicatorLeds[]       = {13,14,27,28,41,42};
    // static uint8_t leftTwoIndicatorLeds[]       = {15,16,29,30,43,44};
    // static uint8_t leftThreeIndicatorLeds[]     = {17,18,31,32,45,46};
    // static uint8_t rightOneIndicatorLeds[]      = {19,20,33,34,47,48};
    // static uint8_t rightTwoIndicatorLeds[]      = {21,22,35,36,49,50};
    // static uint8_t rightThreeIndicatorLeds[]    = {23,24,37,38,51,52};

    for (int i = first_led; i <= last_led; i++) {
        // RGB_TOT_IND_L is 'how many right indicator leds between left and right key ranges, in the context of the led-flag section of g_led_config'
        // cuz, ledmaps doesn't think there are any indicator leds, it believes you only have l.key-range + r.key-range = total addressable leds
        // if (!(is_keyboard_left())) {
        //     i = i - RGB_TOT_IND_L;
        // }
        HSV hsv = {
            .h = (*l)[i][0],
            .s = (*l)[i][1],
            .v = val,
        };
        // if (!(is_keyboard_left())) {
        //     i = i + RGB_TOT_IND_L;
        // } // revert i to fit the 'in reality' led sequence
        if (hsv.h || hsv.s) {
            RGB rgb = hsv_to_rgb(hsv);
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
            // actions for leds 3-5 and 9-11
            if (!(is_keyboard_left())) {
                if (i == 1) { // left-toe-1 {13,14,27,28,41,42};
                    rgb_matrix_set_color(13, rgb.r, rgb.g, rgb.b);
                    rgb_matrix_set_color(14, rgb.r, rgb.g, rgb.b);
                    rgb_matrix_set_color(27, rgb.r, rgb.g, rgb.b);
                    rgb_matrix_set_color(28, rgb.r, rgb.g, rgb.b);
                    rgb_matrix_set_color(41, rgb.r, rgb.g, rgb.b);
                    rgb_matrix_set_color(42, rgb.r, rgb.g, rgb.b);
                    continue;
                }
                if (i == 3) { // left-toe-2 {15,16,29,30,43,44};
                    rgb_matrix_set_color(15, rgb.r, rgb.g, rgb.b);
                    rgb_matrix_set_color(16, rgb.r, rgb.g, rgb.b);
                    rgb_matrix_set_color(29, rgb.r, rgb.g, rgb.b);
                    rgb_matrix_set_color(30, rgb.r, rgb.g, rgb.b);
                    rgb_matrix_set_color(43, rgb.r, rgb.g, rgb.b);
                    rgb_matrix_set_color(44, rgb.r, rgb.g, rgb.b);
                    continue;
                }
                if (i == 5) { // left-toe-3 {17,18,31,32,45,46};
                    rgb_matrix_set_color(17, rgb.r, rgb.g, rgb.b);
                    rgb_matrix_set_color(18, rgb.r, rgb.g, rgb.b);
                    rgb_matrix_set_color(31, rgb.r, rgb.g, rgb.b);
                    rgb_matrix_set_color(32, rgb.r, rgb.g, rgb.b);
                    rgb_matrix_set_color(45, rgb.r, rgb.g, rgb.b);
                    rgb_matrix_set_color(46, rgb.r, rgb.g, rgb.b);
                    continue;
                }
                if (i == 7) { // right-toe-1 {19,20,33,34,47,48};
                    // uprintf("RGB: %d %d %d \n", rgb.r, rgb.g, rgb.b);
                    // uprintf("HSV: %d %d %d \n", hsv.h, hsv.s, hsv.v);
                    rgb_matrix_set_color(19, rgb.r, rgb.g, rgb.b);
                    rgb_matrix_set_color(20, rgb.r, rgb.g, rgb.b);
                    rgb_matrix_set_color(33, rgb.r, rgb.g, rgb.b);
                    rgb_matrix_set_color(34, rgb.r, rgb.g, rgb.b);
                    rgb_matrix_set_color(47, rgb.r, rgb.g, rgb.b);
                    rgb_matrix_set_color(48, rgb.r, rgb.g, rgb.b);
                    continue;
                }
                if (i == 9) { // right-toe-2 {21,22,35,36,49,50};
                    rgb_matrix_set_color(21, rgb.r, rgb.g, rgb.b);
                    rgb_matrix_set_color(22, rgb.r, rgb.g, rgb.b);
                    rgb_matrix_set_color(35, rgb.r, rgb.g, rgb.b);
                    rgb_matrix_set_color(36, rgb.r, rgb.g, rgb.b);
                    rgb_matrix_set_color(49, rgb.r, rgb.g, rgb.b);
                    rgb_matrix_set_color(50, rgb.r, rgb.g, rgb.b);
                    continue;
                }
                if (i == 11) { // right-toe-3 {23,24,37,38,51,52};
                    rgb_matrix_set_color(23, rgb.r, rgb.g, rgb.b);
                    rgb_matrix_set_color(24, rgb.r, rgb.g, rgb.b);
                    rgb_matrix_set_color(37, rgb.r, rgb.g, rgb.b);
                    rgb_matrix_set_color(38, rgb.r, rgb.g, rgb.b);
                    rgb_matrix_set_color(51, rgb.r, rgb.g, rgb.b);
                    rgb_matrix_set_color(52, rgb.r, rgb.g, rgb.b);
                    continue;
                }
            } else {
            }
        }
    }
}

// set_rgb_range(RGB_FAL1_MIN, RGB_FAL1_MAX, FAL1_L0);
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
    for (int i = 0; i <= 5; i++) {
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
static uint8_t layerIndicatorLeds[]         = {12,25,26,39,40,53};

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    // uprintf("LastHitBufferTick, Index: %d,%d \n",(g_last_hit_tracker.tick[0]), (g_last_hit_tracker.index[0]));
    if (is_keyboard_left()) {
        // set LEFT per-key leds by ledmap
        set_rgb_ledmap(RGB_KEYS_L_MIN, RGB_KEYS_L_MAX, rgb_matrix_get_val(), get_highest_layer(layer_state | default_layer_state));
    } else {
        // set RIGHT per-key leds by ledmap
        // set_rgb_ledmap(RGB_KEYS_R_MIN, RGB_KEYS_R_MAX, rgb_matrix_get_val(), get_highest_layer(layer_state | default_layer_state));
        set_rgb_ledmap(0, 53, rgb_matrix_get_val(), get_highest_layer(layer_state | default_layer_state));
        switch(get_highest_layer(layer_state|default_layer_state)) {
            case 0:
                set_rgb_array(layerIndicatorLeds, LAYER_SCROLL);
                break;
            case 1:
                set_rgb_array(layerIndicatorLeds, LAYER_MOUSE);
                break;
            case 2:
                set_rgb_array(layerIndicatorLeds, LAYER_FUSION);
                break;
            case 3:
                set_rgb_array(layerIndicatorLeds, LAYER_SPACES);
                break;
            case 4:
                set_rgb_array(layerIndicatorLeds, LAYER_ARROWS);
                break;
            case 5:
                set_rgb_array(layerIndicatorLeds, LAYER_MODS);
                break;
            case 6:
                set_rgb_array(layerIndicatorLeds, LAYER_MGMT);
                break;
            default:
                break;
        }

    }
    return rgb_matrix_indicators_advanced_keymap(led_min, led_max);
}
