// Copyright 2021 Mikael Manukyan <arm.localhost@gmail.com>
// Copyright 2023 Chris Trotter (@christrotter)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

// these need to match the rgb matrix led count/layout
/*
    Physical layout:
               #### LEFT FOOT ####            ###               #### RIGHT FOOT ####
    botL(1), botR(2), topL(3), topR(4),         desk1     ###      botL, botR, topL, topR,         desk1
    sideL(5), sideR(6), heelL(7), heelR(8),     desk2     ###      sideL, sideR, heelL, heelR,     desk2

    should lay this out nicer...
*/
/*
this is what we're seeing...
bot-L:  00: 10000000         bot-R:  00: 01000000
top-L:  01: 10000000         top-R:  00: 00100000
side-L: 01: 00100000         side-R: 00: 00010000
heel-L: 01: 01000000         heel-R: 01: 00010000

bot-L:  row0,col0         bot-R:  row0,col1
top-L:  row1,col0         top-R:  row0,col2
side-L: row1,col2         side-R: row0,col3
heel-L: row1,col1         heel-R: row1,col3

so this is what is electrically wired up...
0,0 
0,1
1,0 
0,2
1,2 
0,3
1,1 
1,3

    LM_00_1, LM_00_2, LM_00_3, \
    LM_01_1, LM_01_2, LM_01_3, \
    LM_02_1, LM_02_2, LM_02_3, \
    LM_03_1, LM_03_2, LM_03_3, \
    LM_10_1, LM_10_2, LM_10_3, \
    LM_11_1, LM_11_2, LM_11_3, \
    LM_12_1, LM_12_2, LM_12_3, \
    LM_13_1, LM_13_2, LM_13_3, \
    RM_00_1, RM_00_2, RM_00_3, \
    RM_01_1, RM_01_2, RM_01_3, \
    RM_02_1, RM_02_2, RM_02_3, \
    RM_03_1, RM_03_2, RM_03_3, \
    RM_10_1, RM_10_2, RM_10_3, \
    RM_11_1, RM_11_2, RM_11_3, \
    RM_12_1, RM_12_2, RM_12_3, \
    RM_13_1, RM_13_2, RM_13_3 \

            { "flags": 4, "matrix": [0, 0], "x": 0, "y": 0}, correct
            { "flags": 4, "matrix": [0, 0], "x": 0, "y": 0}, correct
            { "flags": 4, "matrix": [0, 0], "x": 0, "y": 0}, correct
            { "flags": 4, "matrix": [0, 1], "x": 1, "y": 0},correct
            { "flags": 4, "matrix": [0, 1], "x": 1, "y": 0},correct
            { "flags": 4, "matrix": [0, 1], "x": 1, "y": 0},correct
            { "flags": 4, "matrix": [1, 0], "x": 4, "y": 0}, offbyone
            { "flags": 4, "matrix": [1, 0], "x": 4, "y": 0},
            { "flags": 4, "matrix": [1, 0], "x": 4, "y": 0},
            { "flags": 4, "matrix": [0, 2], "x": 2, "y": 0},
            { "flags": 4, "matrix": [0, 2], "x": 2, "y": 0},
            { "flags": 4, "matrix": [0, 2], "x": 2, "y": 0},
            { "flags": 4, "matrix": [1, 2], "x": 6, "y": 0},
            { "flags": 4, "matrix": [1, 2], "x": 6, "y": 0},
            { "flags": 4, "matrix": [1, 2], "x": 6, "y": 0},
            { "flags": 4, "matrix": [0, 3], "x": 3, "y": 0},
            { "flags": 4, "matrix": [0, 3], "x": 3, "y": 0},
            { "flags": 4, "matrix": [0, 3], "x": 3, "y": 0},
            { "flags": 4, "matrix": [1, 1], "x": 5, "y": 0},
            { "flags": 4, "matrix": [1, 1], "x": 5, "y": 0},
            { "flags": 4, "matrix": [1, 1], "x": 5, "y": 0},
            { "flags": 4, "matrix": [1, 3], "x": 7, "y": 0},
            { "flags": 4, "matrix": [1, 3], "x": 7, "y": 0},
            { "flags": 4, "matrix": [1, 3], "x": 7, "y": 0},

    LM_00_1, LM_00_2, LM_00_3, \ red
    LM_01_1, LM_01_2, LM_01_3, \ yellow
    LM_11_1, LM_11_2, LM_11_3, \ green
    LM_12_1, LM_12_2, LM_12_3, \ blue
    LM_10_1, LM_10_2, LM_10_3, \ orange?
    LM_03_1, LM_03_2, LM_03_3, \ orange
    LM_02_1, LM_02_2, LM_02_3, \ cyan?
    LM_13_1, LM_13_2, LM_13_3, \ cyan?

    botL    #define L_B1_L2 {HSV_RED}
    botR    #define L_B2_L2 {HSV_YELLOW}
    topL    #define L_B3_L2 {HSV_ORANGE}
    topR    #define L_B4_L2 {HSV_ORANGE}
    sideL   #define L_B5_L2 {HSV_GREEN}
    sideR   #define L_B6_L2 {HSV_BLUE}
    heelL   #define L_B7_L2 {HSV_SPRINGGREEN}
    heelR   #define L_B8_L2 {HSV_SPRINGGREEN}

    #define L_B1_L2 {HSV_RED}
    #define L_B2_L2 {HSV_YELLOW}
    #define L_B3_L2 {HSV_ORANGE}
    #define L_B4_L2 {HSV_ORANGE}
    #define L_B5_L2 {HSV_GREEN}
    #define L_B6_L2 {HSV_BLUE}
    #define L_B7_L2 {HSV_SPRINGGREEN}
    #define L_B8_L2 {HSV_SPRINGGREEN}

    LM_10_1, LM_10_2, LM_10_3, \ 
    LM_03_1, LM_03_2, LM_03_3, \
    LM_02_1, LM_02_2, LM_02_3, \
    LM_13_1, LM_13_2, LM_13_3, \

    LM_00_1, LM_00_2, LM_00_3, \ botL
    LM_01_1, LM_01_2, LM_01_3, \ botR
    LM_13_1, LM_13_2, LM_13_3, \ 
    LM_11_1, LM_11_2, LM_11_3, \ sideR
    LM_12_1, LM_12_2, LM_12_3, \
    LM_10_1, LM_10_2, LM_10_3, \
    LM_03_1, LM_03_2, LM_03_3, \
    LM_02_1, LM_02_2, LM_02_3, \

    red         = 00
    orange      = 01
    yellow      = 02
    green       = 03
    springgreen = 10
    cyan        = 11
    blue        = 12
    purple      = 13

i think the silkscreen is messed, or something...
can be re-worked in info.json - actually no; here only
info.json is only useful for flags at this point.
so why is the ordering seemingly dynamic??
why does this seem to happen on every build...

LEFT
- definitely messed up something in the pcb?
- getting mirroring right from kicad -> wiring -> info.json -> ledmap
left side should be wired up as per how you'd set the keymap/ledmap
- maybe i need to start w. keymap/ledmap, work backwards?

Sequence: location: matrix location actually reported in console
LEFT
0: bot-toe-inner:   0,1
1: bot-toe-outer:   0,0
2: top-toe-inner:   0,2 
3: top-toe-outer:   1,0 why is this not 0,3? -> pcb issue
4: long-inner:      0,3
5: long-outer:      1,2
6: heel-inner:      1,3
7: heel-outer:      1,1

RIGHT
0: bot-toe-inner    2,0
1: bot-toe-outer    2,1
2: top-toe-inner    2,2
3: top-toe-outer    3,0
4: long-inner:      2,3
5: long-outer:      3,2
6: heel-inner:      3,1
7: heel-outer:      3,3

- these match; wiring has been done correctly

right side problems:
- inner-heel is not the right keycode; swapped with outer-long; this is working fine on the left side
*/

