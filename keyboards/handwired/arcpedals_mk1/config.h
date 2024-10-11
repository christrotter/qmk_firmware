// Copyright 2023 christrotter (@christrotter)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// RP2040 reset functionality
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET              // Activates the double-tap behavior
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 200U // Timeout window in ms in which the double tap can occur.
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED_MASK 0U  // Specify a optional status led which blinks when entering the bootloader

// RP2040 performance improvements
#define CRC8_USE_TABLE
#define CRC8_OPTIMIZE_SPEED

// Split settings
#if defined(SPLIT_KEYBOARD)
    #define EE_HANDS                            // cuz we are using hand-targeted flashing, which sets eeprom handednesss
    #define SERIAL_USART_TX_PIN GP1             // I could never get full-duplex working; this is the only config needed for half-duplex
    #define SERIAL_PIO_USE_PIO1                 // using PIO0 i get a lot of dropped packets; none using PIO1
    #define SERIAL_USART_SPEED 800000
    #define SPLIT_LAYER_STATE_ENABLE            // docs say use this if you are using split and rgb lighting per layer // this added 20 to scanrate???
#endif

// WS2812 RGB LED strip input and number of LEDs
#if defined(RGB_MATRIX_ENABLE) || defined(RGB_MATRIX_LEDMAPS_ENABLED)
    #define RGB_MATRIX_KEYPRESSES
    #define ENABLE_RGB_MATRIX_SOLID_REACTIVE
    #define RGB_MATRIX_LED_COUNT RGBLED_NUM
    // I got better scan rate performance by avoiding led_min/led_max and flags.
    #define RGB_KEYS_L_MIN 0 // (actual keys, 4x6 + 5 + 1f + 5dpad + 1f = 36)
    #define RGB_KEYS_L_MAX 5
    #define RGB_KEYS_R_MIN 6
    #define RGB_KEYS_R_MAX 11
    #define RGB_TOT_IND_L 0
    #define RGB_IND_R_MIN 12
    #define RGB_IND_R_MAX 53
    #define RGB_MATRIX_DEFAULT_HUE 5
    #define RGB_MATRIX_DEFAULT_SAT 5
    #define RGB_MATRIX_DEFAULT_VAL RGB_MATRIX_MAXIMUM_BRIGHTNESS
    #define NOP_FUDGE 0.4 // won't compile without this set
#endif
