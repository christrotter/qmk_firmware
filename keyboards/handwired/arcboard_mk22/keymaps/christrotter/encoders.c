// Copyright 2025 Chris Trotter (@christrotter)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include "arcboard_mk22.h"
#include "keymap.h"

/*
        
        ENCODER_CCW_CW(LEFT:  TOP ENCODER, LOWER ),        
        ENCODER_CCW_CW(LEFT:  TOP ENCODER, UPPER ),
        ENCODER_CCW_CW(LEFT:  RING ENCODER       ),
        
        ENCODER_CCW_CW(RIGHT: TOP ENCODER, LOWER ),
        ENCODER_CCW_CW(RIGHT: TOP ENCODER, UPPER ),
        ENCODER_CCW_CW(RIGHT: RING ENCODER       )
*/

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_QWERTY]   =  {
        ENCODER_CCW_CW(SFT_ALT_TAB, ALT_TAB),
        ENCODER_CCW_CW(KC_MPRV, KC_MNXT),
        ENCODER_CCW_CW(KC_VOLD, KC_VOLU),
        ENCODER_CCW_CW(KC_TAB_R, KC_TAB_L),
        ENCODER_CCW_CW(KC_PGDN, KC_PGUP),
        ENCODER_CCW_CW(ALT_TAB, SFT_ALT_TAB),
    },
    [_MOUSE] =  {
        ENCODER_CCW_CW(_______, _______),
        ENCODER_CCW_CW(_______, _______),
        ENCODER_CCW_CW(_______, _______),
        ENCODER_CCW_CW(_______, _______),
        ENCODER_CCW_CW(_______, _______),
        ENCODER_CCW_CW(_______, _______)
    },
    [_SYMBOLS] =  {
        ENCODER_CCW_CW(_______, _______),
        ENCODER_CCW_CW(_______, _______),
        ENCODER_CCW_CW(_______, _______),
        ENCODER_CCW_CW(_______, _______),
        ENCODER_CCW_CW(_______, _______),
        ENCODER_CCW_CW(_______, _______)
    },
    [_NAV] =  {
        ENCODER_CCW_CW(_______, _______),
        ENCODER_CCW_CW(_______, _______),
        ENCODER_CCW_CW(_______, _______),
        ENCODER_CCW_CW(_______, _______),
        ENCODER_CCW_CW(_______, _______),
        ENCODER_CCW_CW(_______, _______)
    },
    [_RECT] =  {
        ENCODER_CCW_CW(_______, _______),
        ENCODER_CCW_CW(_______, _______),
        ENCODER_CCW_CW(_______, _______),
        ENCODER_CCW_CW(_______, _______),
        ENCODER_CCW_CW(_______, _______),
        ENCODER_CCW_CW(_______, _______)
    },
    [_VSCODE] =  {
        ENCODER_CCW_CW(_______, _______),
        ENCODER_CCW_CW(_______, _______),
        ENCODER_CCW_CW(_______, _______),
        ENCODER_CCW_CW(_______, _______),
        ENCODER_CCW_CW(_______, _______),
        ENCODER_CCW_CW(_______, _______)
    },
    [_FUSION] =  {
        ENCODER_CCW_CW(_______, _______),
        ENCODER_CCW_CW(_______, _______),
        ENCODER_CCW_CW(_______, _______),
        ENCODER_CCW_CW(_______, _______),
        ENCODER_CCW_CW(_______, _______),
        ENCODER_CCW_CW(_______, _______)
    },
    [_CHROME] =  {
        ENCODER_CCW_CW(_______, _______),
        ENCODER_CCW_CW(_______, _______),
        ENCODER_CCW_CW(_______, _______),
        ENCODER_CCW_CW(_______, _______),
        ENCODER_CCW_CW(_______, _______),
        ENCODER_CCW_CW(_______, _______)
    },
    [_KICAD] =  {
        ENCODER_CCW_CW(_______, _______),
        ENCODER_CCW_CW(_______, _______),
        ENCODER_CCW_CW(_______, _______),
        ENCODER_CCW_CW(_______, _______),
        ENCODER_CCW_CW(_______, _______),
        ENCODER_CCW_CW(_______, _______)
    },
    [_MGMT] =  {
        ENCODER_CCW_CW(_______, _______),
        ENCODER_CCW_CW(_______, _______),
        ENCODER_CCW_CW(_______, _______),
        ENCODER_CCW_CW(_______, _______),
        ENCODER_CCW_CW(_______, _______),
        ENCODER_CCW_CW(_______, _______)
    },
};
