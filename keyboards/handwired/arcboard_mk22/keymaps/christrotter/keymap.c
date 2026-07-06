// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "arcboard_mk22.h"
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
        KC_TILD, LGUI(KC_1), _______, KC_TAB_L, QK_LAYER_LOCK, AM_Toggle, CW_TOGG,     KC_MACSHOT,KC_CHROMEWIN,KC_TAB_R,MAGIPLAY, LGUI(KC_9), KC_EQUAL, SUP_ALT_TAB,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, _______,                                 KC_Y, KC_U, LT(0,KC_I),KC_O, KC_P, KC_MINUS, CW_TOGG,       
        _______, KC_A, KC_S,  KC_D,  KC_F, KC_G,                                    KC_H, KC_J, KC_K, HOME_L, KC_QUOT, KC_SCLN,         
        KC_D, KC_Z, KC_X, KC_C, KC_V, KC_B,                       LT(0,KC_N),HOME_M,KC_COMM,KC_DOT,KC_SLASH,OSM(MOD_LGUI),         
        KC_BSPC, MO(_QWERTY), KC_DEL, _______, INPUT_CHG, KC_ESC,                      KC_SPACE,  KC_ENTER,   MO(_QWERTY), MO(_QWERTY), OSL(_QWERTY), _______,         
        KC_FINDER, WHISP_REC, OSM(MOD_LSFT), KC_ESC, _______,                   KC_LEFT, KC_UP, KC_DOWN, KC_RIGHT,_______
    )
};
