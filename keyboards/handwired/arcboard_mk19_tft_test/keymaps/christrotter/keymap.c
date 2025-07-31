// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "arcboard_mk19.h"
#include "print.h"

#include "qp_internal.h"
#include "qp_comms.h"
#include "qp_st77xx_opcodes.h"
#include "qp_st7789_opcodes.h"
#include "qp_tft_panel.h"

#include <qp.h>
#include "qp_st7789.h"
static painter_device_t display;

#include "graphics/futura40.qff.c"
static painter_font_handle_t font;

// this is required to invert the colours on the display
bool qp_st7789_init(painter_device_t device, painter_rotation_t rotation) {
    // clang-format off
    const uint8_t st7789_init_sequence[] = {
        // Command,                 Delay, N, Data[N]
        ST77XX_CMD_RESET,            120,  0,
        ST77XX_CMD_SLEEP_OFF,          5,  0,
        ST77XX_SET_PIX_FMT,            0,  1, 0x55,
        ST77XX_CMD_INVERT_OFF,          0,  0,
        ST77XX_CMD_NORMAL_ON,          0,  0,
        ST77XX_CMD_DISPLAY_ON,        20,  0
    };
    // clang-format on
    qp_comms_bulk_command_sequence(device, st7789_init_sequence, sizeof(st7789_init_sequence));

    // Configure the rotation (i.e. the ordering and direction of memory writes in GRAM)
    const uint8_t madctl[] = {
        [QP_ROTATION_0]   = ST77XX_MADCTL_RGB,
        [QP_ROTATION_90]  = ST77XX_MADCTL_RGB | ST77XX_MADCTL_MX | ST77XX_MADCTL_MV,
        [QP_ROTATION_180] = ST77XX_MADCTL_RGB | ST77XX_MADCTL_MX | ST77XX_MADCTL_MY,
        [QP_ROTATION_270] = ST77XX_MADCTL_RGB | ST77XX_MADCTL_MV | ST77XX_MADCTL_MY,
    };
    qp_comms_command_databyte(device, ST77XX_SET_MADCTL, madctl[rotation]);

    return true;
}


void keyboard_post_init_user(void) {
    // Customise these values to desired behaviour
    // debug_enable=true;
    // debug_matrix=true;
    // debug_keyboard=true;
    // debug_mouse=true;
    font = qp_load_font_mem(font_futura40);
    setPinOutput(DISPLAY_BL_PIN);
    writePinLow(DISPLAY_BL_PIN);
    
    display = qp_st7789_make_spi_device(76, 284, DISPLAY_CS_PIN, DISPLAY_DC_PIN, DISPLAY_RST_PIN, DISPLAY_SPI_DIVISOR, DISPLAY_SPI_MODE);
    qp_set_viewport_offsets(display, 81, 17); // for qp_rotation_0
    // if using horizontal orientation, use below, and reverse your x and y numbers when using QP draw functions
    // display = qp_st7789_make_spi_device(284, 76, DISPLAY_CS_PIN, DISPLAY_DC_PIN, DISPLAY_RST_PIN, DISPLAY_SPI_DIVISOR, DISPLAY_SPI_MODE);
    // qp_set_viewport_offsets(display, 17, 81); // for qp_rotation_270
    qp_init(display, QP_ROTATION_0);
    
}


void housekeeping_task_user(void) {
    static uint32_t last_draw = 0;
    if (timer_elapsed32(last_draw) > 160) { // Throttle to 30fps
        qp_rect(display, 
            0, 0, 
            76, 284, 
            HSV_BLACK,  // White: H=0, S=0, V=255
            true
        );
    }
    if (timer_elapsed32(last_draw) > 33) { // Throttle to 30fps
        last_draw = timer_read32();
        
        static const char *text = "C";
        
        // Get text dimensions
        int16_t text_width = qp_textwidth(font, text);
        
        // Calculate centered position
        int16_t x_centered = (76 - text_width) / 2;
        int16_t y_centered = (284 - font->line_height) / 2;

        qp_drawtext_recolor(display, x_centered, y_centered, font, text, 
                           HSV_WHITE,
                           HSV_BLACK);
    }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
        KC_A
    ),
};
