// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "arcboard_mk20.h"
#include "keymap.h"

void keyboard_post_init_user(void) {
    // Customise these values to desired behaviour
    debug_enable=true;
    debug_matrix=true;
    debug_keyboard=true;
    // debug_mouse=true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┐
     * │ A │
     * └───┘
     */
    [0] = LAYOUT_ortho_1x1(
        QK_BOOT
    )
};

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0]   =  {
        ENCODER_CCW_CW(KC_VOLU, KC_VOLD),
        ENCODER_CCW_CW(KC_TAB_L, KC_TAB_R),
        ENCODER_CCW_CW(KC_TAB_L, KC_TAB_R)
    }
};
