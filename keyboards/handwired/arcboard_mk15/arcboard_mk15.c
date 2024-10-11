// Copyright 2022 Chris Trotter (@christrotter)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "arcboard_mk15.h"

// clang-format off
    /* row,col
     * .------+------+------+------+------+------.                                                       .------+------+------+------+------+------.
     * |  1,1 |  1,2 |  1,3 |  1,4 |  1,5 |  1,6 |                                                       |  1,1 |  1,2 |  1,3 |  1,4 |  1,5 |  1,6 |
     * |------+------+------+------+------+------|                                                       |------+------+------+------+------+------|
     * |  2,1 |  2,2 |  2,3 |  2,4 |  2,5 |  2,6 |                                                       |  2,1 |  2,2 |  2,3 |  2,4 |  2,5 |  2,6 |
     * |------+------+------+------+------+------|                                                       |------+------+------+------+------+------|
     * |  3,1 |  3,2 |  3,3 |  3,4 |  3,5 |  3,6 |                                                       |  3,1 |  3,2 |  3,3 |  3,4 |  3,5 |  3,6 |
     * |------+------+------+------+------+------|                                                       |------+------+------+------+------+------|
     * |  4,1 |  4,2 |  4,3 |  4,4 |  4,5 |  4,6 |                                                       |  4,1 |  4,2 |  4,3 |  4,4 |  4,5 |  4,6 |
     * '------+------+------+------+------+------+------+------+------.             .------+------+------+------+------+------+------+------+------'
     *        |  trackball  |  5,1 |  5,2 |------|  6,1 |  6,2 |  6,3 |             |  6,1 |  6,2 |  6,3 |------|  5,1 |  5,2 |  trackball  |
     *        '-------------+------+------+------+------+------+------'             +------+------+------+------+------+------+-------------'
     *                      |  5,3 |  5,4 |  5,5 |  6,3 |  6,4 |                    |  6,3 |  6,4 |             |  5,3 |  5,4 |  5,5 |
     *                      '------+------+------+------+------' .------.  .------. '------+------'             +------+------+------'
     *                             |  5,6 |          |  6,5 |    |  6,6 |  |  6,6 |     |  6,5 |                       |  5,6 |
     *                             '------'          '------'    '------'  '------'     '------'                       '------'
     * 5,1-5,6  = thumb keys
     * 6,1-6,4  = 5-way/dpad up/down/left/right
     * 6,5      = 5-way/dpad button
     * 6,6      = falcon button
     */
// clang-format on

/*
    LED chain is as follows:
    30x2 LEDs for the keys ((4x6 + 6) +2 sides), 12 LEDs for each falcon, 14 LEDs for each indicator strip
    Keys-L(0-29) -> Falcon-L(60-71) -> Indicators-L(84-97) -> Keys-R(30-59) -> Falcon-R(72-83) -> Indicators-R(98-111)
    Indicators can be further broken up into banks.
*/

