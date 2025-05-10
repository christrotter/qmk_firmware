// Copyright 2023 Chris Trotter (@christrotter)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

#define XXX KC_NO
#define __LED__ KC_NO

#define KC_CHRMCYC LGUI(KC_TILDE)

// single button to reset layer
#define KC_LAYRST TO(_QWERTY)

#if defined(RGB_MATRIX_LEDMAPS_ENABLED)
    // note: these cannot have braces e.g. #define HRM_SFT {GREEN} blows up the evaluation of the [3] part of the int[KEYS_COUNT][3]; sees it as one item
    #define ___n___ {0, 0, 0}
    #define LAYER_0_COLOUR HSV_CYAN
    #define LAYER_1_COLOUR HSV_ORANGE
    #define LAYER_2_COLOUR HSV_RED
    #define LAYER_FUSION ORANGE
    #define LAYER_MGMT RED
    #define BLANK {HSV_WHITE}
    #define CMD {HSV_PURPLE}
    #define SHIFT {HSV_GREEN}
    #define CTRL {HSV_BLUE}
    #define ALT {HSV_YELLOW}
    #define CYCLE {HSV_SPRINGGREEN}
    #define DRAGTOG {HSV_ORANGE}
    #define KB_RECT {HSV_RED}

    /* 
    L_B1_L0 = bottom-toe, lower
    L_B2_L0 = bottom-toe, upper
    L_B3_L0 = upper-toe, right
    L_B4_L0 = upper-toe, left
    L_B5_L0 = side, right
    L_B6_L0 = side, left
    L_B7_L0 = heel
    L_B8_L0 = heel
    
    R_B1_L0 = bottom-toe, upper
    R_B2_L0 = bottom-toe, lower
    R_B3_L0 = upper-toe, right
    R_B4_L0 = upper-toe, left
    R_B5_L0 = side, left
    R_B6_L0 = side, right
    R_B7_L0 = heel
    R_B8_L0 = heel
    */

    // SCROLL
    #define L_B1_L0 {HSV_RED}      // outside, lower big toe
    #define L_B2_L0 {HSV_RED}       // inside, upper big toe
    #define L_B3_L0 CMD     // top inside
    #define L_B4_L0 CMD    // top outside
    #define L_B5_L0 DRAGTOG    // side inside
    #define L_B6_L0 KB_RECT       // side outside
    #define L_B7_L0 CYCLE
    #define L_B8_L0 CYCLE
    
    #define R_B1_L0 {HSV_GREEN}     // inside, upper big toe
    #define R_B2_L0 {HSV_GREEN}      // outside, lower big toe
    #define R_B3_L0 CMD    // top inside
    #define R_B4_L0 CMD    // top outside
    #define R_B5_L0 DRAGTOG     // side inside
    #define R_B6_L0 KB_RECT       // side outside
    #define R_B7_L0 CYCLE
    #define R_B8_L0 CYCLE

    // ARROWS
    #define L_B1_L1 {HSV_GREEN}  // outside, lower big toe
    #define L_B2_L1 {HSV_GREEN}  // inside, upper big toe
    #define L_B3_L1 SHIFT  // top inside
    #define L_B4_L1 CMD // top outside
    #define L_B5_L1 {HSV_GREEN} // side inside
    #define L_B6_L1 {HSV_RED}    // side outside
    #define L_B7_L1 CYCLE
    #define L_B8_L1 CYCLE
    
    #define R_B1_L1 {HSV_GREEN}  // inside, upper big toe
    #define R_B2_L1 {HSV_GREEN}  // outside, lower big toe
    #define R_B3_L1 SHIFT // top inside
    #define R_B4_L1 CMD  // top outside
    #define R_B5_L1 {HSV_GREEN}  // side inside
    #define R_B6_L1 {HSV_RED}   // side outside
    #define R_B7_L1 CYCLE
    #define R_B8_L1 CYCLE

    // FUSION
    #define L_B1_L2 {HSV_WHITE}  // outside, lower big toe
    #define L_B2_L2 CMD // inside, upper big toe
    #define L_B3_L2 {HSV_WHITE}  // top inside
    #define L_B4_L2 {HSV_WHITE}  // top outside
    #define L_B5_L2 {HSV_GREEN} // side inside
    #define L_B6_L2 {HSV_RED}    // side outside
    #define L_B7_L2 CYCLE
    #define L_B8_L2 CYCLE
    
    #define R_B1_L2 {HSV_PINK}  // inside, upper big toe
    #define R_B2_L2 {HSV_WHITE} // outside, lower big toe
    #define R_B3_L2 {HSV_WHITE} // top inside
    #define R_B4_L2 {HSV_WHITE} // top outside
    #define R_B5_L2 {HSV_GREEN} // side inside
    #define R_B6_L2 {HSV_RED}  // side outside
    #define R_B7_L2 CYCLE
    #define R_B8_L2 CYCLE

    // MGMT
    #define L_B1_L3 {HSV_WHITE}  // outside, lower big toe
    #define L_B2_L3 {HSV_WHITE}  // inside, upper big toe
    #define L_B3_L3 {HSV_ORANGE} // top inside
    #define L_B4_L3 {HSV_RED}    // top outside
    #define L_B5_L3 {HSV_WHITE}  // side inside
    #define L_B6_L3 {HSV_WHITE}  // side outside
    #define L_B7_L3 CYCLE
    #define L_B8_L3 CYCLE
    
    #define R_B1_L3 {HSV_WHITE}  // inside, upper big toe
    #define R_B2_L3 {HSV_WHITE}  // outside, lower big toe
    #define R_B3_L3 {HSV_RED}    // top inside
    #define R_B4_L3 {HSV_ORANGE} // top outside
    #define R_B5_L3 {HSV_WHITE}  // side inside
    #define R_B6_L3 {HSV_WHITE}  // side outside
    #define R_B7_L3 CYCLE
    #define R_B8_L3 CYCLE
#endif

enum custom_keycodes {
    KC_CYCLE_LAYERS = QK_USER,
    KC_KB_DRAGSCROLL,
    KC_KB_ONESHOT_GUI,
    KC_KB_RECT,
};

// usb-hid config
typedef enum {
    _TIME = 0xAA, // random value that does not conflict with VIA, must match companion app
    _VOLUME,
    _LAYOUT,
    _MEDIA_ARTIST,
    _MEDIA_TITLE,
    _CYCLE_PEDAL_LAYERS = 0xBA,
    _LAYER_COLOUR,

    _RELAY_FROM_DEVICE = 0xCC,
    _RELAY_TO_DEVICE = 0xCD,
    _DIRECT_TO_HOST = 0xCE,
    _TOGGLE_DRAGSCROLL = 0xDD,
    _TOGGLE_ONESHOT_GUI = 0xDE,
    _TOGGLE_KB_RECT = 0xDF,
} hid_data_type;
