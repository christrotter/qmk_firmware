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

// #if defined(CONSOLE_ENABLE)
//     // Debug flags
//     // #define QUANTUM_PAINTER_DEBUG
// #endif

#define DEBUG_MATRIX_SCAN_RATE // need this to show scan rate on display

#if defined(POINTING_DEVICE_ENABLE)
    #define ROTATIONAL_TRANSFORM_ANGLE 90
    #define POINTING_DEVICE_INVERT_Y
    #define POINTING_DEVICE_AUTO_MOUSE_ENABLE
    #define AUTO_MOUSE_DEFAULT_LAYER 1
    #define AUTO_MOUSE_DEBOUNCE 25
    // tuning the scroll responsiveness
    #define MOUSEKEY_WHEEL_INTERVAL 1      // Time between wheel movements
    #define MOUSEKEY_WHEEL_DELTA 30          // Wheel movement step size, bigger is more
    #define MOUSEKEY_WHEEL_MAX_SPEED 30     // Maximum number of scroll steps per scroll action
    #define MOUSEKEY_WHEEL_TIME_TO_MAX 0    // Time until maximum scroll speed is reached
#endif

#if defined(QUANTUM_PAINTER_ENABLE)
    #define QUANTUM_PAINTER_SUPPORTS_256_PALETTE TRUE
    #define QUANTUM_PAINTER_SUPPORTS_NATIVE_COLORS TRUE
    #define QUANTUM_PAINTER_NUM_IMAGES 32
    #define SCREEN_TIMEOUT (900 * 1000) // shut off the displays after 15 minutes
#endif