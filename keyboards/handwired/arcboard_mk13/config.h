// Copyright 2022 Chris Trotter (@Chris Trotter)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "config_common.h"

#ifdef CONSOLE_ENABLE
    #define SERIAL_DEBUG
    // #define QUANTUM_PAINTER_DEBUG // this puts out crazy amounts of debug
#endif

#define MATRIX_ROW_PINS { GP7, GP6, GP5, GP4, GP3, GP2, GP27 }
#define MATRIX_COL_PINS { GP16, GP17, GP18, GP19, GP20, GP21, GP22 }
#define DIODE_DIRECTION COL2ROW
#define MATRIX_ROWS 14                          // Rows are doubled-up in a split kb
#define MATRIX_COLS 7
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

// For the tft display
#ifdef QUANTUM_PAINTER_ENABLE
    #define SPI_MATRIX_DIVISOR 8
    #define DISPLAY_SPI_DIVISOR 4
    #define DISPLAY_DC_PIN GP8
    #define DISPLAY_CS_PIN GP9
    #define DISPLAY_RST_PIN GP15
    #define ST7789_NUM_DEVICES 2
    #define QUANTUM_PAINTER_CONCURRENT_ANIMATIONS 8
    #define QUANTUM_PAINTER_LOAD_FONTS_TO_RAM TRUE
    #define QUANTUM_PAINTER_NUM_IMAGES 14
    #define QUANTUM_PAINTER_SUPPORTS_256_PALETTE TRUE
    #define QP_MATRIX_SCAN_INTERVAL 1000
    #define DEBUG_MATRIX_SCAN_RATE // we call it on the TFTs
    #ifdef BACKLIGHT_ENABLE
        #define BACKLIGHT_PWM_DRIVER PWMD0
        // there is code in platforms/chibios/vendors/RP/_pin_defs.h: #define RP2040_PWM_CHANNEL_A 1
        #undef RP2040_PWM_CHANNEL_A
        #define RP2040_PWM_CHANNEL_A 1
        #define BACKLIGHT_PWM_CHANNEL RP2040_PWM_CHANNEL_A // waveshare rp2040-plus has 16 pwm channels
        #define BACKLIGHT_PIN GP26
        #define BACKLIGHT_LIMIT_VAL	128 // limiting this cuz...don't want to crash the board?...is that founded?
        #define BACKLIGHT_LEVELS 1
    #endif // BACKLIGHT_ENABLE
#endif

// Split settings
#ifdef SPLIT_KEYBOARD
    #define EE_HANDS                            // cuz we are using hand-targeted flashing, which sets eeprom handednesss
    // this is all you should need for RP2040 serial...
    // #define SERIAL_USART_FULL_DUPLEX // this breaks transport
    #define SERIAL_USART_PIN_SWAP               // because the trrs pinouts are the same on both sides
    #define SOFT_SERIAL_PIN GP0                 // Defines the half-duplex serial data pin; on both sides, cuz pin swap // GP1 consistently doesn't work for me on Waveshare RP2040-Plus
    #define SERIAL_USART_RX_PIN GP1 // not sure this is necessary...but it is working
    // #define SERIAL_USART_FULL_DUPLEX   // Enable full duplex operation mode. // this currently breaks all transport
    // #define SERIAL_PIO_USE_PIO1 // Force the usage of PIO1 peripheral, by default the Serial implementation uses the PIO0 peripheral
    #define SELECT_SOFT_SERIAL_SPEED 5
    // must have eeprom reset buttons on both halves
    #define BOOTMAGIC_LITE_ROW 0
    #define BOOTMAGIC_LITE_COLUMN 0
    // this uses row/col numbering that starts on 0
    #define BOOTMAGIC_LITE_ROW_RIGHT 7
    #define BOOTMAGIC_LITE_COLUMN_RIGHT 6
    // generic split config
    #define SPLIT_WATCHDOG_ENABLE
    #define SPLIT_WATCHDOG_TIMEOUT 3000
    #define SPLIT_TRANSPORT_MIRROR              // docs say use this if you are using RGB_MATRIX_SPLIT { X, Y }
    #define SPLIT_LAYER_STATE_ENABLE            // docs say use this if you are using split and rgb lighting per layer
    #define SPLIT_MODS_ENABLE                   // docs say it is for telling the other half about modifier (e.g. oneshot) state
    #define SPLIT_USB_DETECT // i think uses vsys on usb as a signal (cuz slave side gets 3v3)
#endif

#ifdef POINTING_DEVICE_ENABLE
    #ifdef POINTING_DEBUG_ENABLE
        #define POINTING_DEVICE_DEBUG // enables some handy debug output; pair with 'debug_mouse=true' in your keyboard_post_init_user // also, should wrap debug up in something maybe
    #endif
    // note that PMW33XX_SPI_DIVISOR is pre-defined to 64
    #define SPLIT_POINTING_ENABLE               // required for telling the master side about slave trackball state, i.e. if usb left, and tb right
    #define POINTING_DEVICE_RIGHT               // Which keyboard half contains the trackball
    #define PMW33XX_CS_PIN GP13                 // where the SS (CS) pin on the PMW module connects to the mcu
    #define PMW33XX_SPI_DIVISOR 64              // this is the default, but given the use of SPI, handy to have here for reference; drivers/sensors/pmw33xx_common.h
    #define PMW33XX_LIFTOFF_DISTANCE 0x07       // LIFTOFF_DISTANCE specifies how far from the sensor the trackball is
    #define ROTATIONAL_TRANSFORM_ANGLE 0        // Software adjustment for how not-squarely you packaged the sensor
    #define POINTING_DEVICE_INVERT_X            // Inverted movement for X (not sure why this is set tbh...maybe due to the kb half it's installed on?)
    #define DRAGSCROLL_REVERSE_X                // i must have installed the sensor flipped around
    #define POINTING_DEVICE_TASK_THROTTLE_MS 10 // this ensures that the trackball sensor polling happens only every 10ms
#endif

// WS2812 RGB LED strip input and number of LEDs
#if defined(RGB_MATRIX_ENABLE) || defined(RGB_MATRIX_LEDMAPS_ENABLED)
    #define RGB_DI_PIN GP28
    #define RGBLED_NUM 86                       // Total number of LEDs, total of both halves
    #define RGB_MATRIX_SPLIT { 43, 43 }
    #define RGB_MATRIX_LED_COUNT RGBLED_NUM
    // this brightness is only for 'default' rgb settings; userspace rgb is set in the keymap config.h
    #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 0 // this has no effect unless you eeprom reset  // setting this too high will cause the trackball to reset every min or so, and at highest just brownout entirely
    #define NOP_FUDGE 0.4                       // not sure what this does - some math about rgb brightness or something? - but it won't compile without this set
#endif
