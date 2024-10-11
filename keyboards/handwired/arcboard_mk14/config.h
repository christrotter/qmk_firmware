// Copyright 2022 Chris Trotter (@Chris Trotter)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "config_common.h"

#ifdef CONSOLE_ENABLE
    // #define SERIAL_DEBUG
    // #define QUANTUM_PAINTER_DEBUG // this puts out crazy amounts of debug
#endif


#define MATRIX_ROW_PINS { GP11 }
#define MATRIX_COL_PINS { GP16, GP17 }
#define DIODE_DIRECTION COL2ROW
#define MATRIX_ROWS 1                          // Rows are doubled-up in a split kb
#define MATRIX_COLS 2
#define USB_POLLING_INTERVAL_MS 1 /* Set Polling rate to 1000Hz */
#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0

// setting i2c for pimoroni
//#define I2C_DRIVER I2CD2 // whyyyyy does this work
//#define I2C1_SDA_PIN GP14
//#define I2C1_SCL_PIN GP15
//#define CIRQUE_PINNACLE_DIAMETER_MM 40
//#define POINTING_DEVICE_ROTATION_90
//#define POINTING_DEVICE_INVERT_X
//#define POINTING_DEVICE_INVERT_Y
//#define CIRQUE_PINNACLE_TAP_ENABLE
//#define POINTING_DEVICE_GESTURES_SCROLL_ENABLE
//#define PIMORONI_TRACKBALL_SCALE 1
//#define POINTING_DEVICE_TASK_THROTTLE_MS 1
//#define MOUSE_EXTENDED_REPORT

// setting the SPI pins for the PMW // why isn't this inside pointing_device_enable?
//#define SPI_DRIVER SPID1
//#define SPI_SCK_PIN GP10  // clock is shared
//#define SPI_MOSI_PIN GP11 // mosi is shared....?
//#define SPI_MISO_PIN GP12 // this is dedicated for pmw according to wiring doc

// RP2040 reset functionality
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET      // Activates the double-tap behavior
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 200U // Timeout window in ms in which the double tap can occur.
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED_MASK 0U // Specify a optional status led which blinks when entering the bootloader
#define CRC8_USE_TABLE
#define CRC8_OPTIMIZE_SPEED

// encoder
#define ENCODERS_PAD_A { GP12 }
#define ENCODERS_PAD_B { GP13 }
#define ENCODER_RESOLUTION 4

// WS2812 RGB LED strip input and number of LEDs
#if defined(RGB_MATRIX_ENABLE) || defined(RGB_MATRIX_LEDMAPS_ENABLED)
    #define RGB_DI_PIN GP15
    #define RGBLED_NUM 12                      // Total number of LEDs, total of both halves
    #define RGB_MATRIX_LED_COUNT RGBLED_NUM
    #define KEYS_LED_MIN 0
    #define KEYS_LED_MAX 12
    #define KEYS_LED_COUNT 12
//    #define IND1_LED_MIN 3
//    #define IND1_LED_MAX 4
//    #define IND1_LED_COUNT 2
//    #define IND2_LED_MIN 5
//    #define IND2_LED_MAX 6
//    #define IND2_LED_COUNT 2

    // this brightness is only for 'default' rgb settings; userspace rgb is set in the keymap config.h
    #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 90 // this has no effect unless you eeprom reset  // setting this too high will cause the trackball to reset every min or so, and at highest just brownout entirely
    #define NOP_FUDGE 0.4                       // not sure what this does - some math about rgb brightness or something? - but it won't compile without this set
#endif
