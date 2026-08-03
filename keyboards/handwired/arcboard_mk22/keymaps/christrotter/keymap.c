// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
// #include "arcboard_mk22.h"
#include "keymap.h"


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┐
     * │ 7 │ 8 │ 9 │ / │
     * ├───┼───┼───┼───┤
     * │ 4 │ 5 │ 6 │ * │
     * ├───┼───┼───┼───┤
     * │ 1 │ 2 │ 3 │ - │
     * ├───┼───┼───┼───┤
     * │ 0 │ . │Ent│ + │
     * └───┴───┴───┴───┘
     */
    [0] = LAYOUT(
        EE_CLR, KC_1, KC_2, KC_3, KC_4, KC_5,          EE_CLR, KC_7, KC_8, KC_9, KC_0, KC_EQUAL,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T,           KC_Y, KC_U, KC_I, KC_O, KC_P, KC_MINUS,
        KC_0, KC_A, KC_S, KC_D, KC_F, KC_G,             KC_H, KC_J, KC_K, KC_L, KC_COLON, KC_QUOTE,
        KC_0, KC_Z, KC_X, KC_C, KC_V, KC_B,             KC_N, KC_M, KC_COMMA, KC_DOT, KC_SLASH, KC_LCMD,
        KC_BSPC, KC_0, KC_DEL, KC_1, KC_ESC,            KC_SPACE, KC_ENTER, KC_0, KC_1, KC_2,
        KC_L, KC_M, KC_R,                               KC_L, KC_M, KC_R,
        KC_A, KC_B, KC_C, KC_D, KC_E,                   KC_A, KC_B, KC_C, KC_D, KC_E
    )
};

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0]   =  {
        ENCODER_CCW_CW(KC_VOLD, KC_VOLU),
        ENCODER_CCW_CW(KC_VOLD, KC_VOLU),
        ENCODER_CCW_CW(KC_VOLD, KC_VOLU),
        ENCODER_CCW_CW(KC_A, KC_B),
        ENCODER_CCW_CW(KC_A, KC_B),
        ENCODER_CCW_CW(KC_A, KC_B)
    },
};

// the indicator LEDs are mapped using the flags and for loop.
// const ledmap ledmaps[] = {
//    [0]   = LEDMAP(
//     CYAN, CYAN, ___n___, RED, SPRING, SPRING,                                                   ORANGE,   SPRING,   GREEN,    PINK,    CYAN,    CYAN,
//     GOLD   , ___n___, ___n___, ___n___, ___n___, ___n___,                                       ___n___, ___n___, ___n___, ___n___, ___n___,    CYAN, 
//     ___n___, ___n___, ___n___, ___n___, ___n___, ___n___,                                       ___n___, ___n___, ___n___, HRM_ALT, ___n___, ___n___, 
//     ORANGE, ___n___, ___n___, ___n___, ___n___, ___n___,                                        ___n___, HRM_CTL, ___n___, ___n___, ___n___, HRM_GUI,
//     RED, TOG_NAV, RED, ___n___, SPRING, RED,                                                    SPACE,ENTER, TOG_SYM,   TOG_NAV,   TOG_RECT, ___n___,
//     ___n___, RED, GREEN, BLUE, BLUE, GREEN, BLUE,                                                GREEN, GREEN, GREEN, GREEN, ORANGE, GREEN, BLUE
//     ),
// };


void keyboard_post_init_user(void) {
    // Customise these values to desired behaviour
    debug_enable=true;
    debug_matrix=true;
    debug_keyboard=true;
    // debug_mouse=true;
    // init_ui();   // Initialise the display
}
