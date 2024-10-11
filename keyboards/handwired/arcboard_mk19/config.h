// Copyright 2023 christrotter (@christrotter)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define DEBOUNCE 10

// only used for testing matrix/led issues
// #define	SPLIT_HAND_PIN_LOW_IS_LEFT

// GPIO configuration
#define SPI_SCK_PIN  GP10
#define SPI_MOSI_PIN GP11
#define SPI_MISO_PIN GP12
#define SPI_MATRIX_LATCH_PIN GP14
#define SPI_MATRIX_CHIP_SELECT_PIN_ROWS GP15
#define SPI_MATRIX_CHIP_SELECT_PIN_COLS GP13
#if defined(SPLIT_KEYBOARD)
    #define SERIAL_USART_TX_PIN GP28
    #define SERIAL_USART_RX_PIN GP29
    #define SPLIT_HAND_PIN GP2
#endif
#if defined(POINTING_DEVICE_ENABLE)
    #define PMW33XX_CS_PIN GP16
#endif
#if defined(QUANTUM_PAINTER_ENABLE)
    // wat dis
    #define DISPLAY_DC_PIN GP20
    #define DISPLAY_RST_PIN GP21
    #define DISPLAY_LED_PIN GP19
    #define DISPLAY1_CS_PIN GP17
    #define DISPLAY2_CS_PIN GP18
#endif
#ifdef AUDIO_ENABLE
    #define AUDIO_PIN GP0
#endif

// SPI configuration
#define SPI_MATRIX_DIVISOR 16
#define SPI_MODE 0
#define SPI_DRIVER SPID1

// custom matrix config
#define MATRIX_COLS_SHIFT_REGISTER_COUNT 2
#define MATRIX_ROWS_SHIFT_REGISTER_COUNT 2
#define ROWS_COUNT 6 // this can be replaced w. array_size or something?
#define ROWS { \
    0b0000000000000001, \
    0b0000000000000010, \
    0b0000000000000100, \
    0b0000000000001000, \
    0b0000000000010000, \
    0b0000000000100000, \
}

    // 0b0000000001000000, 
    // 0b0000000010000000, 
    // 0b0000000100000000, 
    // 0b0000001000000000, 
    // 0b0000010000000000, 
    // 0b0000100000000000, 
    // 0b0000010000000000, 
    // 0b0000100000000000, 
    // 0b0001000000000000, 
    // 0b0010000000000000, 
    // 0b0100000000000000, 
    // 0b1000000000000000, 

// #define ROWS (uint16_t[]){0x4000, 0x2000, 0x1000, 0x0800, 0x0400, 0x0200, 0x0100, 0x0080, 0x0040, 0x0020, 0x0010, 0x0008, 0x0004, 0x0002, 0x0001}
// Rows that should be scanned, by their bit position and thus row index.

// this makes sense if they are == PCB-ROW0, like the physical pin location
// #define ROWS { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 }
// #define ROWS { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 }
// #define ROWS { 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 }

// Split settings
#if defined(SPLIT_KEYBOARD)
    #define SERIAL_USART_FULL_DUPLEX
    #define SERIAL_USART_PIN_SWAP
    #define SERIAL_PIO_USE_PIO1                 // using PIO0 i get a lot of dropped packets; none using PIO1
    #define SERIAL_USART_SPEED 800000           // this improves scan rate by 200
    #define SPLIT_LAYER_STATE_ENABLE            // docs say use this if you are using split and rgb lighting per layer // this added 20 to scanrate???
#endif

#if defined(POINTING_DEVICE_ENABLE)
    #define POINTING_DEVICE_TASK_THROTTLE_MS 10 // this ensures that the trackball sensor polling happens only every 10ms
    #define MOUSE_EXTENDED_REPORT
    #define SPLIT_POINTING_ENABLE               // required for telling the master side about slave trackball state, i.e. if usb left, and tb right
    #define POINTING_DEVICE_RIGHT
#endif

// encoder direction change fix
#define ENCODER_DEFAULT_POS 3

#if defined(RGB_MATRIX_ENABLE) || defined(RGB_MATRIX_LEDMAPS_ENABLED)
    #define RGB_MATRIX_DEFAULT_HUE 5
    #define RGB_MATRIX_DEFAULT_SAT 5
    // keys/thumbs count = 38
    // big slats count = 37 // flag: 1
    // sm. slats count = 11 // flag: 1
    // indicator count = 5 // flag: 2
    // macro count = 8 // flag: 4
    // falcon1 count = 30?
    // falcon2 count = 30?
    // dpad = 4
    // screen count = ? ?? // flag: 8

    // Total counts are important for the left/right 'set_rgb_range' logic, cuz life is hard.
    #define RGB_TOT_IND_L 65
    #define RGB_TOT_IND_R 65

    #define RGB_KEYS_L_START 0
    #define RGB_KEYS_L_END 47
    #define RGB_UF1_INNER_L_START 48
    #define RGB_UF1_INNER_L_END 53
    #define RGB_UF1_OUTER_L_START 54
    #define RGB_UF1_OUTER_L_END 77
    #define RGB_UF2_INNER_L_START 78
    #define RGB_UF2_INNER_L_END 83
    #define RGB_UF2_OUTER_L_START 84
    #define RGB_UF2_OUTER_L_END 107
    #define RGB_INDICATOR_L_START 108
    #define RGB_INDICATOR_L_END 112
    #define RGB_KEYS_R_START 113
    #define RGB_KEYS_R_END 160
    #define RGB_UF1_INNER_R_START 161
    #define RGB_UF1_INNER_R_END 166
    #define RGB_UF1_OUTER_R_START 167
    #define RGB_UF1_OUTER_R_END 190
    #define RGB_UF2_INNER_R_START 191
    #define RGB_UF2_INNER_R_END 196
    #define RGB_UF2_OUTER_R_START 197
    #define RGB_UF2_OUTER_R_END 220
    #define RGB_INDICATOR_R_START 221
    #define RGB_INDICATOR_R_END 225
    /*
    #define RGB_SCREEN_GLOW_START 0
    #define RGB_SCREEN_GLOW_END 0
    #define RGB_SCREEN_IND_START 0
    #define RGB_SCREEN_IND_END 0
    */

    // I got better scan rate performance by avoiding led_min/led_max and flags.
#endif

#if defined(QUANTUM_PAINTER_ENABLE)
    #define QUANTUM_PAINTER_TASK_THROTTLE 50 // trying to reduce the scan rate impact
    #define QUANTUM_PAINTER_DISPLAY_TIMEOUT 0 // this is super important - you get a white screen after 30s otherwise
    // #define QUANTUM_PAINTER_DEBUG
    #define DISPLAY_SPI_DIVISOR 12
    #define DISPLAY_SPI_MODE 0
    #define GC9A01_NUM_DEVICES 2
    #define QUANTUM_PAINTER_SUPPORTS_NATIVE_COLORS true
    #define QP_LVGL_TASK_PERIOD 40
    #define SCREEN_TIMEOUT (900 * 1000) // shut off the displays after 15 minutes
    // #define QUANTUM_PAINTER_NUM_DISPLAYS 2
#endif

#ifdef AUDIO_ENABLE
    #define AUDIO_PWM_CHANNEL RP2040_PWM_CHANNEL_A
    #define AUDIO_PWM_DRIVER PWMD0
    #define STARTUP_SONG SONG(STARTUP_SOUND)
#endif