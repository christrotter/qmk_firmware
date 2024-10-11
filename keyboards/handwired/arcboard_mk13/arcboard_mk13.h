// Copyright 2022 Chris Trotter (@christrotter)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"
#include QMK_KEYBOARD_H

#if defined(RGB_MATRIX_LEDMAPS_ENABLED)
    #include "rgb_ledmaps.h"
#endif
bool process_record_keymap(uint16_t keycode, keyrecord_t *record);
void post_process_record_keymap(uint16_t keycode, keyrecord_t *record);

// this feels kinda janky...is it really needed?
#ifdef QUANTUM_PAINTER_ENABLE
    #include <qp.h>
    #pragma pack(push)
    #pragma pack(1)
    extern painter_device_t st7789;
    #pragma pack(pop)
#endif // QUANTUM_PAINTER_ENABLE

enum userspace_layers {
    _QWERTY             = 0,
    FIRST_DEFAULT_LAYER = 0,
    _SYMBOLS,
    _MOUSE,
    _NAV,
};

#define _MACROS _MOUSE

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
     *               |  6,1 | 6,2  |             | 7,1  | 7,2  |        | 7,1  | trackball | 7,5  | 7,6  | |  6,1 | 6,2  |
     *               `------+------+------+------+------+------|        '-+----'-+-----,---+------+------+ '------+------+
     *                             | 7,6  | 7,5  | 7,4  | 7,3  |                 | 7,3 | 7,4  |
     *                             '------+------+------+------'              ,--+-----+------'
     *                                                                        | 7,2  |
     *                                                                        '------'
     */
// clang-format on

#define LAYOUT( \
    LM_11, LM_12, LM_13, LM_14, LM_15, LM_16, LM_17,                    RM_11, RM_12, RM_13, RM_14, RM_15, RM_16, RM_17, \
    LM_21, LM_22, LM_23, LM_24, LM_25, LM_26, LM_27,                    RM_21, RM_22, RM_23, RM_24, RM_25, RM_26, RM_27, \
    LM_31, LM_32, LM_33, LM_34, LM_35, LM_36, LM_37,                    RM_31, RM_32, RM_33, RM_34, RM_35, RM_36, RM_37, \
    LM_41, LM_42, LM_43, LM_44, LM_45, LM_46, LM_47,                    RM_41, RM_42, RM_43, RM_44, RM_45, RM_46, RM_47, \
    LM_51, LM_52, LM_53, LM_54, LM_55, LM_56, LM_57,                    RM_51, RM_52, RM_53, RM_54, RM_55, RM_56, RM_57, \
                  LM_61, LM_62,                                                              RM_61, RM_62, \
                LT_76, LT_75, LT_74, LT_73, LT_72, LT_71, RT_71, RT_72, RT_73, RT_74, RT_75, RT_76 \
) \
{ \
    { LM_11, LM_12, LM_13, LM_14, LM_15, LM_16, LM_17 }, \
    { LM_21, LM_22, LM_23, LM_24, LM_25, LM_26, LM_27 }, \
    { LM_31, LM_32, LM_33, LM_34, LM_35, LM_36, LM_37 }, \
    { LM_41, LM_42, LM_43, LM_44, LM_45, LM_46, LM_47 }, \
    { LM_51, LM_52, LM_53, LM_54, LM_55, LM_56, LM_57 }, \
    { XXX,   XXX,   LM_61, LM_62, XXX,   XXX,   XXX  }, \
    { LT_76, LT_75, LT_74, LT_73, LT_72, LT_71, XXX }, \
    { RM_11, RM_12, RM_13, RM_14, RM_15, RM_16, RM_17 }, \
    { RM_21, RM_22, RM_23, RM_24, RM_25, RM_26, RM_27 }, \
    { RM_31, RM_32, RM_33, RM_34, RM_35, RM_36, RM_37 }, \
    { RM_41, RM_42, RM_43, RM_44, RM_45, RM_46, RM_47 }, \
    { RM_51, RM_52, RM_53, RM_54, RM_55, RM_56, RM_57 }, \
    { XXX,   XXX,   XXX,   RM_61, RM_62, XXX,   XXX  }, \
    { RT_71, RT_72, RT_73, RT_74, RT_75, RT_76, XXX }, \
}

// clang-format on

#ifdef POINTING_DEVICE_ENABLE
    enum board_keycodes {
        DRAG_SCROLL,
        BOARD_SAFE_RANGE,
    };
    #define DRGSCRL DRAG_SCROLL

    bool board_get_pointer_dragscroll_enabled(void);
#endif // POINTING_DEVICE_ENABLE

void keyboard_post_init_transport_sync(void);
void housekeeping_task_transport_sync(void);

void matrix_init_sub_kb(void);
void matrix_scan_sub_kb(void);
bool process_record_user_rgb_matrix(uint16_t keycode, keyrecord_t *record); //_user should not be in the keyboard.c
