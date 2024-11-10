// Copyright 2023 Chris Trotter (@christrotter)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#undef TAPPING_TERM
#define TAPPING_TERM 225            // time (in ms) for a tap to become a hold
#define TAP_CHECK TAPPING_TERM
#define PERMISSIVE_HOLD

#undef TAPPING_TOGGLE
#define TAPPING_TOGGLE 2
#define ONESHOT_TAP_TOGGLE 2        /* Tapping this number of times holds the key until tapped once again. */
#define ONESHOT_TIMEOUT 2000        /* Time (in ms) before the one shot key is released */
#define CUSTOM_KEYCODES

#if defined(RGB_MATRIX_LEDMAPS_ENABLED)
    #define RGB_INDICATOR_BRIGHTNESS 100
    #define RGB_LEDMAP_BRIGHTNESS 100

    #define RGB_START_LEDMAP_LEFT 0
    #define RGB_END_LEDMAP_LEFT 23
    #define RGB_INDICATOR_L_START 24
    #define RGB_INDICATOR_L_END 63
    // +6 for the two unwired keys
    #define RGB_TOT_IND_L 46

    #define RGB_START_LEDMAP_RIGHT 70
    #define RGB_END_LEDMAP_RIGHT 93
    #define RGB_INDICATOR_R_START 94
    #define RGB_INDICATOR_R_END 139
    // +6 for the two unwired keys
    
#endif