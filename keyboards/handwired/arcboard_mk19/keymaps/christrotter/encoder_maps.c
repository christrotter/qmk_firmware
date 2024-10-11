// Copyright 2023 Chris Trotter (@christrotter)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include "arcboard_mk19.h"
#include "keymap.h"

#if defined(ENCODER_MAP_ENABLE)
    const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
        [_QWERTY]   =  {
            ENCODER_CCW_CW(KC_MS_WH_DOWN, KC_MS_WH_UP), // Left,  flat
            ENCODER_CCW_CW(SFT_ALT_TAB, ALT_TAB),       // Left,  angled
            ENCODER_CCW_CW(KC_TAB_L, KC_TAB_R),         // Right, angled
            ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN)  // Right, flat
        },
        [_MOUSE]    =  {
            ENCODER_CCW_CW(KC_NO, KC_NO),               // Left,  flat
            ENCODER_CCW_CW(KC_NO, KC_NO),               // Left,  angled
            ENCODER_CCW_CW(KC_NO, KC_NO),               // Right, angled
            ENCODER_CCW_CW(KC_NO, KC_NO)                // Right, flat
        },
        [_SYMBOLS]  =  {
            ENCODER_CCW_CW(KC_NO, KC_NO),               // Left,  flat
            ENCODER_CCW_CW(GDOCZMOU, GDOCZMIN),         // Left,  angled
            ENCODER_CCW_CW(KC_NO, KC_NO),               // Right, angled
            ENCODER_CCW_CW(KC_NO, KC_NO)                // Right, flat
        },
        [_NAV]      =  {
            ENCODER_CCW_CW(KC_NO, KC_NO),               // Left,  flat
            ENCODER_CCW_CW(KC_NO, KC_NO),               // Left,  angled
            ENCODER_CCW_CW(KC_VOLD, KC_VOLU),           // Right, angled
            ENCODER_CCW_CW(ZOOM_OUT, ZOOM_IN)           // Right, flat
        },
    };
#endif
