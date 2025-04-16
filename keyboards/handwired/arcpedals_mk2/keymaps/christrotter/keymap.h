// Copyright 2023 Chris Trotter (@christrotter)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

#if defined(CONSOLE_ENABLE)
    // #define DEBUG_MATRIX_SCAN_RATE
#endif

#define XXX KC_NO
#define __LED__ KC_NO

#define KC_CHRMCYC LGUI(KC_TILDE)

// single button to reset layer
#define KC_LAYRST TO(_QWERTY)

#if defined(RGB_MATRIX_LEDMAPS_ENABLED)
    // note: these cannot have braces e.g. #define HRM_SFT {GREEN} blows up the evaluation of the [3] part of the int[KEYS_COUNT][3]; sees it as one item
    #define ___n___ {0, 0, 0}
    #define LAYER_SCROLL SPRING
    #define LAYER_MOUSE PINK
    #define LAYER_FUSION ORANGE
    #define LAYER_MGMT RED
#endif

// usb-hid config
typedef enum {
    _TIME = 0xAA, // random value that does not conflict with VIA, must match companion app
    _VOLUME,
    _LAYOUT,
    _MEDIA_ARTIST,
    _MEDIA_TITLE,
    _PEDAL_CYCLE_LAYERS = 0xBA,

    _RELAY_FROM_DEVICE = 0xCC,
    _RELAY_TO_DEVICE,
} hid_data_type;
