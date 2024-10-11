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

#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0

#if defined(RGB_MATRIX_ENABLE) || defined(RGB_MATRIX_LEDMAPS_ENABLED)
#undef RGB_MATRIX_MAXIMUM_BRIGHTNESS
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 90 // need to clear eeprom to make this work.
// Startup values.
#define RGB_MATRIX_STARTUP_HUE 5
#define RGB_MATRIX_STARTUP_SAT 5
#define RGB_MATRIX_STARTUP_VAL RGB_MATRIX_MAXIMUM_BRIGHTNESS
#define RGB_MATRIX_STARTUP_HSV RGB_MATRIX_STARTUP_HUE, RGB_MATRIX_STARTUP_SAT, RGB_MATRIX_STARTUP_VAL
#endif // RGB_MATRIX_ENABLE

