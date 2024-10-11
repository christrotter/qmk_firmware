// Copyright 2022 Chris Trotter (@christrotter)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "arcboard_mk13.h"
#include "string.h"
#include <hal.h>
#include "split_util.h"
#include "spi_master.h"

#ifdef QUANTUM_PAINTER_ENABLE
    bool lcd_power = false;
#endif

// clang-format off
    /* row,col
     * ,------------------------------------------------,                             ,------------------------------------------------,
     * |  1,1 |  1,2 |  1,3 |  1,4 |  1,5 |  1,6 |  1,7 |                             |  1,1 |  1,2 |  1,3 |  1,4 |  1,5 |  1,6 |  1,7 |
     * |------+------+------+------+------+------+------|                             |------+------+------+------+------+------+------|
     * |  2,1 |  2,2 |  2,3 |  2,4 |  2,5 |  2,6 |  2,7 |                             |  2,1 |  2,2 |  2,3 |  2,4 |  2,5 |  2,6 |  2,7 |
     * |------+------+------+------+------+------+------|                             |------+------+------+------+------+------+------|
     * |  3,1 |  3,2 |  3,3 |  3,4 |  3,5 |  3,6 |  3,7 |                             |  3,1 |  3,2 |  3,3 |  3,4 |  3,5 |  3,6 |  3,7 |
     * |------+------+------+------+------+------+------|                             |------+------+------+------+------+------+------|
     * |  4,1 |  4,2 |  4,3 |  4,4 |  4,5 |  4,6 |  4,7 |                             |  4,1 |  4,2 |  4,3 |  4,4 |  4,5 |  4,6 |  4,7 |
     * |------+------+------+------+------+------+------|                             |------+------+------+------+------+------+------|
     * |  5,1 |  5,2 |  5,3 |  5,4 |  5,5 |  5,6 |  5,7 |                             |  5,1 |  5,2 |  5,3 |  5,4 |  5,5 |  5,6 |  5,7 |
     * |------+------+------+------+------+------+------+------,        ,------|------+------+----+-+----+-+------+------+------|------|
     *               |  6,1 | 6,2  |             | 7,6  | 7,5  |        | 7,1  | trackball | 7,5  | 7,6  | |  6,1 | 6,2  |
     *               `------+------+------+------+------+------|        '-+----'-+-----,---+------+------+ '------+------+
     *                             | 7,1  | 7,2  | 7,3  | 7,4  |                 | 7,3 | 7,4  |
     *                             '------+------+------+------'              ,--+-----+------'
     *                                                                        | 7,2  |
     *                                                                        '------'
     */
    // the left thumb ordering might be backwards..
// clang-format on