#define LEDMAP( \
    LM_00_1, LM_00_2, LM_00_3, \
    LM_01_1, LM_01_2, LM_01_3, \
    LM_02_1, LM_02_2, LM_02_3, \
    LM_03_1, LM_03_2, LM_03_3, \
    LM_10_1, LM_10_2, LM_10_3, \
    LM_11_1, LM_11_2, LM_11_3, \
    LM_12_1, LM_12_2, LM_12_3, \
    LM_13_1, LM_13_2, LM_13_3, \
    RM_00_1, RM_00_2, RM_00_3, \
    RM_01_1, RM_01_2, RM_01_3, \
    RM_02_1, RM_02_2, RM_02_3, \
    RM_03_1, RM_03_2, RM_03_3, \
    RM_10_1, RM_10_2, RM_10_3, \
    RM_11_1, RM_11_2, RM_11_3, \
    RM_12_1, RM_12_2, RM_12_3, \
    RM_13_1, RM_13_2, RM_13_3 \
) { \
    LM_00_1, LM_00_2, LM_00_3, \
    LM_01_1, LM_01_2, LM_01_3, \
    LM_02_1, LM_02_2, LM_02_3, \
    LM_10_1, LM_10_2, LM_10_3, \
    LM_03_1, LM_03_2, LM_03_3, \
    LM_12_1, LM_12_2, LM_12_3, \
    LM_11_1, LM_11_2, LM_11_3, \
    LM_13_1, LM_13_2, LM_13_3, \
    RM_00_1, RM_00_2, RM_00_3, \
    RM_01_1, RM_01_2, RM_01_3, \
    RM_02_1, RM_02_2, RM_02_3, \
    RM_10_1, RM_10_2, RM_10_3, \
    RM_03_1, RM_03_2, RM_03_3, \
    RM_12_1, RM_12_2, RM_12_3, \
    RM_11_1, RM_11_2, RM_11_3, \
    RM_13_1, RM_13_2, RM_13_3 \
}

typedef uint8_t ledmap[RGB_MATRIX_LED_COUNT][3];
extern const ledmap ledmaps[];

// void set_rgb_ledmap(uint8_t first_led, uint8_t last_led, int val, int layer);
void set_rgb_ledmap(uint16_t first_led, uint16_t last_led, int val, int layer);
void set_rgb_range(uint16_t first_led, uint16_t last_led, int hue, int sat, int val, int val_override);
// void set_rgb_array(uint8_t ledArray[], int hue, int sat, int val);

void rgb_matrix_layers_enable(void);     // do we need this?
void rgb_matrix_layers_disable(void);    // do we need this?
bool rgb_matrix_indicators_keymap(void); // do we need this?
bool rgb_matrix_indicators_advanced_keymap(uint8_t led_min, uint8_t led_max);
