// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

static uint32_t hello_timer = 0;

void keyboard_post_init_user(void) {
    // Customise these values to desired behaviour
    debug_enable=true;
    debug_matrix=true;
    debug_keyboard=true;
    // debug_mouse=true;
    hello_timer = timer_read32();
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┐
     * │ A │
     * └───┘
     */
    [0] = LAYOUT_ortho_1x1(
        KC_A
    )
};

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0]   =  {
        ENCODER_CCW_CW(KC_VOLU, KC_VOLD)
    }
};

void matrix_scan_user(void) {
    if (timer_elapsed32(hello_timer) > 1000) { // 1000ms = 1 second
        printf("hello\n");
        hello_timer = timer_read32(); // Reset the timer
    }
}