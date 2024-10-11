// Copyright 2023 Chris Trotter (@christrotter)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once
// keyboard config
// this is how long 'hold for effect' takes; 300 feels way too long, 200 causes too many accidental triggers
#undef TAPPING_TERM
#define TAPPING_TERM 225            // time (in ms) for a tap to become a hold
#define TAP_CHECK TAPPING_TERM
#undef TAPPING_TOGGLE
#define TAPPING_TOGGLE 2
#define ONESHOT_TAP_TOGGLE 2        /* Tapping this number of times holds the key until tapped once again. */
#define ONESHOT_TIMEOUT 2000        /* Time (in ms) before the one shot key is released */
#define CUSTOM_KEYCODES

#if defined(CONSOLE_ENABLE)
    #define DEBUG_MATRIX_SCAN_RATE // we call it on the TFTs
    // #if defined(QP_DEBUG_ENABLE)
    //     #define QUANTUM_PAINTER_DEBUG // massively degrades performance!!!
    // #endif
#endif

#if defined(RGB_MATRIX_LEDMAPS_ENABLED)
    #define RGB_INDICATOR_BRIGHTNESS 100
#endif
