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
    #define LAYER_0_COLOUR HSV_WHITE         // qwerty
    #define LAYER_1_COLOUR HSV_ORANGE       // mouse
    #define LAYER_2_COLOUR HSV_PINK        // symbols  
    #define LAYER_3_COLOUR HSV_CHARTREUSE   // nav
    #define LAYER_4_COLOUR HSV_RED          // rect
    #define LAYER_5_COLOUR HSV_PURPLE       // vscode
    #define LAYER_6_COLOUR HSV_ORANGE       // fusion
    #define LAYER_7_COLOUR HSV_CYAN       // chrome
    #define LAYER_8_COLOUR HSV_PINK       // chrome
    #define LAYER_9_COLOUR HSV_RED          // mgmt
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

    // MOUSE
    #define L_B1_L1 {HSV_RED}      // outside, lower big toe
    #define L_B2_L1 {HSV_RED}       // inside, upper big toe
    #define L_B3_L1 {HSV_PURPLE} // top inside
    #define L_B4_L1 {HSV_PURPLE} // top outside
    #define L_B5_L1 {HSV_GREEN} // side inside      
    #define L_B6_L1 {HSV_BLUE}  // side outside
    #define L_B7_L1 CYCLE
    #define L_B8_L1 CYCLE
    #define R_B1_L1 {HSV_GREEN}     // inside, upper big toe
    #define R_B2_L1 {HSV_GREEN}      // outside, lower big toe
    #define R_B3_L1 {HSV_PURPLE} // top inside
    #define R_B4_L1 {HSV_PURPLE} // top outside
    #define R_B5_L1 {HSV_BLUE}  // side inside
    #define R_B6_L1 {HSV_GREEN} // side outside
    #define R_B7_L1 CYCLE
    #define R_B8_L1 CYCLE

    // SYMBOLS
    #define L_B1_L2 {HSV_RED}      // outside, lower big toe
    #define L_B2_L2 {HSV_RED}       // inside, upper big toe
    #define L_B3_L2 {HSV_YELLOW} // top inside
    #define L_B4_L2 {HSV_YELLOW} // top outside
    #define L_B5_L2 {HSV_GREEN} // side inside
    #define L_B6_L2 {HSV_BLUE}  // side outside
    #define L_B7_L2 CYCLE
    #define L_B8_L2 CYCLE
    #define R_B1_L2 {HSV_GREEN}     // inside, upper big toe
    #define R_B2_L2 {HSV_GREEN}      // outside, lower big toe
    #define R_B3_L2 {HSV_YELLOW} // top inside
    #define R_B4_L2 {HSV_YELLOW} // top outside
    #define R_B5_L2 {HSV_BLUE}  // side inside
    #define R_B6_L2 {HSV_GREEN} // side outside
    #define R_B7_L2 CYCLE
    #define R_B8_L2 CYCLE

    // NAV
    #define L_B1_L3 {HSV_RED}      // outside, lower big toe
    #define L_B2_L3 {HSV_RED}       // inside, upper big toe
    #define L_B3_L3 {HSV_ORANGE} // top inside
    #define L_B4_L3 {HSV_ORANGE} // top outside
    #define L_B5_L3 {HSV_GREEN} // side inside
    #define L_B6_L3 {HSV_BLUE}  // side outside
    #define L_B7_L3 CYCLE
    #define L_B8_L3 CYCLE
    #define R_B1_L3 {HSV_GREEN}     // inside, upper big toe
    #define R_B2_L3 {HSV_GREEN}      // outside, lower big toe
    #define R_B3_L3 {HSV_ORANGE} // top inside
    #define R_B4_L3 {HSV_ORANGE} // top outside
    #define R_B5_L3 {HSV_BLUE}  // side inside
    #define R_B6_L3 {HSV_GREEN} // side outside
    #define R_B7_L3 CYCLE
    #define R_B8_L3 CYCLE

    // RECT
    #define L_B1_L4 {HSV_RED}      // outside, lower big toe
    #define L_B2_L4 {HSV_RED}       // inside, upper big toe
    #define L_B3_L4 {HSV_YELLOW} // top inside
    #define L_B4_L4 {HSV_YELLOW} // top outside
    #define L_B5_L4 {HSV_GREEN} // side inside
    #define L_B6_L4 {HSV_BLUE}  // side outside
    #define L_B7_L4 CYCLE
    #define L_B8_L4 CYCLE
    #define R_B1_L4 {HSV_GREEN}     // inside, upper big toe
    #define R_B2_L4 {HSV_GREEN}      // outside, lower big toe
    #define R_B3_L4 {HSV_YELLOW} // top inside
    #define R_B4_L4 {HSV_YELLOW} // top outside
    #define R_B5_L4 {HSV_BLUE}  // side inside
    #define R_B6_L4 {HSV_GREEN} // side outside
    #define R_B7_L4 CYCLE
    #define R_B8_L4 CYCLE

    // VSCODE
    #define L_B1_L5 {HSV_RED}      // outside, lower big toe
    #define L_B2_L5 {HSV_RED}       // inside, upper big toe
    #define L_B3_L5 {HSV_PURPLE} // top inside
    #define L_B4_L5 {HSV_PURPLE} // top outside
    #define L_B5_L5 {HSV_GREEN} // side inside
    #define L_B6_L5 {HSV_BLUE}  // side outside
    #define L_B7_L5 CYCLE
    #define L_B8_L5 CYCLE
    #define R_B1_L5 {HSV_GREEN}     // inside, upper big toe
    #define R_B2_L5 {HSV_GREEN}      // outside, lower big toe
    #define R_B3_L5 {HSV_PURPLE} // top inside
    #define R_B4_L5 {HSV_PURPLE} // top outside
    #define R_B5_L5 {HSV_BLUE}  // side inside
    #define R_B6_L5 {HSV_GREEN} // side outside
    #define R_B7_L5 CYCLE
    #define R_B8_L5 CYCLE

    // FUSION
    #define L_B1_L6 {HSV_WHITE}  // outside, lower big toe
    #define L_B2_L6 CMD // inside, upper big toe
    #define L_B3_L6 {HSV_WHITE}  // top inside
    #define L_B4_L6 {HSV_WHITE}  // top outside
    #define L_B5_L6 {HSV_GREEN} // side inside
    #define L_B6_L6 {HSV_RED}    // side outside
    #define L_B7_L6 CYCLE
    #define L_B8_L6 CYCLE
    
    #define R_B1_L6 {HSV_PINK}  // inside, upper big toe
    #define R_B2_L6 {HSV_WHITE} // outside, lower big toe
    #define R_B3_L6 {HSV_WHITE} // top inside
    #define R_B4_L6 {HSV_WHITE} // top outside
    #define R_B5_L6 {HSV_GREEN} // side inside
    #define R_B6_L6 {HSV_RED}  // side outside
    #define R_B7_L6 CYCLE
    #define R_B8_L6 CYCLE

    // CHROME
    #define L_B1_L7 {HSV_WHITE}  // outside, lower big toe
    #define L_B2_L7 CMD // inside, upper big toe
    #define L_B3_L7 {HSV_WHITE}  // top inside
    #define L_B4_L7 {HSV_WHITE}  // top outside
    #define L_B5_L7 {HSV_GREEN} // side inside
    #define L_B6_L7 {HSV_RED}    // side outside
    #define L_B7_L7 CYCLE
    #define L_B8_L7 CYCLE
    
    #define R_B1_L7 {HSV_PINK}  // inside, upper big toe
    #define R_B2_L7 {HSV_WHITE} // outside, lower big toe
    #define R_B3_L7 {HSV_WHITE} // top inside
    #define R_B4_L7 {HSV_WHITE} // top outside
    #define R_B5_L7 {HSV_GREEN} // side inside
    #define R_B6_L7 {HSV_RED}  // side outside
    #define R_B7_L7 CYCLE
    #define R_B8_L7 CYCLE

    // KICAD
    #define L_B1_L8 {HSV_WHITE}  // outside, lower big toe
    #define L_B2_L8 {HSV_PINK}  // inside, upper big toe
    #define L_B3_L8 {HSV_WHITE} // top inside
    #define L_B4_L8 {HSV_WHITE}    // top outside
    #define L_B5_L8 {HSV_WHITE}  // side inside
    #define L_B6_L8 {HSV_WHITE}  // side outside
    #define L_B7_L8 CYCLE
    #define L_B8_L8 CYCLE
    
    #define R_B1_L8 {HSV_PINK}  // inside, upper big toe
    #define R_B2_L8 {HSV_WHITE}  // outside, lower big toe
    #define R_B3_L8 {HSV_WHITE}    // top inside
    #define R_B4_L8 {HSV_WHITE} // top outside
    #define R_B5_L8 {HSV_WHITE}  // side inside
    #define R_B6_L8 {HSV_WHITE}  // side outside
    #define R_B7_L8 CYCLE
    #define R_B8_L8 CYCLE

    // MGMT
    #define L_B1_L9 {HSV_WHITE}  // outside, lower big toe
    #define L_B2_L9 {HSV_WHITE}  // inside, upper big toe
    #define L_B3_L9 {HSV_ORANGE} // top inside
    #define L_B4_L9 {HSV_RED}    // top outside
    #define L_B5_L9 {HSV_WHITE}  // side inside
    #define L_B6_L9 {HSV_WHITE}  // side outside
    #define L_B7_L9 CYCLE
    #define L_B8_L9 CYCLE
    
    #define R_B1_L9 {HSV_WHITE}  // inside, upper big toe
    #define R_B2_L9 {HSV_WHITE}  // outside, lower big toe
    #define R_B3_L9 {HSV_ORANGE}    // top inside
    #define R_B4_L9 {HSV_RED} // top outside
    #define R_B5_L9 {HSV_WHITE}  // side inside
    #define R_B6_L9 {HSV_WHITE}  // side outside
    #define R_B7_L9 CYCLE
    #define R_B8_L9 CYCLE