#if defined(RGB_MATRIX_ENABLE) || defined(RGB_MATRIX_LEDMAPS_ENABLED)
    led_config_t g_led_config = {
    // Key Matrix to LED Index - this is used to provide the 'default' white colour
    {
        { 0, 1, 2, 3, 4, 5, 6 },
        { 7, 8, 9, 10, 11, 12, 13 },
        { 14, 15, 16, 17, 18, 19, 20 },
        { 21, 22, 23, 24, 25, 26, 27 },
        { 28, 29, 30, 31, 32, 33, 34 },
        { 35, 36 },
        { 37, 38, 39, 40, 41, 42 },
        { 43, 44, 45, 46, 47, 48, 49 },
        { 50, 51, 52, 53, 54, 55, 56 },
        { 57, 58, 59, 60, 61, 62, 63 },
        { 64, 65, 66, 67, 68, 69, 70 },
        { 71, 72, 73, 74, 75, 76, 77 },
        { 78, 79 },
        { 80, 81, 82, 83, 84, 85 },
    },
    // LED Index to Physical Position
    {
        { 102,   0 }, {  81,   0 }, {  61,   0 }, {  41,   0 }, {  20,   0 }, {   0,   0 }, { 102,   0 },
        { 102,  16 }, {  81,  16 }, {  61,  16 }, {  41,  16 }, {  20,  16 }, {   0,  16 }, { 102,   0 },
        { 102,  32 }, {  81,  32 }, {  61,  32 }, {  41,  32 }, {  20,  32 }, {   0,  32 }, { 102,   0 },
        { 102,  48 }, {  81,  48 }, {  61,  48 }, {  41,  48 }, {  20,  48 }, {   0,  48 }, { 102,   0 },
        { 102,  64 }, {  81,  64 },
        { 102,   0 }, { 102,   0 }, { 102,   0 }, { 102,   0 }, { 102,   0 }, { 102,   0 },
        { 224,   0 }, { 204,   0 }, { 183,   0 }, { 163,   0 }, { 143,   0 }, { 122,   0 }, { 102,   0 },
        { 224,  16 }, { 204,  16 }, { 183,  16 }, { 163,  16 }, { 143,  16 }, { 122,  16 }, { 102,   0 },
        { 224,  32 }, { 204,  32 }, { 183,  32 }, { 163,  32 }, { 143,  32 }, { 122,  32 }, { 102,   0 },
        { 224,  48 }, { 204,  48 }, { 183,  48 }, { 163,  48 }, { 143,  48 }, { 122,  48 }, { 102,   0 },
        { 224,  64 }, { 204,  64 }, { 183,  64 }, { 163,  64 }, { 143,  64 }, { 122,  64 }, { 102,   0 },
        { 102,   0 }, { 102,   0 },
        { 102,   0 }, { 102,   0 }, { 102,   0 }, { 102,   0 }, { 102,   0 }, { 102,   0 },
    },
    // LED type bit mask - 4 is per-key
    {
            4, 4, 4, 4, 4, 4, 4,
            4, 4, 4, 4, 4, 4, 4,
            4, 4, 4, 4, 4, 4, 4,
            4, 4, 4, 4, 4, 4, 4,
            4, 4, 4, 4, 4, 4, 4,
                    4, 4,
                    4, 4, 4, 4, 4, 4,
            4, 4, 4, 4, 4, 4, 4,
            4, 4, 4, 4, 4, 4, 4,
            4, 4, 4, 4, 4, 4, 4,
            4, 4, 4, 4, 4, 4, 4,
            4, 4, 4, 4, 4, 4, 4,
        4, 4,
        4, 4, 4, 4, 4, 4
    }
    };
#endif

////  QUANTUM PAINTER SECTION  ////

#ifdef QUANTUM_PAINTER_ENABLE
    #include "qp_st7789.h"
    extern painter_device_t qp_display;
    __attribute__((weak)) void draw_ui_user(void) {} //_user should not be in the keyboard.c
    __attribute__((weak)) void ui_init(void) {}
#endif
void keyboard_post_init_kb(void) {
    #ifdef QUANTUM_PAINTER_ENABLE
        ui_init(); //initialize display // if this is missing you will crash qmk on kb boot
        wait_ms(50);
    #endif
    keyboard_post_init_user(); //_user should not be in the keyboard.c
}

void housekeeping_task_kb(void) {
    #ifdef QUANTUM_PAINTER_ENABLE
        // set the lcd_power state bool based on matrix activity vs. SCREEN_TIMEOUT value
        lcd_power = (last_input_activity_elapsed() < SCREEN_TIMEOUT) ? 1 : 0;
        setPinOutput(BACKLIGHT_PIN);
        if (lcd_power) {
            writePinHigh(BACKLIGHT_PIN);
        } else {
            writePinLow(BACKLIGHT_PIN);
        }
        if (lcd_power) {
            draw_ui_user(); //_user should not be in the keyboard.c
        }
    #endif // QUANTUM_PAINTER_ENABLE
}

// Forward declare RP2040 SDK declaration.
void gpio_init(uint gpio);

void matrix_slave_scan_keymap(void);
