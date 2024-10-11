// Copyright 2023 Chris Trotter (@christrotter)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include "arcboard_mk17.h"
#include "keymap.h"

// so here, [_LAYERNAME] = { ENCODER_CCW_CW(ccw-action,cw-action), ENCODER_CCW_CW(ccw-action,cw-action), ENCODER_CCW_CW(ccw-action,cw-action), ENCODER_CCW_CW(ccw-action,cw-action) }
// where you have FalconL1, FalconL2, FalconR1, FalconR2 as the index
// as is right now, this means each side has identical encoder mapping
//  ENCODER_CCW_CW(LEFT-FALCON1), ENCODER_CCW_CW(LEFT-FALCON2),
//  ENCODER_CCW_CW(RIGHT-FALCON1), ENCODER_CCW_CW(RIGHT-FALCON2)
// and this is kinda hard to grok, cuz the physical implementation is mirrored.
//          physically |  logically  |  in-code
//          L2,L1,     |  L1,L2,     |  FAL1,FAL2
//          R1,R2      |  R1,R2      |  FAL3,FAL4
// hindsight: this seems kinda dumb...why not just re-order logical to equal physical?
#if defined(ENCODER_MAP_ENABLE)
    const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
        [_QWERTY]   =  {
            ENCODER_CCW_CW(KC_SPCLEFT, KC_SPCRGHT),     // Left,  angled
            ENCODER_CCW_CW(KC_MS_WH_DOWN, KC_MS_WH_UP), // Left,  flat
            ENCODER_CCW_CW(KC_TAB_L, KC_TAB_R),         // Right, angled
            ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN)  // Right, flat
        },
        [_MOUSE]    =  {
            ENCODER_CCW_CW(KC_MNXT, KC_MPRV),           // Left,  angled
            ENCODER_CCW_CW(KC_NO, KC_NO),               // Left,  flat
            ENCODER_CCW_CW(KC_NO, KC_NO),               // Right, angled
            ENCODER_CCW_CW(KC_VOLU, KC_VOLD)            // Right, flat
        },
        [_SYMBOLS]  =  {
            ENCODER_CCW_CW(GDOCZMIN, GDOCZMOU),         // Left,  angled
            ENCODER_CCW_CW(KC_NO, KC_NO),               // Left,  flat
            ENCODER_CCW_CW(KC_NO, KC_NO),               // Right, angled
            ENCODER_CCW_CW(KC_NO, KC_NO)                // Right, flat
        },
        [_NAV]      =  {
            ENCODER_CCW_CW(KC_NO, KC_NO),               // Left,  angled
            ENCODER_CCW_CW(KC_NO, KC_NO),               // Left,  flat
            ENCODER_CCW_CW(KC_NO, KC_NO),               // Right, angled
            ENCODER_CCW_CW(KC_NO, KC_NO)                // Right, flat
        },
    };
#endif