#endif

enum custom_keycodes {
    KC_CYCLE_LAYERS = QK_USER,
    KC_KB_DRAGSCROLL,
    KC_KB_ONESHOT_GUI,
    KC_KB_RECT,
};

#if defined(RAW_ENABLE)
    // raw-hid config
    typedef struct PACKED {
        uint16_t source_id;  // first two bytes == always identifier
        uint8_t type;        // 1 byte for type
        uint8_t type_id;     // 1 byte for type id
        uint8_t payload[16]; // takes up the rest of the bytes you send; 16 cuz nice number, can be up to 26
    } hid_msg_t;
    
    typedef enum {
        _APPSENSE   = 0x01,
        _LAYER      = 0x02,
        _ONESHOT    = 0x03,
        _DRAGSCROLL = 0x04,
        _WLED       = 0x05,
    } hid_types;
    
    typedef enum {
        _ONESHOT_SHIFT = 0x01,
        _ONESHOT_LGUI  = 0x02,
        _ONESHOT_LCTRL = 0x03,
        _ONESHOT_LALT  = 0x04,
    } hid_oneshot_ids;
    
    typedef enum {
        _APP_OTHER  = 0x00,
        _APP_VSCODE = 0x01,
        _APP_CHROME = 0x02,
        _APP_FUSION = 0x03,
        _APP_KICAD = 0x04,
    } hid_appsense_apps;
    
    typedef enum {
        _CYCLE_PEDAL_LAYERS = 0xBA,
    } hid_commands;
    
    // refactor this code to use the native layers...
    typedef enum {
        _TOGGLE_KB_RECT = 0xDF,
    } hid_layers;
#endif // RAW_ENABLE
