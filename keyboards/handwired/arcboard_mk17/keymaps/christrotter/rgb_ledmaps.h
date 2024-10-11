// Copyright 2021 Mikael Manukyan <arm.localhost@gmail.com>
// Copyright 2023 Chris Trotter (@christrotter)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

#define LEDMAP( \
    LM_11, LM_12, LM_13, LM_14, LM_15, LM_16,     RM_11, RM_12, RM_13, RM_14, RM_15, RM_16, \
    LM_21, LM_22, LM_23, LM_24, LM_25, LM_26,     RM_21, RM_22, RM_23, RM_24, RM_25, RM_26, \
    LM_31, LM_32, LM_33, LM_34, LM_35, LM_36,     RM_31, RM_32, RM_33, RM_34, RM_35, RM_36, \
    LM_41, LM_42, LM_43, LM_44, LM_45, LM_46,     RM_41, RM_42, RM_43, RM_44, RM_45, RM_46, \
    LT_51, LT_52, LT_53, LT_54, LT_55, FL_B0,     RT_51, RT_52, RT_53, RT_54, RT_55, FL_B2, \
    DP_01, DP_02, DP_03, DP_04, DP_05, FL_B1,     DP_11, DP_12, DP_13, DP_14, DP_15, FL_B3 \
) { \
    LM_11, LM_12, LM_13, LM_14, LM_15, LM_16, \
    LM_21, LM_22, LM_23, LM_24, LM_25, LM_26, \
    LM_31, LM_32, LM_33, LM_34, LM_35, LM_36, \
    LM_41, LM_42, LM_43, LM_44, LM_45, LM_46, \
    LT_51, LT_52, LT_53, LT_54, LT_55, FL_B0, \
    DP_01, DP_02, DP_03, DP_04, DP_05, FL_B1, \
    RM_11, RM_12, RM_13, RM_14, RM_15, RM_16, \
    RM_21, RM_22, RM_23, RM_24, RM_25, RM_26, \
    RM_31, RM_32, RM_33, RM_34, RM_35, RM_36, \
    RM_41, RM_42, RM_43, RM_44, RM_45, RM_46, \
    RT_51, RT_52, RT_53, RT_54, RT_55, FL_B2, \
    DP_11, DP_12, DP_13, DP_14, DP_15, FL_B3 \
}

typedef uint8_t ledmap[RGB_MATRIX_LED_COUNT][3];
extern const ledmap ledmaps[];

void set_rgb_ledmap(uint8_t first_led, uint8_t last_led, int val, int layer);
void set_rgb_range(uint8_t first_led, uint8_t last_led, int hue, int sat, int val);

void rgb_matrix_layers_enable(void);     // do we need this?
void rgb_matrix_layers_disable(void);    // do we need this?
