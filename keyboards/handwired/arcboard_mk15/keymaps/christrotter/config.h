#pragma once
// keyboard config
// this is how long 'hold for effect' takes; 300 feels way too long, 200 causes too many accidental triggers
#undef TAPPING_TERM
#define TAPPING_TERM 225            // time (in ms) for a tap to become a hold
#define TAP_CHECK TAPPING_TERM
#undef TAPPING_TOGGLE
#define TAPPING_TOGGLE 2
//#define DEBOUNCE 5                // trying this down from 45, apparently can contribute to input lag
#define ONESHOT_TAP_TOGGLE 2        /* Tapping this number of times holds the key until tapped once again. */
#define ONESHOT_TIMEOUT 2000        /* Time (in ms) before the one shot key is released */
#define IGNORE_MOD_TAP_INTERRUPT

#define CUSTOM_KEYCODES

#if defined(CONSOLE_ENABLE)
    // #define DEBUG_MATRIX_SCAN_RATE
#endif

#if defined(POINTING_DEVICE_ENABLE)
    #define POINTING_DEVICE_AUTO_MOUSE_ENABLE
    #define AUTO_MOUSE_DEFAULT_LAYER 1
    #define AUTO_MOUSE_DEBOUNCE 25
    #define POINTING_DEVICE_INVERT_X_RIGHT
    #define ROTATIONAL_TRANSFORM_ANGLE -60
    #define DRAGSCROLL_BUFFER_SIZE 6
#endif
