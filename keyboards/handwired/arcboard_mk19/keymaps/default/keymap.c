// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#if defined(CONSOLE_ENABLE)
    #include "print.h"
    void keyboard_post_init_user(void) {
        // Customise these values to desired behaviour
        debug_enable=true;
        debug_matrix=true;
        debug_keyboard=true;
        // debug_mouse=true;
    }
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_A,  KC_B,    KC_C,    KC_D,    KC_E,   KC_F,   KC_G,   KC_H,  KC_I, KC_J, KC_K, KC_L, KC_M, KC_N, KC_O, KC_P,
        KC_A,  KC_B,    KC_C,    KC_D,    KC_E,   KC_F,   KC_G,   KC_H,  KC_I, KC_J, KC_K, KC_L, KC_M, KC_N, KC_O, KC_P,
        KC_A,  KC_B,    KC_C,    KC_D,    KC_E,   KC_F,   KC_G,   KC_H,  KC_I, KC_J, KC_K, KC_L, KC_M, KC_N, KC_O, KC_P,
        KC_A,  KC_B,    KC_C,    KC_D,    KC_E,   KC_F,   KC_G,   KC_H,  KC_I, KC_J, KC_K, KC_L, KC_M, KC_N, KC_O, KC_P,
        KC_A,  KC_B,    KC_C,    KC_D,    KC_E,   KC_F,   KC_G,   KC_H,  KC_I, KC_J, KC_K, KC_L, KC_M, KC_N, KC_O, KC_P,
        KC_A,  KC_B,    KC_C,    KC_D,    KC_E,   KC_F,   KC_G,   KC_H,  KC_I, KC_J, KC_K, KC_L, KC_M, KC_N, KC_O, KC_P,
        KC_A,  KC_B,    KC_C,    KC_D,    KC_E,   KC_F,   KC_G,   KC_H,  KC_I, KC_J, KC_K, KC_L, KC_M, KC_N, KC_O, KC_P,
        KC_A,  KC_B,    KC_C,    KC_D,    KC_E,   KC_F,   KC_G,   KC_H,  KC_I, KC_J, KC_K, KC_L, KC_M, KC_N, KC_O, KC_P,
        KC_A,  KC_B,    KC_C,    KC_D,    KC_E,   KC_F,   KC_G,   KC_H,  KC_I, KC_J, KC_K, KC_L, KC_M, KC_N, KC_O, KC_P,
        KC_A,  KC_B,    KC_C,    KC_D,    KC_E,   KC_F,   KC_G,   KC_H,  KC_I, KC_J, KC_K, KC_L, KC_M, KC_N, KC_O, KC_P,
        KC_A,  KC_B,    KC_C,    KC_D,    KC_E,   KC_F,   KC_G,   KC_H,  KC_I, KC_J, KC_K, KC_L, KC_M, KC_N, KC_O, KC_P,
        KC_A,  KC_B,    KC_C,    KC_D,    KC_E,   KC_F,   KC_G,   KC_H,  KC_I, KC_J, KC_K, KC_L, KC_M, KC_N, KC_O, KC_P,
        KC_A,  KC_B,    KC_C,    KC_D,    KC_E,   KC_F,   KC_G,   KC_H,  KC_I, KC_J, KC_K, KC_L, KC_M, KC_N, KC_O, KC_P,
        KC_A,  KC_B,    KC_C,    KC_D,    KC_E,   KC_F,   KC_G,   KC_H,  KC_I, KC_J, KC_K, KC_L, KC_M, KC_N, KC_O, KC_P,
        KC_A,  KC_B,    KC_C,    KC_D,    KC_E,   KC_F,   KC_G,   KC_H,  KC_I, KC_J, KC_K, KC_L, KC_M, KC_N, KC_O, KC_P,
        KC_A,  KC_B,    KC_C,    KC_D,    KC_E,   KC_F,   KC_G,   KC_H,  KC_I, KC_J, KC_K, KC_L, KC_M, KC_N, KC_O, KC_P,
        KC_A,  KC_B,    KC_C,    KC_D,    KC_E,   KC_F,   KC_G,   KC_H,  KC_I, KC_J, KC_K, KC_L, KC_M, KC_N, KC_O, KC_P,
        KC_A,  KC_B,    KC_C,    KC_D,    KC_E,   KC_F,   KC_G,   KC_H,  KC_I, KC_J, KC_K, KC_L, KC_M, KC_N, KC_O, KC_P,
        KC_A,  KC_B,    KC_C,    KC_D,    KC_E,   KC_F,   KC_G,   KC_H,  KC_I, KC_J, KC_K, KC_L, KC_M, KC_N, KC_O, KC_P,
        KC_A,  KC_B,    KC_C,    KC_D,    KC_E,   KC_F,   KC_G,   KC_H,  KC_I, KC_J, KC_K, KC_L, KC_M, KC_N, KC_O, KC_P
    )
};
