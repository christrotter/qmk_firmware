// Copyright 2023 Chris Trotter (@Chris Trotter)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "config_common.h"

#ifdef CONSOLE_ENABLE
    // #define SERIAL_DEBUG
    // #define QUANTUM_PAINTER_DEBUG // this puts out crazy amounts of debug
#endif

#define MATRIX_ROW_PINS { GP7, GP6, GP5, GP4, GP3, GP2 }
#define MATRIX_COL_PINS { GP16, GP17, GP18, GP19, GP20, GP21 }
#define DIODE_DIRECTION COL2ROW
#define MATRIX_ROWS 22                          // Rows are doubled-up in a split kb
#define MATRIX_COLS 6
#define USB_POLLING_INTERVAL_MS 1 /* Set Polling rate to 1000Hz */

// setting the SPI pins for the PMW // why isn't this inside pointing_device_enable?
#define SPI_DRIVER SPID1
#define SPI_SCK_PIN GP10  // clock is shared
#define SPI_MOSI_PIN GP11 // mosi is shared....?
#define SPI_MISO_PIN GP12 // this is dedicated for pmw according to wiring doc

// RP2040 reset functionality
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET      // Activates the double-tap behavior
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 200U // Timeout window in ms in which the double tap can occur.
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED_MASK 0U // Specify a optional status led which blinks when entering the bootloader
#define CRC8_USE_TABLE
#define CRC8_OPTIMIZE_SPEED

// Split settings
#ifdef SPLIT_KEYBOARD
    #define EE_HANDS                            // cuz we are using hand-targeted flashing, which sets eeprom handednesss
    #define SERIAL_USART_TX_PIN GP1  // I could never get full-duplex working; this is the only config needed for half-duplex
    // must have eeprom reset buttons on both halves
    #define BOOTMAGIC_LITE_ROW 0
    #define BOOTMAGIC_LITE_COLUMN 0
    // this uses row/col numbering that starts on 0
    #define BOOTMAGIC_LITE_ROW_RIGHT 5
    #define BOOTMAGIC_LITE_COLUMN_RIGHT 0
    // generic split config
    #define SPLIT_WATCHDOG_ENABLE // this took 30 off the scanrate
    #define SPLIT_WATCHDOG_TIMEOUT 3000
    #define SPLIT_TRANSPORT_MIRROR              // docs say use this if you are using RGB_MATRIX_SPLIT { X, Y } // this doesn't seem to do anything...took 10 off scanrate
    #define SPLIT_LAYER_STATE_ENABLE            // docs say use this if you are using split and rgb lighting per layer // this added 20 to scanrate???
    #define SPLIT_MODS_ENABLE                   // docs say it is for telling the other half about modifier (e.g. oneshot) state // this removed 35 from scanrate
#endif

#ifdef POINTING_DEVICE_ENABLE
    #ifdef POINTING_DEBUG_ENABLE
        #define POINTING_DEVICE_DEBUG // enables some handy debug output; pair with 'debug_mouse=true' in your keyboard_post_init_user // also, should wrap debug up in something maybe
    #endif
    #define MOUSE_EXTENDED_REPORT // do we need this?
    #define POINTING_DEVICE_TASK_THROTTLE_MS 10 // this ensures that the trackball sensor polling happens only every 10ms
    // note that PMW33XX_SPI_DIVISOR is pre-defined to 64
    #define SPLIT_POINTING_ENABLE               // required for telling the master side about slave trackball state, i.e. if usb left, and tb right
    #define POINTING_DEVICE_COMBINED
    #define PMW33XX_CS_PIN GP13                 // where the SS (CS) pin on the PMW module connects to the mcu
    #define PMW33XX_SPI_DIVISOR 64              // this is the default, but given the use of SPI, handy to have here for reference; drivers/sensors/pmw33xx_common.h
    #define PMW33XX_LIFTOFF_DISTANCE 0x07       // LIFTOFF_DISTANCE specifies how far from the sensor the trackball is

    #define RIGHT_PMW_CPI 700       // your mouse cpi (DPI) setting (how fast the ball tracks)
    #define LEFT_PMW_CPI 100    // dragscroll cpi - interestingly, can't be set below 100?

    // #define POINTING_DEVICE_INVERT_X
    // #define ROTATIONAL_TRANSFORM_ANGLE 100        // Software adjustment for how not-squarely you packaged the sensor
    // #define POINTING_DEVICE_ROTATION_90_RIGHT
    // #define POINTING_DEVICE_INVERT_Y_RIGHT
    // #define POINTING_DEVICE_ROTATION_90
    // #define POINTING_DEVICE_INVERT_X            // Inverted movement for X (not sure why this is set tbh...maybe due to the kb half it's installed on?)
    // #define POINTING_DEVICE_INVERT_Y
    // #define DRAGSCROLL_REVERSE_X                // i must have installed the sensor flipped around

#endif

// WS2812 RGB LED strip input and number of LEDs
#if defined(RGB_MATRIX_ENABLE) || defined(RGB_MATRIX_LEDMAPS_ENABLED)
    #define RGB_DI_PIN GP28
    #define RGBLED_NUM 112                       // Total number of LEDs, total of both halves
    #define RGB_MATRIX_SPLIT { 56, 56 }
    #define RGB_MATRIX_LED_COUNT RGBLED_NUM

    // this brightness is only for 'default' rgb settings; userspace rgb is set in the keymap config.h
    #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 50 // this has no effect unless you eeprom reset  // setting this too high will cause the trackball to reset every min or so, and at highest just brownout entirely
    #define RGB_MATRIX_DEFAULT_HUE 5
    #define RGB_MATRIX_DEFAULT_SAT 5
    #define RGB_MATRIX_DEFAULT_VAL RGB_MATRIX_MAXIMUM_BRIGHTNESS
    #define NOP_FUDGE 0.4                       // not sure what this does - some math about rgb brightness or something? - but it won't compile without this set
#endif

#if defined(ENCODER_ENABLE)
    #define ENCODERS_PAD_A { GP8 }
    #define ENCODERS_PAD_B { GP9 }
    #define ENCODER_RESOLUTION 4
#endif
