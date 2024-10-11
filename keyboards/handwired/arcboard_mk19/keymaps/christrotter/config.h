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
    // #define DEBUG_MATRIX_SCAN_RATE // we call it on the TFTs
    // #if defined(QP_DEBUG_ENABLE)
    //    #define QUANTUM_PAINTER_DEBUG // massively degrades performance!!!
    // #endif
#endif

#if defined(RGB_MATRIX_LEDMAPS_ENABLED)
    #define UF_INNER_BRIGHTNESS 150
    #define UF_OUTER_BRIGHTNESS 150
    #define INDICATOR_BRIGHTNESS 90
    #define INDICATOR_IDLE_BRIGHTNESS 30
#endif

#if defined(POINTING_DEVICE_ENABLE)
    #define POINTING_DEVICE_AUTO_MOUSE_ENABLE
    #define AUTO_MOUSE_DEBOUNCE 25
    #define POINTING_DEVICE_INVERT_Y
    #define ROTATIONAL_TRANSFORM_ANGLE 90
    #define DRAGSCROLL_BUFFER_SIZE 6
    #define PMW33XX_CPI 700       // your mouse cpi (DPI) setting (how fast the ball tracks); note when usb main is on the left half this config needs to be 900
    #define DRAGSCROLL_CPI 100    // dragscroll cpi - interestingly, can't be set below 100?
#endif


// tuning the scroll responsiveness
#define MOUSEKEY_WHEEL_INTERVAL 5      // Time between wheel movements
#define MOUSEKEY_WHEEL_DELTA 7          // Wheel movement step size, bigger is more
#define MOUSEKEY_WHEEL_MAX_SPEED 30     // Maximum number of scroll steps per scroll action
#define MOUSEKEY_WHEEL_TIME_TO_MAX 5    // Time until maximum scroll speed is reached