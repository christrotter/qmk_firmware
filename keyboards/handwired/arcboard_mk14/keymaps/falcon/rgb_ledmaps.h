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

#ifdef RGB_MATRIX_LEDMAPS_ENABLED

// clang-format off
#   define RGB_MATRIX_LAYOUT_LEDMAP( \
    LM_11, LM_12, LM_13, LM_14, LM_15, LM_16, LM_17,                    RM_11, RM_12, RM_13, RM_14, RM_15, RM_16, RM_17, \
    LM_21, LM_22, LM_23, LM_24, LM_25, LM_26, LM_27,                    RM_21, RM_22, RM_23, RM_24, RM_25, RM_26, RM_27, \
    LM_31, LM_32, LM_33, LM_34, LM_35, LM_36, LM_37,                    RM_31, RM_32, RM_33, RM_34, RM_35, RM_36, RM_37, \
    LM_41, LM_42, LM_43, LM_44, LM_45, LM_46, LM_47,                    RM_41, RM_42, RM_43, RM_44, RM_45, RM_46, RM_47, \
    LM_51, LM_52, LM_53, LM_54, LM_55, LM_56, LM_57,                    RM_51, RM_52, RM_53, RM_54, RM_55, RM_56, RM_57, \
                  LM_61, LM_62,                                                              RM_61, RM_62, \
                LT_76, LT_75, LT_74, LT_73, LT_72, LT_71, RT_71, RT_72, RT_73, RT_74, RT_75, RT_76 \
) \
{ \
    LM_11, LM_12, LM_13, LM_14, LM_15, LM_16, LM_17, \
    LM_21, LM_22, LM_23, LM_24, LM_25, LM_26, LM_27, \
    LM_31, LM_32, LM_33, LM_34, LM_35, LM_36, LM_37, \
    LM_41, LM_42, LM_43, LM_44, LM_45, LM_46, LM_47, \
    LM_51, LM_52, LM_53, LM_54, LM_55, LM_56, LM_57, \
    LM_61, LM_62, \
    LT_76, LT_75, LT_74, LT_73, LT_72, LT_71, \
    RM_11, RM_12, RM_13, RM_14, RM_15, RM_16, RM_17, \
    RM_21, RM_22, RM_23, RM_24, RM_25, RM_26, RM_27, \
    RM_31, RM_32, RM_33, RM_34, RM_35, RM_36, RM_37, \
    RM_41, RM_42, RM_43, RM_44, RM_45, RM_46, RM_47, \
    RM_51, RM_52, RM_53, RM_54, RM_55, RM_56, RM_57, \
    RM_61, RM_62, \
    RT_71, RT_72, RT_73, RT_74, RT_75, RT_76, \
}
// clang-format on
// no association keycode

typedef uint8_t ledmap[RGB_MATRIX_LED_COUNT][3];
extern const ledmap ledmaps[];
void set_layer_rgb(uint8_t led_min, uint8_t led_max, int layer);

#define LEDMAP_KEYS( LM_0, LM_1, LM_2, LM_3, LM_4, LM_5, LM_6, LM_7, LM_8, LM_9, LM_10, LM_11 ) { LM_0, LM_1, LM_2, LM_3, LM_4, LM_5, LM_6, LM_7, LM_8, LM_9, LM_10, LM_11 }
typedef uint8_t keysledmap[KEYS_LED_COUNT][3];
extern const keysledmap keysledmaps[];
void set_rgb_range_keys(uint8_t led_start, uint8_t led_last, int layer);




void rgb_matrix_layers_enable(void);
void rgb_matrix_layers_disable(void);

#    define HSV_MOONLANDER         5,   5, 255

// Just a handy defines to make our ledmaps look better
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


#endif  // RGB_MATRIX_LEDMAPS_ENABLED

bool rgb_matrix_indicators_keymap(void);
bool rgb_matrix_indicators_advanced_keymap(uint8_t led_min, uint8_t led_max);
