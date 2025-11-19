#pragma once
// #define QUANTUM_PAINTER_DEBUG
// #define DEBUG_MATRIX_SCAN_RATE

// #define PMW33XX_LIFTOFF_DISTANCE 0xFF
#define ROTATIONAL_TRANSFORM_ANGLE 90
#define POINTING_DEVICE_INVERT_Y

#define INDICATOR_BRIGHTNESS 90
#define INDICATOR_IDLE_BRIGHTNESS 30

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
    #define AUTO_MOUSE_DEFAULT_LAYER 1
    #define AUTO_MOUSE_DEBOUNCE 25
#endif

// tuning the scroll responsiveness
#define MOUSEKEY_WHEEL_INTERVAL 1      // Time between wheel movements
#define MOUSEKEY_WHEEL_DELTA 30          // Wheel movement step size, bigger is more
#define MOUSEKEY_WHEEL_MAX_SPEED 30     // Maximum number of scroll steps per scroll action
#define MOUSEKEY_WHEEL_TIME_TO_MAX 0    // Time until maximum scroll speed is reached


// rgb stuff
// we have 94 leds per side
#define RGB_TOT_IND_L 64
#define RGB_TOT_IND_R 64

// 30 in keys + 4 in dpad + 3 in paddle-keys
// 37 + 19 + 8 + 10 + 16 + 12 = 102
// 102 - 37 = 65
#define RGB_LEDS_IN_KEYS 37
#define RGB_LEDS_IN_RING 18
#define RGB_LEDS_IN_RING_R 19
#define RGB_LEDS_IN_INDICATOR 8
#define RGB_LEDS_IN_INDICATOR_SPLIT 4
#define RGB_LEDS_IN_INNER_INTAKE 10
#define RGB_LEDS_IN_OUTER_INTAKE 16
#define RGB_LEDS_IN_LOGO 12

// left side led counts
// keys
#define RGB_KEYS_L_START 0
#define RGB_KEYS_L_END RGB_KEYS_L_START + RGB_LEDS_IN_KEYS

// ring encoder
#define RGB_RING_L_START RGB_KEYS_L_END
#define RGB_RING_L_END RGB_RING_L_START + RGB_LEDS_IN_RING

// indicator bar // 8 leds in the indicator
#define RGB_INDICATOR_L_START RGB_RING_L_END
#define RGB_INDICATOR_L_END RGB_INDICATOR_L_START + RGB_LEDS_IN_INDICATOR - 1

// now we split it up for multi-function display
#define RGB_INDICATOR_L1_START RGB_INDICATOR_L_START
#define RGB_INDICATOR_L1_END RGB_INDICATOR_L_START + RGB_LEDS_IN_INDICATOR_SPLIT
#define RGB_INDICATOR_L2_START RGB_INDICATOR_L1_END
#define RGB_INDICATOR_L2_END RGB_INDICATOR_L_END

// intakes
#define RGB_INNER_INTAKE_L_START RGB_INDICATOR_L_END // there are 10 leds in the inner intake
#define RGB_INNER_INTAKE_L_END RGB_INNER_INTAKE_L_START + RGB_LEDS_IN_INNER_INTAKE
#define RGB_OUTER_INTAKE_L_START RGB_INNER_INTAKE_L_END + 1  // there are 24 leds in the outer intake
// there are 24 leds in the outer intake
#define RGB_OUTER_INTAKE_L_END RGB_OUTER_INTAKE_L_START + RGB_LEDS_IN_OUTER_INTAKE
// there are 12 leds in the logo
#define RGB_LOGO_L_START RGB_OUTER_INTAKE_L_END + 1
#define RGB_LOGO_L_END RGB_LOGO_L_START + RGB_LEDS_IN_LOGO


// right side
// keys
#define RGB_KEYS_R_START RGB_LOGO_L_END
#define RGB_KEYS_R_END RGB_KEYS_R_START + RGB_LEDS_IN_KEYS

// ring encoder
#define RGB_RING_R_START RGB_KEYS_R_END - 1
#define RGB_RING_R_END RGB_RING_R_START + RGB_LEDS_IN_RING_R

// indicator bar // 8 leds in the indicator
#define RGB_INDICATOR_R_START RGB_RING_R_END
#define RGB_INDICATOR_R_END RGB_INDICATOR_R_START + RGB_LEDS_IN_INDICATOR - 1

// now we split it up for multi-function display
#define RGB_INDICATOR_R1_START RGB_INDICATOR_R_START
#define RGB_INDICATOR_R1_END RGB_INDICATOR_R_START + RGB_LEDS_IN_INDICATOR_SPLIT
#define RGB_INDICATOR_R2_START RGB_INDICATOR_R1_END
#define RGB_INDICATOR_R2_END RGB_INDICATOR_R_END

// intakes
#define RGB_INNER_INTAKE_R_START RGB_INDICATOR_R_END // there are 10 leds in the inner intake
#define RGB_INNER_INTAKE_R_END RGB_INNER_INTAKE_R_START + RGB_LEDS_IN_INNER_INTAKE
#define RGB_OUTER_INTAKE_R_START RGB_INNER_INTAKE_R_END + 1  // there are 24 leds in the outer intake
// there are 24 leds in the outer intake
#define RGB_OUTER_INTAKE_R_END RGB_OUTER_INTAKE_R_START + RGB_LEDS_IN_OUTER_INTAKE - 1
// there are 12 leds in the logo
#define RGB_LOGO_R_START RGB_OUTER_INTAKE_R_END + 1
#define RGB_LOGO_R_END RGB_LOGO_R_START + RGB_LEDS_IN_LOGO
