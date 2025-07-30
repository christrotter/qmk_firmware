// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "arcboard_mk19.h"
#include "print.h"

#include <qp.h>
#include "qp_st7789.h"
static painter_device_t display;

#include "graphics/futura40.qff.c"
static painter_font_handle_t font;

void keyboard_post_init_user(void) {
    // Customise these values to desired behaviour
    // debug_enable=true;
    // debug_matrix=true;
    // debug_keyboard=true;
    // debug_mouse=true;
    font = qp_load_font_mem(font_futura40);
    setPinOutput(DISPLAY_BL_PIN);
    writePinLow(DISPLAY_BL_PIN);
    // interesting, the order of the xy in the make_spi_device function doesn't seem to matter?
    display = qp_st7789_make_spi_device(284, 76, DISPLAY_CS_PIN, DISPLAY_DC_PIN, DISPLAY_RST_PIN, DISPLAY_SPI_DIVISOR, DISPLAY_SPI_MODE);
    
    // qp_set_viewport_offsets(display, 82, 18); // for qp_rotation_0
    // qp_set_viewport_offsets(display, 82, 18); // for qp_rotation_270
    qp_set_viewport_offsets(display, 17, 81); // for qp_rotation_270
    qp_init(display, QP_ROTATION_270);
    
}


void housekeeping_task_user(void) {
    static uint32_t last_draw = 0;
    if (timer_elapsed32(last_draw) > 160) { // Throttle to 30fps
        // so 66 is 2px into the display; 64 is our 0
        // qp_rect(display, -64, 64, 128, 128, 255, 255, 255, true);
        // moving x by -10
        // moving xy by 10 moved down-right
        // y=130 is almost the bottom of the display
        //  top left; x, y
        // bot rightx, y
        // where is the top left corner?
        // start by drawing a 20x20; 
        // finally from 0,0/20,20 to 60,60/80,80 we start to see something
        // i reset the viewport offsets to 0,0
        // 82 
        // here the square is 12mm up, 4mm in
        // it is moving up and to the right; what does 20px off the y1 do?
        // changing y1 is doing nothing... what
        // so the y is actually the x; left is 0, moving right is positive numbers
        // lowering the x number moves it downwards
        // so we are looking at bottom left (opposite power/gnd) as 0,0
        // so from 0,0 to 18,82 is a single pixel; so that means 
        // ok, with offset of 17,81, we can now use 0,0 as true zero; i.e. 0,0/1,1 = single bottom-left pixel
        // HOWEVER the x and y are swapsies so you are not seeing x,y but rather y,x
        qp_rect(display, 
            0, 0, 
            284, 76, 
            0, 0, 255,  // White: H=0, S=0, V=255
            true
        );
    }
    if (timer_elapsed32(last_draw) > 33) { // Throttle to 30fps
        last_draw = timer_read32();
        
        static const char *text = "CHROME";
        
        // Get text dimensions
        int16_t text_width = qp_textwidth(font, text);
        
        // Calculate centered position
        int16_t x_centered = (284 - text_width) / 2;
        int16_t y_centered = (76 - font->line_height) / 2;
        
        // Black text on white background using HSV values
        // Black: H=0, S=0, V=0 (no brightness)
        // White: H=0, S=0, V=255 (max brightness, no saturation)
        qp_drawtext_recolor(display, x_centered, y_centered, font, text, 
                           0, 0, 0,    // foreground: black (H, S, V)
                           0, 0, 255); // background: white (H, S, V)
        // qp_flush(display);
    }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
        KC_A
    ),
};
