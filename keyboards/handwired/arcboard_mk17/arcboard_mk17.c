// Copyright 2023 Chris Trotter (@christrotter)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "arcboard_mk17.h"

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
        if (!(is_keyboard_left())) {
            init_ui();
        }
    #endif

    keyboard_post_init_user(); //_user should not be in the keyboard.c
}
