// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┐
     * │ A │
     * └───┘
     */
    [0] = LAYOUT(
        EE_CLR, RM_TOGG, KC_A, KC_A, KC_A, KC_A, KC_A
    )
};

#if defined(CONSOLE_ENABLE)
    #include "print.h"
    void keyboard_post_init_user(void) {
        // todo: some code that takes gpio state and combines into logic
        // setPinOutput("GPIO18");
        // writePinLow("GPIO18");
        // setPinOutput("GPIO19");
        // writePinLow("GPIO19");
        // setPinOutput("GPIO20");
        // writePinLow("GPIO20");
        // setPinOutput("GPIO21");
        // writePinLow("GPIO21");
    }
#endif

