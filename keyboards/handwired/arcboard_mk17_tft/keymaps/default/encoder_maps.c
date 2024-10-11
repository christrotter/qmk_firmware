/*
 * Copyright 2023 Chris Trotter <ctrotter@gmail.com> (@christrotter)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Publicw License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "quantum.h"
#include "arcboard_mk17_tft.h"
#include "keymap.h"

#if defined(RGB_MATRIX_LEDMAPS_ENABLED)
    // where...the _L# = layer numbers
    // and...
    // FAL1 = left2 (flat)
    // FAL2 = left1 (angled)
    // FAL3 = right1(angled)
    // FAL4 = right2(flat)

    // left, flat
    #define FAL1_L0 CYAN
    #define FAL1_L1 PINK
    #define FAL1_L2 RED
    #define FAL1_L3 RED
    // left, angled
    #define FAL2_L0 CYAN
    #define FAL2_L1 RED
    #define FAL2_L2 BLUE
    #define FAL2_L3 RED
    // right, angled - full-time layer selector
    #define FAL3_L0 WHITE
    #define FAL3_L1 RED
    #define FAL3_L2 PINK
    #define FAL3_L3 CHART
    // right, flat
    #define FAL4_L0 CYAN
    #define FAL4_L1 GREEN
    #define FAL4_L2 RED
    #define FAL4_L3 RED
#endif
// so here, [_LAYERNAME] = { ENCODER_CCW_CW(ccw-action,cw-action), ENCODER_CCW_CW(ccw-action,cw-action), ENCODER_CCW_CW(ccw-action,cw-action), ENCODER_CCW_CW(ccw-action,cw-action) }
// where you have FalconL1, FalconL2, FalconR1, FalconR2 as the index
// as is right now, this means each side has identical encoder mapping
//  ENCODER_CCW_CW(LEFT-FALCON1), ENCODER_CCW_CW(LEFT-FALCON2),
//  ENCODER_CCW_CW(RIGHT-FALCON1), ENCODER_CCW_CW(RIGHT-FALCON2)
// and this is kinda hard to grok, cuz the physical implementation is mirrored.
//          physically |  logically
//          L2,L1,     |  L1,L2,
//          R1,R2      |  R1,R2
// hindsight: this seems kinda dumb...why not just re-order logical to equal physical?
#if defined(ENCODER_MAP_ENABLE)
    const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
        [_QWERTY]   =  {
            ENCODER_CCW_CW(KC_SPCLEFT, KC_SPCRGHT),     // Left,  angled
            ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN), // Left,  flat
            ENCODER_CCW_CW(TO(_MOUSE), KC_NO),          // Right, angled
            ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN)  // Right, flat
        },
        [_MOUSE]    =  {
            ENCODER_CCW_CW(KC_MNXT, KC_MPRV),           // Left,  angled
            ENCODER_CCW_CW(KC_NO, KC_NO),               // Left,  flat
            ENCODER_CCW_CW(TO(_SYMBOLS), TO(_QWERTY)),  // Right, angled
            ENCODER_CCW_CW(KC_VOLU, KC_VOLD)            // Right, flat
        },
        [_SYMBOLS]  =  {
            ENCODER_CCW_CW(GDOCZMIN, GDOCZMOU),         // Left,  angled
            ENCODER_CCW_CW(KC_NO, KC_NO),               // Left,  flat
            ENCODER_CCW_CW(TO(_NAV), TO(_MOUSE)),       // Right, angled
            ENCODER_CCW_CW(KC_NO, KC_NO)                // Right, flat
        },
        [_NAV]      =  {
            ENCODER_CCW_CW(KC_NO, KC_NO),               // Left,  angled
            ENCODER_CCW_CW(KC_NO, KC_NO),               // Left,  flat
            ENCODER_CCW_CW(KC_NO, TO(_SYMBOLS)),        // Right, angled
            ENCODER_CCW_CW(KC_NO, KC_NO)                // Right, flat
        },
    };
#endif
