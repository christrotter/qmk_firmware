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

#if defined(POINTING_DEVICE_ENABLE)
    // #define POINTING_DEVICE_DEBUG
    #define POINTING_DEVICE_TASK_THROTTLE_MS 10 // this ensures that the trackball sensor polling happens only every 10ms
    #define SPLIT_POINTING_ENABLE               // required for telling the master side about slave trackball state, i.e. if usb left, and tb right
    #define POINTING_DEVICE_RIGHT
    #define PMW33XX_CS_PIN GP13                 // where the SS (CS) pin on the PMW module connects to the mcu
#endif

#if defined(POINTING_DEVICE_ENABLE) || defined(QUANTUM_PAINTER_ENABLE)
    // SPI setup (PMW33xx is normally in use)
    #define SPI_DRIVER SPID1  // Waveshare documentation says these pins are SPI1
    #define SPI_SCK_PIN GP10  // clock is shared
    #define SPI_MOSI_PIN GP11 // mosi is shared
    #define SPI_MISO_PIN GP12 // this is dedicated for pmw according to wiring doc
#endif

// WS2812 RGB LED strip input and number of LEDs
#if defined(RGB_MATRIX_ENABLE) || defined(RGB_MATRIX_LEDMAPS_ENABLED)
    #define RGB_MATRIX_LED_COUNT RGBLED_NUM
    // I got better scan rate performance by avoiding led_min/led_max and flags.
    #define RGB_MATRIX_DEFAULT_HUE 5
    #define RGB_MATRIX_DEFAULT_SAT 5
    #define RGB_MATRIX_DEFAULT_VAL RGB_MATRIX_MAXIMUM_BRIGHTNESS
    #define NOP_FUDGE 0.4 // won't compile without this set
#endif
