// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "arcboard_mk19.h"
#include "print.h"

#include <qp.h>
#include "qp_st7789.h"
static painter_device_t display;

void keyboard_post_init_user(void) {
    // Customise these values to desired behaviour
    // debug_enable=true;
    // debug_matrix=true;
    // debug_keyboard=true;
    // debug_mouse=true;

    setPinOutput(DISPLAY_BL_PIN);
    writePinLow(DISPLAY_BL_PIN);
    display = qp_st7789_make_spi_device(76, 284, DISPLAY_CS_PIN, DISPLAY_DC_PIN, DISPLAY_RST_PIN, DISPLAY_SPI_DIVISOR, DISPLAY_SPI_MODE);
    qp_init(display, QP_ROTATION_0);
}


void housekeeping_task_user(void) {
    static uint32_t last_draw = 0;
    if (timer_elapsed32(last_draw) > 33) { // Throttle to 30fps
        last_draw = timer_read32();
        qp_rect(display, 0, 0, 75, 283, 0, 0, 255, true);
    }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
        KC_A
    ),
};
