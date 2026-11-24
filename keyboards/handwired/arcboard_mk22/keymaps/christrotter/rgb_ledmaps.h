// Copyright 2021 Mikael Manukyan <arm.localhost@gmail.com>
// Copyright 2023 Chris Trotter (@christrotter)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

// takes colours laid out like the keymap (key rows top to bottom, then thumbs) and reorders them into ws2812 chain order
#define LEDMAP( \
    L_40, L_41, L_42, L_43, L_44, L_45,                             R_40, R_41, R_42, R_43, R_44, R_45, \
    L_30, L_31, L_32, L_33, L_34, L_35,                             R_30, R_31, R_32, R_33, R_34, R_35, \
    L_20, L_21, L_22, L_23, L_24, L_25,                             R_20, R_21, R_22, R_23, R_24, R_25, \
    L_10, L_11, L_12, L_13, L_14, L_15,                             R_10, R_11, R_12, R_13, R_14, R_15, \
    L_00, L_01, L_02, L_03, L_04,                                   R_00, R_01, R_02, R_03, R_04  \
) { \
    L_35, L_25, L_15, L_45, \
    L_34, L_24, L_14, L_44, \
    L_33, L_23, L_13, L_43, \
    L_32, L_22, L_12, L_42, \
    L_31, L_21, L_11, L_41, \
    L_30, L_20, L_10, L_40, \
    L_04, L_03, L_02, L_01, L_00, \
    R_30, R_20, R_10, R_40, \
    R_31, R_21, R_11, R_41, \
    R_32, R_22, R_12, R_42, \
    R_33, R_23, R_13, R_43, \
    R_34, R_24, R_14, R_44, \
    R_35, R_25, R_15, R_45, \
    R_04, R_03, R_02, R_01, R_00 \
}

#define ___t___ {255, 255} // Transparent color that inherits from lower layers

typedef uint8_t ledmap[RGB_MATRIX_LED_COUNT][3];
extern const ledmap ledmaps[];

void set_rgb_ledmap(uint16_t start, uint16_t count, uint8_t val);
void set_rgb_range(uint16_t start, uint16_t count, hsv_t hsv, uint8_t val);
