// Copyright 2023 Chris Trotter (@christrotter)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include "arcboard_mk19.h"
#include "keymap.h"

// left, flat: scroll: down, up
// left, angled: left, right
// right, angled: left, right
// right, flat: scroll: up, down

#if defined(ENCODER_MAP_ENABLE)
    const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
        [_QWERTY]   =  {
            ENCODER_CCW_CW(KC_NO, KC_NO),                   // Left,  flat
            ENCODER_CCW_CW(SFT_ALT_TAB, ALT_TAB),           // Left,  angled
            ENCODER_CCW_CW(KC_VOLD, KC_VOLU),               // Right, angled
            ENCODER_CCW_CW(KC_NO, KC_NO)                    // Right, flat
        },
        [_MOUSE]    =  {
            ENCODER_CCW_CW(_______, _______),               // Left,  flat
            ENCODER_CCW_CW(_______, _______),               // Left,  angled
            ENCODER_CCW_CW(_______, _______),               // Right, angled
            ENCODER_CCW_CW(_______, _______)                // Right, flat
        },
        [_SYMBOLS]  =  {
            ENCODER_CCW_CW(_______, _______),               // Left,  flat
            ENCODER_CCW_CW(GDOCZMOU, GDOCZMIN),             // Left,  angled
            ENCODER_CCW_CW(_______, _______),               // Right, angled
            ENCODER_CCW_CW(_______, _______)                // Right, flat
        },
        [_NAV]      =  {
            ENCODER_CCW_CW(_______, _______),               // Left,  flat
            ENCODER_CCW_CW(_______, _______),               // Left,  angled
            ENCODER_CCW_CW(_______, _______),               // Right, angled
            ENCODER_CCW_CW(_______, _______)                // Right, flat
        },
        [_RECT]      =  {
            ENCODER_CCW_CW(_______, _______),               // Left,  flat
            ENCODER_CCW_CW(_______, _______),               // Left,  angled
            ENCODER_CCW_CW(_______, _______),               // Right, angled
            ENCODER_CCW_CW(_______, _______)                // Right, flat
        },
        // the appsense layers are "base" layers, so match base encoder mapping for the most part
        [_VSCODE]      =  {
            ENCODER_CCW_CW(_______, _______),               // Left,  flat
            ENCODER_CCW_CW(_______, _______),               // Left,  angled
            ENCODER_CCW_CW(_______, _______),               // Right, angled
            ENCODER_CCW_CW(_______, _______)                // Right, flat
        },
        [_FUSION]      =  {
            ENCODER_CCW_CW(_______, _______),               // Left,  flat
            ENCODER_CCW_CW(_______, _______),               // Left,  angled
            ENCODER_CCW_CW(_______, _______),               // Right, angled
            ENCODER_CCW_CW(_______, _______)                // Right, flat
        },
        [_CHROME]      =  {
            ENCODER_CCW_CW(_______, _______),               // Left,  flat
            ENCODER_CCW_CW(_______, _______),               // Left,  angled
            ENCODER_CCW_CW(KC_TAB_L, KC_TAB_R),             // Right, angled
            ENCODER_CCW_CW(_______, _______)                // Right, flat
        },
        [_MGMT]      =  {
            ENCODER_CCW_CW(_______, _______),               // Left,  flat
            ENCODER_CCW_CW(_______, _______),               // Left,  angled
            ENCODER_CCW_CW(_______, _______),               // Right, angled
            ENCODER_CCW_CW(_______, _______)                // Right, flat
        },
    };
#endif
