// Copyright 2021 Mikael Manukyan <arm.localhost@gmail.com>
// Copyright 2023 Chris Trotter (@christrotter)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

// the naming here is arbitrary.
// r30-35 = top row somehow...
// r20-25 = homerow
//  3,  1, 0, 6, 5, 4
// so today we have
// col3,  col2,  col1, col0, col7, col6, col5, col4
// GREEN,   TOG_NAV,   TOG_SYM, ENTER,   SPACE, BLUE, CYAN, GREEN
/*
0 cyan
1 pink
2 chart
3 green
4 green
5 cyan
6 blue 
7 green
*/
#define LEDMAP( \
    L_50, L_51, L_52, L_53, L_54, L_55, L_56, L_57, L_58, L_59,     R_50, R_51, R_52, R_53, R_54, R_55, R_56, R_57, R_58, R_59, \
    L_40, L_41, L_42, L_43, L_44, L_45,                             R_40, R_41, R_42, R_43, R_44, R_45, \
    L_30, L_31, L_32, L_33, L_34, L_35,                             R_30, R_31, R_32, R_33, R_34, R_35, \
    L_20, L_21, L_22, L_23, L_24, L_25,                             R_20, R_21, R_22, R_23, R_24, R_25, \
    L_10, L_11, L_12, L_13, L_14, L_15,                             R_10, R_11, R_12, R_13, R_14, R_15, \
    L_00, L_01, L_02, L_03, L_04, L_05,                             R_00, R_01, R_02, R_03, R_04, R_05, \
    L_36, L_37, L_38, L_39, L_26, L_27, L_28, L_29,                 R_36, R_37, R_38, R_39, R_26, R_27, R_28, R_29 \
) { \
    L_30, L_20, L_10, L_50, L_40, \
    L_31, L_21, L_11, L_51, L_41, \
    L_32, L_22, L_12, L_52, L_42, \
    L_33, L_23, L_13, L_53, L_43, \
    L_34, L_24, L_14, L_54, L_44, \
    L_35, L_25, L_15, L_55, L_45, \
    L_00, L_01, L_02, L_03, L_04, L_05, \
    L_36, L_37, L_38, L_39, L_26, L_27, L_28, L_29, \
    L_56, L_57, L_58, L_59, \
    R_30, R_20, R_10, R_50, R_40, \
    R_31, R_21, R_11, R_51, R_41, \
    R_32, R_22, R_12, R_52, R_42, \
    R_33, R_23, R_13, R_53, R_43, \
    R_34, R_24, R_14, R_54, R_44, \
    R_35, R_25, R_15, R_55, R_45, \
    R_00, R_01, R_02, R_03, R_04, R_05, \
    R_36, R_37, R_38, R_39, R_26, R_27, R_28, R_29, \
    R_56, R_57, R_58, R_59 \
}

typedef uint8_t ledmap[RGB_MATRIX_LED_COUNT][3];
extern const ledmap ledmaps[];

void set_rgb_ledmap(uint16_t first_led, uint16_t last_led, int val, int layer);
void set_rgb_range(uint16_t first_led, uint16_t last_led, int hue, int sat, int val, int val_override);

void rgb_matrix_layers_enable(void);     // do we need this?
void rgb_matrix_layers_disable(void);    // do we need this?
