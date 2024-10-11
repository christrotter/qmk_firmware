// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "arcpedals_mk3.h"
#include "keymap.h"

enum keycodes {
  KC_CYCLE_LAYERS = QK_USER,
};

#if defined(RGB_MATRIX_LEDMAPS_ENABLED)
    #include "rgb_ledmaps.h"
#endif

__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) { return true; }
__attribute__((weak)) void post_process_record_keymap(uint16_t keycode, keyrecord_t *record) {}
void                       post_process_record_user(uint16_t keycode, keyrecord_t *record) { post_process_record_keymap(keycode, record); }

/*
    Physical layout:
               #### LEFT FOOT ####            ###               #### RIGHT FOOT ####
    topL, topR, botL, botR,         desk1     ###      topL, topR, botL, botR,         desk1
    sideL, sideR, heelL, heelR,     desk2     ###      sideL, sideR, heelL, heelR,     desk2
*/
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_SCROLL] = LAYOUT(
        KC_MS_WH_UP,    KC_MS_WH_DOWN,    KC_MS_BTN1,     KC_MS_WH_LEFT,   KC_E,           MO(1),    KC_Y,    KC_X,     KC_W,   KC_U,
        KC_MS_BTN3,    KC_CYCLE_LAYERS,    QK_BOOT,     KC_MS_WH_RIGHT,   KC_5,           KC_0,    KC_9,    KC_8,     KC_7,   KC_6
    ),
    [_MOUSE] = LAYOUT(
        _______,    _______,    _______,     _______,   _______,           _______,    _______,    _______,     _______,   _______,
        _______,    _______,    _______,     _______,   _______,           _______,    _______,    _______,     _______,   _______
    ),
    [_FUSION] = LAYOUT(
        _______,    _______,    _______,     _______,   _______,           _______,    _______,    _______,     _______,   _______,
        _______,    _______,    _______,     _______,   _______,           _______,    _______,    _______,     _______,   _______
    ),
    [_MGMT] = LAYOUT(
        _______,    _______,    _______,     _______,   _______,           _______,    _______,    _______,     _______,   _______,
        _______,    _______,    _______,     _______,   _______,           _______,    _______,    _______,     _______,   _______
    )
};

// super important to get the wiring order correct!!!

#if defined(RGB_MATRIX_LEDMAPS_ENABLED)
// the indicator LEDs are mapped using the flags and for loop.
const ledmap ledmaps[] = {
    [_SCROLL]   = LEDMAP(
      RED, RED, RED, GREEN, GREEN, GREEN, BLUE, BLUE, BLUE, ORANGE, ORANGE, ORANGE, YELLOW, YELLOW, YELLOW, CYAN, CYAN, CYAN, CHART, CHART, CHART, PURPLE, PURPLE, PURPLE, PINK, PINK, PINK, RED, RED, RED,         RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED
   ),
   [_MOUSE]     = LEDMAP(
      GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN,         GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN
   ),
    [_FUSION]   = LEDMAP(
      RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED,         RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED
   ),
   [_MGMT]     = LEDMAP(
      RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED,         RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED
   )
};
#endif // RGB_MATRIX_LEDMAPS_ENABLED

/*
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_SCROLL] = LAYOUT(
    // physical layout is:
    //      (LEFT)                                                   (RIGHT)
    // left, toe, ball, right                              -    left, toe, ball, right
    KC_MS_BTN1, KC_MS_WH_DOWN, KC_CYCLE_LAYERS, KC_MS_WH_RIGHT,      KC_MS_WH_LEFT, KC_MS_WH_UP, KC_CYCLE_LAYERS, KC_MS_BTN3
),
[_MOUSE] = LAYOUT(
    KC_NO, KC_MS_BTN3, KC_CYCLE_LAYERS, KC_MS_BTN1,                            KC_NO, KC_MS_BTN1, KC_CYCLE_LAYERS, KC_MS_BTN2
),
[_FUSION] = LAYOUT(
    KC_NO, KC_LGUI, KC_CYCLE_LAYERS, KC_MS_WH_DOWN,              KC_MS_WH_UP, KC_MS_BTN3, KC_CYCLE_LAYERS, KC_NO
),
[_MGMT] = LAYOUT(
    KC_NO, EE_CLR, KC_CYCLE_LAYERS, KC_NO,                              KC_NO, QK_BOOT, KC_CYCLE_LAYERS, KC_NO
)
};
*/

#if defined(CONSOLE_ENABLE)
    #include "print.h"
    void keyboard_post_init_user(void) {
        // Customise these values to desired behaviour
        debug_enable=true;
        debug_matrix=true;
        // debug_keyboard=true;
        // debug_mouse=true;
        // eeconfig_init();
    }
#endif
