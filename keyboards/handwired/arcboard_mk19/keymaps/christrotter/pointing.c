// Copyright 2023 Chris Trotter (@christrotter)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

void pointing_device_init_user(void) {
    set_auto_mouse_layer(AUTO_MOUSE_DEFAULT_LAYER);
    set_auto_mouse_enable(true);
}
