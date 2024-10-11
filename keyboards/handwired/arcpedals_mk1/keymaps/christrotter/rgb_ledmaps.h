// Copyright 2021 Mikael Manukyan <arm.localhost@gmail.com>
// Copyright 2023 Chris Trotter (@christrotter)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

#define LEDMAP( \
    LM_11, LM_12, RM_11, RM_12, \
    LM_21, LM_22, RM_21, RM_22, \
    LM_31, LM_32, RM_31, RM_32 \
) { \
    LM_11, LM_12, \
    LM_21, LM_22, \
    LM_31, LM_32, \
    RM_11, RM_12, \
    RM_21, RM_22, \
    RM_31, RM_32 \
}

typedef uint8_t ledmap[RGB_MATRIX_LED_COUNT][3];
extern const ledmap ledmaps[];

void set_rgb_ledmap(uint8_t first_led, uint8_t last_led, int val, int layer);
void set_rgb_range(uint8_t first_led, uint8_t last_led, int hue, int sat, int val);
void set_rgb_array(uint8_t ledArray[], int hue, int sat, int val);

void rgb_matrix_layers_enable(void);     // do we need this?
void rgb_matrix_layers_disable(void);    // do we need this?
bool rgb_matrix_indicators_keymap(void); // do we need this?
bool rgb_matrix_indicators_advanced_keymap(uint8_t led_min, uint8_t led_max);
