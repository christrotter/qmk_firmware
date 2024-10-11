// Copyright 2023 christrotter (@christrotter)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "arcboard_mk17_tft_sm.h"
#include <color.h>
#include "print.h"

////  QUANTUM PAINTER SECTION  ////
#if defined(QUANTUM_PAINTER_ENABLE)
    #include "qp_st7789.h"
    #include <qp.h>
    __attribute__((weak)) void draw_ui_user(void) {}
    __attribute__((weak)) void init_ui(void) {}
    extern painter_device_t display;
#endif

void keyboard_post_init_kb(void) {
    #if defined(QUANTUM_PAINTER_ENABLE)
        init_ui();
    #endif
    #if defined(POINTING_DEVICE_ENABLE)
        pointing_device_set_cpi_on_side(true, LEFT_PMW_CPI);
        pointing_device_set_cpi_on_side(false, RIGHT_PMW_CPI);
    #endif
    keyboard_post_init_user(); //_user should not be in the keyboard.c
}

// trying to shrink to match matrix
#if defined(RGB_MATRIX_ENABLE) || defined(RGB_MATRIX_LEDMAPS_ENABLED)
led_config_t g_led_config = {
    {
        // split kb
        { 0,  1  }, // left keys
        { 2,  3  }  // right keys
    },
    {
        { 102,   0 }, {  81,   0 },{ 102,   0 }, {  81,   0 },
        { 102,   0 }, {  81,   0 },{ 102,   0 }, {  81,   0 },
        { 102,   0 }, {  81,   0 },{ 102,   0 }, {  81,   0 }, {  81,   0 }, {  81,   0 }
    },
    {
            4, 4, 4, 4, 1, 2, 3,
            4, 4, 4, 4, 1, 2, 3
    }
};
#endif