#if defined(RGB_MATRIX_ENABLE) || defined(RGB_MATRIX_LEDMAPS_ENABLED)
led_config_t g_led_config = {
    // Key Matrix to LED Index - this is used to provide the 'default' white colour
    // This is just the keys leds, not falcon or indicators.
    {
        { 0,  1,  2,  3,  4,  5  },         // Left, main
        { 6,  7,  8,  9,  10, 11 },         // Left, main
        { 12, 13, 14, 15, 16, 17 },         // Left, main
        { 18, 19, 20, 21, 22, 23 },         // Left, main
        { 24, 25, 26, 27, 28, 29 },         // Left, thumb
        { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED }, // Left, dpad
        { 30, 31, 32, 33, 34, 35 },         // Left, Falcon
        { 36, 37, 38, 39, 40, 41 },         // Left, Falcon
        { 42, 43, 44, 45, 46, 47 },         // Left, indicator strip
        { 48, 49, 50, 51, 52, 53 },         // Left, indicator strip
        { 54, 55 },                         // Left, indicator strip
        { 56, 57, 58, 59, 60, 61 },         // Right, main
        { 62, 63, 64, 65, 66, 67 },         // Right, main
        { 68, 69, 70, 71, 72, 73 },         // Right, main
        { 74, 75, 76, 77, 78, 79 },         // Right, main
        { 80, 81, 82, 83, 84, 85 },         // Right, thumb
        { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED }, // Right, dpad
        { 86, 87, 88, 89, 90, 91 },         // Right, Falcon
        { 92, 93, 94, 95, 96, 97 },         // Right, Falcon
        { 98, 99, 100, 101, 102, 103 },     // Right, indicator strip
        { 104, 105, 106, 107, 108, 109 },   // Right, indicator strip
        { 110, 111 }                        // Right, indicator strip
    },
    // LED Index to Physical Position
    // only used for animations, but necessary for qmk to compile
    // include every LED here
    // needs to match entire led chain, not just keys
    {
        { 102,   0 }, {  81,   0 }, {  61,   0 }, {  41,   0 }, {  20,   0 }, {   0,   0 },
        { 102,  16 }, {  81,  16 }, {  61,  16 }, {  41,  16 }, {  20,  16 }, {   0,  16 },
        { 102,  32 }, {  81,  32 }, {  61,  32 }, {  41,  32 }, {  20,  32 }, {   0,  32 },
        { 102,  48 }, {  81,  48 }, {  61,  48 }, {  41,  48 }, {  20,  48 }, {   0,  48 },
        { 224,   0 }, { 204,   0 }, { 183,   0 }, { 163,   0 }, { 143,   0 }, { 122,   0 },
        { 224,  64 }, { 204,  64 }, { 183,  64 }, { 163,  64 }, { 143,  64 }, { 122,  64 }, { 224,  64 }, { 204,  64 }, { 183,  64 }, { 163,  64 }, { 143,  64 }, { 122,  64 },
        { 224,  64 }, { 204,  64 }, { 183,  64 }, { 163,  64 }, { 143,  64 }, { 122,  64 }, { 224,  64 }, { 204,  64 }, { 183,  64 }, { 163,  64 }, { 143,  64 }, { 122,  64 }, { 143,  64 }, { 122,  64 },
        { 224,  16 }, { 204,  16 }, { 183,  16 }, { 163,  16 }, { 143,  16 }, { 122,  16 },
        { 224,  32 }, { 204,  32 }, { 183,  32 }, { 163,  32 }, { 143,  32 }, { 122,  32 },
        { 224,  48 }, { 204,  48 }, { 183,  48 }, { 163,  48 }, { 143,  48 }, { 122,  48 },
        { 224,  64 }, { 204,  64 }, { 183,  64 }, { 163,  64 }, { 143,  64 }, { 122,  64 },
        { 224,  64 }, { 204,  64 }, { 183,  64 }, { 163,  64 }, { 143,  64 }, { 122,  64 },
        { 224,  64 }, { 204,  64 }, { 183,  64 }, { 163,  64 }, { 143,  64 }, { 122,  64 }, { 224,  64 }, { 204,  64 }, { 183,  64 }, { 163,  64 }, { 143,  64 }, { 122,  64 },
        { 224,  64 }, { 204,  64 }, { 183,  64 }, { 163,  64 }, { 143,  64 }, { 122,  64 }, { 224,  64 }, { 204,  64 }, { 183,  64 }, { 163,  64 }, { 143,  64 }, { 122,  64 }, { 143,  64 }, { 122,  64 },
    },
    // LED type bit mask - 4 is per-key
    // include every LED here
    // ordered by keys+thumbL, keys+thumbR, falconL, falconR, indicatorL, indicatorR
    // remember the 5-way/dpad has no LEDs, and occupies a row
    {
            4, 4, 4, 4, 4, 4,
            4, 4, 4, 4, 4, 4,
            4, 4, 4, 4, 4, 4,
            4, 4, 4, 4, 4, 4,
            4, 4, 4, 4, 4, 4,
            4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
            1, 1, 1, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
            4, 4, 4, 4, 4, 4,
            4, 4, 4, 4, 4, 4,
            4, 4, 4, 4, 4, 4,
            4, 4, 4, 4, 4, 4,
            4, 4, 4, 4, 4, 4,
            4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
            1, 1, 1, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8
    }
};
#endif



void keyboard_post_init_kb(void) {
    pointing_device_set_cpi_on_side(true, LEFT_PMW_CPI);
    pointing_device_set_cpi_on_side(false, RIGHT_PMW_CPI);
    // if (is_keyboard_left()) {
    //     // pointing_device_set_cpi_on_side(true, LEFT_PMW_CPI);    //Set cpi on left side to a low value for slower scrolling.
    //     pointing_device_set_cpi(LEFT_PMW_CPI);
    //     uprintf("Our Left CPI:  %d \n", pointing_device_get_cpi());
    // } else {
    //     // pointing_device_set_cpi_on_side(false, RIGHT_PMW_CPI);  //Set cpi on right side to a reasonable value for mousing.
    //     // pointing_device_set_cpi_on_side(false, RIGHT_PMW_CPI);
    //     pointing_device_set_cpi(RIGHT_PMW_CPI);
    //     uprintf("Our Right CPI: %d \n", pointing_device_get_cpi());
    // }
    keyboard_post_init_user(); //_user should not be in the keyboard.c
}

// Forward declare RP2040 SDK declaration.
void gpio_init(uint gpio);

void matrix_slave_scan_keymap(void);
