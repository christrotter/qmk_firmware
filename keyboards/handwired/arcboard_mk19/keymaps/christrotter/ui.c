// Copyright 2023 Chris Trotter (@christrotter)
// SPDX-License-Identifier: GPL-2.0-or-later

#include <qp.h>
#include "arcboard_mk19.c"
#include "graphics/futura40.qff.c"
#include "graphics/awesome.qgf.h"
#include "graphics/disappointed_guy.qgf.h"
#include "graphics/roger.qgf.h"
#include "graphics/qmk-logo.qgf.h"

bool lcd_power;

static painter_font_handle_t font;
static painter_image_handle_t awesome;
static painter_image_handle_t disappointed_guy;
static painter_image_handle_t roger;
static painter_image_handle_t qmk_logo;
static painter_device_t display1;
static painter_device_t display2;

const char *current_layer_name(void) {
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            return "qwerty";
        case _NAV:
            return "nav";
        case _SYMBOLS:
            return "symbols";
        case _MOUSE:
            return "mouse";
    }
    return "unknown";
}

void init_ui(void) {
    font = qp_load_font_mem(font_futura40);
    awesome = qp_load_image_mem(gfx_awesome);
    disappointed_guy = qp_load_image_mem(gfx_disappointed_guy);
    roger = qp_load_image_mem(gfx_roger);
    qmk_logo = qp_load_image_mem(gfx_qmk_logo);

    display1 = qp_gc9a01_make_spi_device(240, 240, DISPLAY2_CS_PIN, DISPLAY_DC_PIN, DISPLAY_RST_PIN, DISPLAY_SPI_DIVISOR, DISPLAY_SPI_MODE);
    qp_init(display1, QP_ROTATION_0);
    // when you init display1, b/c they share rst pin, you do something to reset; running it again when init-ing display2 un-does all your init?
    display2 = qp_gc9a01_make_spi_device(240, 240, DISPLAY1_CS_PIN, DISPLAY_DC_PIN, NO_PIN, DISPLAY_SPI_DIVISOR, DISPLAY_SPI_MODE);
    qp_init(display2, QP_ROTATION_270);

    setPinOutput(DISPLAY_LED_PIN);
    writePinHigh(DISPLAY_LED_PIN);

    qp_rect(display1, 0, 0, 240, 240, HSV_CYAN, true);
    qp_rect(display2, 0, 0, 240, 240, HSV_CYAN, true);

    qp_drawimage(display1, 0, 0, qmk_logo);
    qp_drawimage(display2, 0, 0, qmk_logo);

    qp_flush(display2);
    qp_flush(display1);
    
}

void draw_ui_user(void) {
    // if (qp_lvgl_attach(display1)) {     // Attach LVGL to the display
    //     // ...Your code to draw           // Run LVGL specific code to draw
    // }
    // then detach lvgl!!!
    // if (!(is_keyboard_left())) {
       // uint16_t width;
       // uint16_t height;
       // qp_get_geometry(display1, &width, &height, NULL, NULL, NULL);
       // #if defined(CONSOLE_ENABLE)
       //     char buf[32] = {0};
       // #endif
       // bool layer_state_redraw = false;
       // static uint32_t last_layer_state   = 0;
       // if (last_layer_state  != layer_state) {
       //     last_layer_state   = layer_state;
       //     layer_state_redraw = true;
       // }
       // if (layer_state_redraw) {
       //     extern const char *current_layer_name(void);
       //     const char        *layer_name = current_layer_name();
       //     const char        *mouse = "mouse";
       //     const char        *qwerty = "qwerty";
       //     const char        *nav = "nav";
       //     const char        *symbols = "symbols";
       //     int ypos = 150;
       //     #if defined(CONSOLE_ENABLE)
       //         snprintf(buf, sizeof(buf), "%s", layer_name);
       //     #endif
       //     int mouse_layer = strcmp(layer_name, mouse);
       //     int qwerty_layer = strcmp(layer_name, qwerty);
       //     int nav_layer = strcmp(layer_name, nav);
       //     int symbols_layer = strcmp(layer_name, symbols);
       //     qp_rect(display1, 0, 0, 240, 240, HSV_BLUE, true);
       //     qp_rect(display2, 0, 0, 240, 240, HSV_BLUE, true);
       //     if (qwerty_layer==0) {
       //         qp_drawtext_recolor(display1, 35, ypos, font, "QWERTY1 ", HSV_WHITE, HSV_BLACK);
       //         qp_drawtext_recolor(display2, 35, ypos, font, "QWERTY2 ", HSV_WHITE, HSV_BLACK);
       //     }
       //     if (mouse_layer==0) {
       //         qp_drawtext_recolor(display1, 45, ypos, font, "MOUSE1  ", HSV_WHITE, HSV_BLACK);
       //         qp_drawtext_recolor(display2, 45, ypos, font, "MOUSE2  ", HSV_WHITE, HSV_BLACK);
       //     }
       //     if (nav_layer==0) {
       //         qp_drawtext_recolor(display1, 75, ypos, font, "NAV1    ", HSV_WHITE, HSV_BLACK);
       //         qp_drawtext_recolor(display2, 75, ypos, font, "NAV2    ", HSV_WHITE, HSV_BLACK);
       //     }
       //     if (symbols_layer==0) {
       //         qp_drawtext_recolor(display1, 25, ypos, font, "SYMBOLS1 ", HSV_WHITE, HSV_BLACK);
       //         qp_drawtext_recolor(display2, 25, ypos, font, "SYMBOLS2 ", HSV_WHITE, HSV_BLACK);
       //     }
       // }
       // qp_flush(display1);
       // qp_flush(display2);
    // }
}

void keyboard_post_init_kb(void) {
    init_ui();   // Initialise the display
    keyboard_post_init_user();
}

void housekeeping_task_user(void) {
    static uint32_t last_draw = 0;
    lcd_power = (last_input_activity_elapsed() < SCREEN_TIMEOUT) ? 1 : 0;

    setPinOutput(DISPLAY_LED_PIN);
    if (lcd_power) {
        writePinHigh(DISPLAY_LED_PIN);
        if (timer_elapsed32(last_draw) > 33) { // Throttle to 30fps
            last_draw = timer_read32();
            draw_ui_user();
        }
    } else {
        writePinLow(DISPLAY_LED_PIN);
    }

}