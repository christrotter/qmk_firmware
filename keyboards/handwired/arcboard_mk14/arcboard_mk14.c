// Copyright 2022 Chris Trotter (@christrotter)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "arcboard_mk14.h"
#include "string.h"
#include <hal.h>
#include "spi_master.h"

// this is ref'd by something deep in the rgbmatrix
#if defined(RGB_MATRIX_ENABLE) || defined(RGB_MATRIX_LEDMAPS_ENABLED)
    led_config_t g_led_config = {
    // Key Matrix to LED Index
    {
        { 0 }
    },
    // LED Index to Physical Position // afaik this is only for stuff like matrix animations
    {
        { 102,   0 }, { 102,   0 }, { 102,   0 }, { 102,   0 }, { 102,   0 }, { 102,   0 }, { 102,   0 }, { 102,   0 }, { 102,   0 }, { 102,   0 }, { 102,   0 }, { 102,   0 }
    },
    // LED type bit mask - 4 is per-key, 8 is indicator
    {
            4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4
    }
    };
#endif

void keyboard_post_init_kb(void) {
    keyboard_post_init_user(); //_user should not be in the keyboard.c
}

void housekeeping_task_kb(void) {
}

// Forward declare RP2040 SDK declaration.
void gpio_init(uint gpio);

void matrix_slave_scan_keymap(void);
