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

#if defined(RAW_ENABLE)
    // Raw-HID packet format shared with the mk3 peripherals.
    typedef struct PACKED {
        uint16_t source_id;
        uint8_t type;
        uint8_t type_id;
        uint8_t payload[16];
    } hid_msg_t;

    typedef enum {
        _APPSENSE   = 0x01,
        _LAYER      = 0x02,
        _ONESHOT    = 0x03,
        _DRAGSCROLL = 0x04,
        _WLED       = 0x05,
    } hid_types;

    typedef enum {
        _ONESHOT_SHIFT = 0x01,
        _ONESHOT_LGUI  = 0x02,
        _ONESHOT_LCTRL = 0x03,
        _ONESHOT_LALT  = 0x04,
    } hid_oneshot_ids;

    typedef enum {
        _APP_OTHER  = 0x00,
        _APP_VSCODE = 0x01,
        _APP_CHROME = 0x02,
        _APP_FUSION = 0x03,
        _APP_KICAD  = 0x04,
    } hid_appsense_apps;

    typedef enum {
        _TOGGLE_KB_RECT = 0xDF,
    } hid_layers;
#endif // RAW_ENABLE