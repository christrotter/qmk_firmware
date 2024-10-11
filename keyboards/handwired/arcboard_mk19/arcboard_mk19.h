// Copyright 2023 Chris Trotter (@christrotter)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"
#include "color.h"
#include QMK_KEYBOARD_H

#define _MACROS _MOUSE

#define HSV_MOONLANDER 5, 5, 255
// Just a handy defines to make our ledmaps look better
// braces work here because
#define RED \
    { HSV_RED }
#define CORAL \
    { HSV_CORAL }
#define ORANGE \
    { HSV_ORANGE }
#define GOLDEN \
    { HSV_GOLDENROD }
#define GOLD \
    { HSV_GOLD }
#define YELLOW \
    { HSV_YELLOW }
#define CHART \
    { HSV_CHARTREUSE }
#define GREEN \
    { HSV_GREEN }
#define SPRING \
    { HSV_SPRINGGREEN }
#define TURQ \
    { HSV_TURQUOISE }
#define TEAL \
    { HSV_TEAL }
#define CYAN \
    { HSV_CYAN }
#define AZURE \
    { HSV_AZURE }
#define BLUE \
    { HSV_BLUE }
#define PURPLE \
    { HSV_PURPLE }
#define MAGENT \
    { HSV_MAGENTA }
#define PINK \
    { HSV_PINK }
#define BLACK \
    { HSV_BLACK }
#define WHITE \
    { HSV_MOONLANDER }

// indicator colours
#define INDICATOR_BG \
    HSV_CYAN
#define INDICATOR_SHIFT \
    HSV_GREEN

enum userspace_layers {
    _QWERTY             = 0,
    FIRST_DEFAULT_LAYER = 0,
    _MOUSE,
    _SYMBOLS,
    _NAV,
};

#if defined(RGB_MATRIX_LEDMAPS_ENABLED)
    #include "rgb_ledmaps.h"
#endif

#if defined(POINTING_DEVICE_ENABLE)
    enum board_keycodes {
        BOARD_SAFE_RANGE,
    };
#endif // POINTING_DEVICE_ENABLE

void keyboard_post_init_transport_sync(void);
void housekeeping_task_transport_sync(void);

void matrix_init_sub_kb(void);
void matrix_scan_sub_kb(void);
bool process_record_user_rgb_matrix(uint16_t keycode, keyrecord_t *record); //_user should not be in the keyboard.c
