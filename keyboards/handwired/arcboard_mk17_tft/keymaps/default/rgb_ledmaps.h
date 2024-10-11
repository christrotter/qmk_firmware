/* Copyright 2021 Mikael Manukyan <arm.localhost@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
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

typedef uint8_t ledmap[RGB_MATRIX_LED_COUNT][3]; // ledmap is 'count of total leds' by 'hsv macro, i.e. 3 numbers'
extern const ledmap ledmaps[];
void set_rgb_range(uint8_t led_start, uint8_t led_last, int val, int layer);
void set_rgb_led(int index, int hue, int sat, int val);

void rgb_matrix_layers_enable(void);
void rgb_matrix_layers_disable(void);

bool rgb_matrix_indicators_keymap(void);
bool rgb_matrix_indicators_advanced_keymap(uint8_t led_min, uint8_t led_max);
