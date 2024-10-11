// Copyright 2021 Mikael Manukyan <arm.localhost@gmail.com>
// Copyright 2023 Chris Trotter (@christrotter)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

// these need to match the rgb matrix led count/layout
// 
#define LEDMAP( \
    LM_101, LM_102, LM_103, \
    LM_111, LM_112, LM_113, \
    LM_121, LM_122, LM_123, \
    LM_131, LM_132, LM_133, \
    LM_141, LM_142, LM_143, \
    LM_151, LM_152, LM_153, \
    LM_161, LM_162, LM_163, \
    LM_171, LM_172, LM_173, \
    LM_181, LM_182, LM_183, \
    LM_191, LM_192, LM_193, \
    RM_101, RM_102, RM_103, \
    RM_111, RM_112, RM_113, \
    RM_121, RM_122, RM_123, \
    RM_131, RM_132, RM_133, \
    RM_141, RM_142, RM_143, \
    RM_151, RM_152, RM_153, \
    RM_161, RM_162, RM_163, \
    RM_171, RM_172, RM_173, \
    RM_181, RM_182, RM_183, \
    RM_191, RM_192, RM_193 \
) { \
    LM_101, LM_102, LM_103, \
    LM_111, LM_112, LM_113, \
    LM_121, LM_122, LM_123, \
    LM_131, LM_132, LM_133, \
    LM_141, LM_142, LM_143, \
    LM_151, LM_152, LM_153, \
    LM_161, LM_162, LM_163, \
    LM_171, LM_172, LM_173, \
    LM_181, LM_182, LM_183, \
    LM_191, LM_192, LM_193, \
    RM_101, RM_102, RM_103, \
    RM_111, RM_112, RM_113, \
    RM_121, RM_122, RM_123, \
    RM_131, RM_132, RM_133, \
    RM_141, RM_142, RM_143, \
    RM_151, RM_152, RM_153, \
    RM_161, RM_162, RM_163, \
    RM_171, RM_172, RM_173, \
    RM_181, RM_182, RM_183, \
    RM_191, RM_192, RM_193 \
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
