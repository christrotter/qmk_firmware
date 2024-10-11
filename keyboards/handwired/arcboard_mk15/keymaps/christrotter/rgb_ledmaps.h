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

#define HSV_MOONLANDER 5, 5, 255
// Just a handy defines to make our ledmaps look better
// braces work here because
#    define RED \
        { HSV_RED }
#    define CORAL \
        { HSV_CORAL }
#    define ORANGE \
        { HSV_ORANGE }
#    define GOLDEN \
        { HSV_GOLDENROD }
#    define GOLD \
        { HSV_GOLD }
#    define YELLOW \
        { HSV_YELLOW }
#    define CHART \
        { HSV_CHARTREUSE }
#    define GREEN \
        { HSV_GREEN }
#    define SPRING \
        { HSV_SPRINGGREEN }
#    define TURQ \
        { HSV_TURQUOISE }
#    define TEAL \
        { HSV_TEAL }
#    define CYAN \
        { HSV_CYAN }
#    define AZURE \
        { HSV_AZURE }
#    define BLUE \
        { HSV_BLUE }
#    define PURPLE \
        { HSV_PURPLE }
#    define MAGENT \
        { HSV_MAGENTA }
#    define PINK \
        { HSV_PINK }
#    define BLACK \
        { HSV_BLACK }
#    define WHITE \
        { HSV_MOONLANDER }

#define LEDMAP( \
    LM_11, LM_12, LM_13, LM_14, LM_15, LM_16,     RM_11, RM_12, RM_13, RM_14, RM_15, RM_16, \
    LM_21, LM_22, LM_23, LM_24, LM_25, LM_26,     RM_21, RM_22, RM_23, RM_24, RM_25, RM_26, \
    LM_31, LM_32, LM_33, LM_34, LM_35, LM_36,     RM_31, RM_32, RM_33, RM_34, RM_35, RM_36, \
    LM_41, LM_42, LM_43, LM_44, LM_45, LM_46,     RM_41, RM_42, RM_43, RM_44, RM_45, RM_46, \
    LT_51, LT_52, LT_53, LT_54, LT_55, LT_56,     RT_51, RT_52, RT_53, RT_54, RT_55, RT_56, \
    FL_01, FL_02, FL_03, FL_04, FL_05, FL_06,     FR_01, FR_02, FR_03, FR_04, FR_05, FR_06, \
    FL_07, FL_08, FL_09, FL_10, FL_11, FL_12,     FR_07, FR_08, FR_09, FR_10, FR_11, FR_12, \
    IL_01, IL_02, IL_03, IL_04, IL_05, IL_06,     IR_01, IR_02, IR_03, IR_04, IR_05, IR_06, \
    IL_07, IL_08, IL_09, IL_10, IL_11, IL_12,     IR_07, IR_08, IR_09, IR_10, IR_11, IR_12, \
    IL_13, IL_14,                                 IR_13, IR_14 \
) { \
    LM_11, LM_12, LM_13, LM_14, LM_15, LM_16, \
    LM_21, LM_22, LM_23, LM_24, LM_25, LM_26, \
    LM_31, LM_32, LM_33, LM_34, LM_35, LM_36, \
    LM_41, LM_42, LM_43, LM_44, LM_45, LM_46, \
    LT_51, LT_52, LT_53, LT_54, LT_55, LT_56, \
    FL_01, FL_02, FL_03, FL_04, FL_05, FL_06, \
    FL_07, FL_08, FL_09, FL_10, FL_11, FL_12, \
    IL_01, IL_02, IL_03, IL_04, IL_05, IL_06, \
    IL_07, IL_08, IL_09, IL_10, IL_11, IL_12, \
    IL_13, IL_14, \
    RM_11, RM_12, RM_13, RM_14, RM_15, RM_16, \
    RM_21, RM_22, RM_23, RM_24, RM_25, RM_26, \
    RM_31, RM_32, RM_33, RM_34, RM_35, RM_36, \
    RM_41, RM_42, RM_43, RM_44, RM_45, RM_46, \
    RT_51, RT_52, RT_53, RT_54, RT_55, RT_56, \
    FR_01, FR_02, FR_03, FR_04, FR_05, FR_06, \
    FR_07, FR_08, FR_09, FR_10, FR_11, FR_12, \
    IR_01, IR_02, IR_03, IR_04, IR_05, IR_06, \
    IR_07, IR_08, IR_09, IR_10, IR_11, IR_12, \
    IR_13, IR_14 \
}
typedef uint8_t ledmap[RGB_MATRIX_LED_COUNT][3];
extern const ledmap ledmaps[];
void set_rgb_range(uint8_t led_start, uint8_t led_last, int val, int layer);

void rgb_matrix_layers_enable(void);
void rgb_matrix_layers_disable(void);

bool rgb_matrix_indicators_keymap(void);
bool rgb_matrix_indicators_advanced_keymap(uint8_t led_min, uint8_t led_max);
