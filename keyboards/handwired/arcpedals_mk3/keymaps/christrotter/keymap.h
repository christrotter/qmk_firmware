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
    #define LAYER_SCROLL SPRING
    #define LAYER_MOUSE PINK
    #define LAYER_FUSION ORANGE
    #define LAYER_MGMT RED

    #define BLANK {HSV_WHITE}

    #define L_B1_L0 {HSV_BLUE}
    #define L_B2_L0 {HSV_PURPLE}
    #define L_B3_L0 {HSV_GREEN}
    #define L_B4_L0 {HSV_YELLOW}
    #define L_B5_L0 {HSV_PINK}
    #define L_B6_L0 {HSV_RED}
    #define L_B7_L0 {HSV_SPRINGGREEN}
    #define L_B8_L0 {HSV_SPRINGGREEN}
    
    #define R_B1_L0 {HSV_PURPLE}
    #define R_B2_L0 {HSV_BLUE}
    #define R_B3_L0 {HSV_GREEN}
    #define R_B4_L0 {HSV_YELLOW}
    #define R_B5_L0 {HSV_GREEN}
    #define R_B6_L0 {HSV_PINK}
    #define R_B7_L0 {HSV_SPRINGGREEN}
    #define R_B8_L0 {HSV_SPRINGGREEN}
    
    #define L_B1_L1 {HSV_WHITE}
    #define L_B2_L1 {HSV_WHITE}
    #define L_B3_L1 {HSV_WHITE}
    #define L_B4_L1 {HSV_WHITE}
    #define L_B5_L1 {HSV_WHITE}
    #define L_B6_L1 {HSV_WHITE}
    #define L_B7_L1 {HSV_SPRINGGREEN}
    #define L_B8_L1 {HSV_SPRINGGREEN}
    
    #define R_B1_L1 {HSV_WHITE}
    #define R_B2_L1 {HSV_WHITE}
    #define R_B3_L1 {HSV_WHITE}
    #define R_B4_L1 {HSV_WHITE}
    #define R_B5_L1 {HSV_WHITE}
    #define R_B6_L1 {HSV_WHITE}
    #define R_B7_L1 {HSV_SPRINGGREEN}
    #define R_B8_L1 {HSV_SPRINGGREEN}
    
    #define L_B1_L2 {HSV_WHITE}
    #define L_B2_L2 {HSV_WHITE}
    #define L_B3_L2 {HSV_ORANGE}
    #define L_B4_L2 {HSV_RED}
    #define L_B5_L2 {HSV_WHITE}
    #define L_B6_L2 {HSV_WHITE}
    #define L_B7_L2 {HSV_SPRINGGREEN}
    #define L_B8_L2 {HSV_SPRINGGREEN}
    
    #define R_B1_L2 {HSV_WHITE}
    #define R_B2_L2 {HSV_WHITE}
    #define R_B3_L2 {HSV_RED}
    #define R_B4_L2 {HSV_RED}
    #define R_B5_L2 {HSV_WHITE}
    #define R_B6_L2 {HSV_WHITE}
    #define R_B7_L2 {HSV_SPRINGGREEN}
    #define R_B8_L2 {HSV_SPRINGGREEN}
#endif


