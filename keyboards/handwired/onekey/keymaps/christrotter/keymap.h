// Copyright 2023 Chris Trotter (@christrotter)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

#define XXX KC_NO
#define __LED__ KC_NO


// usb-hid config
typedef enum {
    _TIME = 0xAA, // random value that does not conflict with VIA, must match companion app
    _VOLUME,
    _LAYOUT,
    _MEDIA_ARTIST,
    _MEDIA_TITLE,
    _PEDAL_CYCLE_LAYERS = 0xBA,

    _RELAY_FROM_DEVICE = 0xCC,
    _RELAY_TO_DEVICE = 0xCD,
} hid_data_type;
