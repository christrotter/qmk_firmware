// Copyright 2023 Chris Trotter (@christrotter)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include QMK_KEYBOARD_H
#include "arcboard_mk19.h"
#include "keymap.h"

void pointing_device_init_user(void) {
    set_auto_mouse_layer(AUTO_MOUSE_DEFAULT_LAYER);
    set_auto_mouse_enable(true);
}
