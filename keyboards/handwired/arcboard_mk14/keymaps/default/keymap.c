// Copyright 2022 Chris Trotter (@christrotter)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// Note you need to turn off some items in rules.mk if you are not using the christrotter keymap (ledmaps, tapdance)
#define XXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
// clang-format off
    /* row,col
     * ,------------------------------------------------,                             ,------------------------------------------------,
     * |  1,1 |  1,2 |  1,3 |  1,4 |  1,5 |  1,6 |  1,7 |                             |  1,1 |  1,2 |  1,3 |  1,4 |  1,5 |  1,6 |  1,7 |
     * |------+------+------+------+------+------+------|                             |------+------+------+------+------+------+------|
     * |  2,1 |  2,2 |  2,3 |  2,4 |  2,5 |  2,6 |  2,7 |                             |  2,1 |  2,2 |  2,3 |  2,4 |  2,5 |  2,6 |  2,7 |
     * |------+------+------+------+------+------+------|                             |------+------+------+------+------+------+------|
     * |  3,1 |  3,2 |  3,3 |  3,4 |  3,5 |  3,6 |  3,7 |                             |  3,1 |  3,2 |  3,3 |  3,4 |  3,5 |  3,6 |  3,7 |
     * |------+------+------+------+------+------+------|                             |------+------+------+------+------+------+------|
     * |  4,1 |  4,2 |  4,3 |  4,4 |  4,5 |  4,6 |  4,7 |                             |  4,1 |  4,2 |  4,3 |  4,4 |  4,5 |  4,6 |  4,7 |
     * |------+------+------+------+------+------+------|                             |------+------+------+------+------+------+------|
     * |  5,1 |  5,2 |  5,3 |  5,4 |  5,5 |  5,6 |  5,7 |                             |  5,1 |  5,2 |  5,3 |  5,4 |  5,5 |  5,6 |  5,7 |
     * |------+------+------+------+------+------+------+------,        ,------|------+------+----+-+----+-+------+------+------|------|
     *               |  6,1 | 6,2  |             | 7,1  | 7,2  |        | 7,1  | trackball | 7,5  | 7,6  | |  6,1 | 6,2  |
     *               `------+------+------+------+------+------|        '-+----'-+-----,---+------+------+ '------+------+
     *                             | 7,6  | 7,5  | 7,4  | 7,3  |                 | 7,3 | 7,4  |
     *                             '------+------+------+------'              ,--+-----+------'
     *                                                                       | 7,2  |
     *                                                                        '------'
     * Sorry about the reversing of the left thumb column...wiring from underneath causes natural mirroring!
     */
// clang-format on

[0] = LAYOUT( \
    KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, _______,              _______, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F12,
    KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, _______,                   _______, KC_6, KC_7, KC_8, KC_9, KC_0, KC_EQUAL,
    KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, _______,                   _______, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_MINUS,
    KC_LSFT, KC_A,  KC_S,  KC_D,  KC_F, KC_G, KC_PGUP,              KC_HOME, KC_H, KC_J, KC_K, KC_L, KC_QUOT, KC_SCLN,
    _______, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_PGDN,                  KC_END, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLASH, _______,
                      KC_DOWN, KC_UP,                                                                      KC_LEFT, KC_RIGHT,
            KC_BSPC, _______, KC_DEL, KC_ESC, KC_LGUI, _______,      _______, KC_LSFT, _______, KC_LGUI, KC_ENTER, KC_SPACE
)
};
