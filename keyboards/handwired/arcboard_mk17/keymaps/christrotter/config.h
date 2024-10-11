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

// unicode
#define UNICODE_SELECTED_MODE UNICODE_MODE_MAC
#define UNICODE_KEY_MAC KC_LEFT_ALT

#if defined(CONSOLE_ENABLE)
    #define DEBUG_MATRIX_SCAN_RATE // we call it on the TFTs
    // #if defined(QP_DEBUG_ENABLE)
    //     #define QUANTUM_PAINTER_DEBUG // massively degrades performance!!!
    // #endif
#endif

#if defined(RGB_MATRIX_LEDMAPS_ENABLED)
    #define RGB_INDICATOR_BRIGHTNESS 100
#endif

#if defined(POINTING_DEVICE_ENABLE)
    #define POINTING_DEVICE_AUTO_MOUSE_ENABLE
    #define AUTO_MOUSE_DEBOUNCE 25
    #define POINTING_DEVICE_INVERT_Y_RIGHT
    #define ROTATIONAL_TRANSFORM_ANGLE 0
    #define DRAGSCROLL_BUFFER_SIZE 6
    #define PMW33XX_CPI 700       // your mouse cpi (DPI) setting (how fast the ball tracks)
    #define DRAGSCROLL_CPI 100    // dragscroll cpi - interestingly, can't be set below 100?
    #define RIGHT_PMW_CPI 700       // your mouse cpi (DPI) setting (how fast the ball tracks)
    #define LEFT_PMW_CPI 100    // dragscroll cpi - interestingly, can't be set below 100?
#endif

#if defined(MACCEL_ENABLE)
    #define MACCEL_TAKEOFF 1.5      // lower/higher value = curve takes off more smoothly/abruptly
    #define MACCEL_GROWTH_RATE 0.5 // lower/higher value = curve reaches its upper limit slower/faster 
    #define MACCEL_OFFSET 6       // lower/higher value = acceleration kicks in earlier/later
    #define MACCEL_LIMIT 0.0        // lower limit of accel curve (minimum acceleration factor)
#endif