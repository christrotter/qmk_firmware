// Copyright 2022 Chris Trotter (@christrotter)
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H
#include "arcboard_mk13_ui.h"
#include <printf.h>
#include "qp.h"
#include "backlight.h"
#ifdef POINTING_DEVICE_ENABLE
    #include "pointing_device.h"
#endif
#include <qp_st7789.h>
#include "graphics/futura40.qff.c"

painter_device_t qp_display;

static painter_font_handle_t font;

void init_and_clear(painter_device_t device, painter_rotation_t rotation) {
    uint16_t width;
    uint16_t height;
    qp_get_geometry(device, &width, &height, NULL, NULL, NULL);
    qp_init(device, rotation);
}
void ui_init(void) {
    font = qp_load_font_mem(font_futura40);

    qp_display = qp_st7789_make_spi_device(240, 320, DISPLAY_CS_PIN, DISPLAY_DC_PIN, DISPLAY_RST_PIN, DISPLAY_SPI_DIVISOR, 3);
    // cuz of sd card locations, one side has a flipped tft
    if (is_keyboard_left()) {
        init_and_clear(qp_display, QP_ROTATION_180);
    }
    else {
        init_and_clear(qp_display, QP_ROTATION_0);
    }
    qp_clear(qp_display);
    wait_ms(50);
    qp_power(qp_display, true);
    qp_rect(qp_display, 0, 0, 240, 106, HSV_BLACK, true);
    qp_rect(qp_display, 0, 106, 240, 212, HSV_BLACK, true);
    qp_rect(qp_display, 0, 212, 240, 320, HSV_BLACK, true);
    qp_flush(qp_display);
}
void draw_ui_user(void) {
    uint16_t width;
    uint16_t height;
    qp_get_geometry(qp_display, &width, &height, NULL, NULL, NULL);
    char buf[32] = {0};
    /* These are our 'did my qmk state thing change' functions, which get called later as drawing logic */
    // for both sides...
    /* If the layer has changed, redraw accordingly. */
    bool layer_state_redraw = false;
    bool set_scrolling = set_scrolling;

    static uint32_t last_layer_state   = 0;
    if (last_layer_state  != layer_state) {
        last_layer_state   = layer_state;
        layer_state_redraw = true;
    }
    if (layer_state_redraw) {
        extern const char *current_layer_name(void);
        const char        *layer_name = current_layer_name();
        const char        *mouse = "mouse";
        const char        *qwerty = "qwerty";
        const char        *nav = "nav";
        const char        *symbols = "symbols";
        int ypos = 150;
        snprintf(buf, sizeof(buf), "%s", layer_name);
        int mouse_layer = strcmp(layer_name, mouse);
        int qwerty_layer = strcmp(layer_name, qwerty);
        int nav_layer = strcmp(layer_name, nav);
        int symbols_layer = strcmp(layer_name, symbols);
        if (mouse_layer==0) {
            qp_rect(qp_display, 0, 106, 240, 212, HSV_BLUE, true);
            qp_drawtext_recolor(qp_display, 45, ypos, font, "MOUSE", HSV_WHITE, HSV_BLUE);
        }
        if (qwerty_layer==0) {
            qp_rect(qp_display, 0, 106, 240, 212, HSV_WHITE, true);
            qp_drawtext_recolor(qp_display, 35, ypos, font, "QWERTY", HSV_BLACK, HSV_WHITE);
        }
        if (nav_layer==0) {
            qp_rect(qp_display, 0, 106, 240, 212, HSV_CHARTREUSE, true);
            qp_drawtext_recolor(qp_display, 75, ypos, font, "NAV", HSV_BLACK, HSV_CHARTREUSE);
        }
        if (symbols_layer==0) {
            qp_rect(qp_display, 0, 106, 240, 212, HSV_PINK, true);
            qp_drawtext_recolor(qp_display, 25, ypos, font, "SYMBOLS", HSV_BLACK, HSV_PINK);
        }
    }
    /* for this board, left is always usb - there is config somewhere that flips transport sync bits depending on side */
    if (is_keyboard_left()) {
        bool scan_redraw = false;
        /* If the dragscroll config state has changed, redraw accordingly. */
        #ifdef POINTING_DEVICE_ENABLE
            bool ds_state_redraw = false;
            static uint32_t last_ds_state   = 0;
            if (last_ds_state  != set_scrolling) {
                last_ds_state   = set_scrolling;
                ds_state_redraw = true;
            }
        #endif

        static uint32_t last_scan_update = 0;
        if (timer_elapsed32(last_scan_update) > QP_MATRIX_SCAN_INTERVAL) {
            last_scan_update = timer_read32();
            scan_redraw      = true;
        }

        if (scan_redraw) {
            char scanrate_left[32] = {0};
            snprintf(scanrate_left, sizeof(scanrate_left), "SCAN: %d", (int)get_matrix_scan_rate());
            qp_drawtext_recolor(qp_display, 0, 245, font, scanrate_left, HSV_WHITE, HSV_BLACK);
        }
        #ifdef POINTING_DEVICE_ENABLE
            if (ds_state_redraw) {
                if (set_scrolling) {
                    qp_rect(qp_display, 0, 0, 240, 106, HSV_ORANGE, true);
                    qp_rect(qp_display, 0, 212, 240, 320, HSV_ORANGE, true);
                    qp_drawtext_recolor(qp_display, 60, 40, font, "DRAG", HSV_BLACK, HSV_ORANGE);
                    qp_drawtext_recolor(qp_display, 20, 255, font, "SCROLLIN'", HSV_BLACK, HSV_ORANGE);
                } else {
                    qp_rect(qp_display, 0, 0, 240, 106, HSV_BLACK, true);
                    qp_rect(qp_display, 0, 212, 240, 320, HSV_BLACK, true);
                }
            }
        #endif
    }
/////////// NOW WE CONFIGURE THE RIGHT SIDE //////////////
    if (!(is_keyboard_left())) {
        bool scan_redraw = false;
        static uint32_t last_scan_update = 0;
        if (timer_elapsed32(last_scan_update) > QP_MATRIX_SCAN_INTERVAL) {
            last_scan_update = timer_read32();
            scan_redraw      = true;
        }
        if (scan_redraw) {
            char scanrate_right[32] = {0};
            #ifdef POINTING_DEVICE_ENABLE
                char cpi_right[32] = {0};
                snprintf(cpi_right, sizeof(cpi_right), "CPI: %d", (int)pointing_device_get_cpi());
                qp_drawtext_recolor(qp_display, 0, 245, font, cpi_right, HSV_WHITE, HSV_BLACK);
            #endif
            snprintf(scanrate_right, sizeof(scanrate_right), "SCAN: %d", (int)get_matrix_scan_rate());
            qp_drawtext_recolor(qp_display, 0, 0, font, scanrate_right, HSV_WHITE, HSV_BLACK);
        }

        /* If the shift mod state has changed, redraw accordingly. */
        bool is_shifted_redraw = false;
        static uint32_t last_is_shifted_state = 0;
        if (last_is_shifted_state  != ((get_mods() | get_weak_mods()) & MOD_MASK_SHIFT)) {
            last_is_shifted_state   = ((get_mods() | get_weak_mods()) & MOD_MASK_SHIFT);
            is_shifted_redraw = true;
        }
        bool is_oneshot_redraw = false;
        static uint32_t last_is_oneshot_state = 0;
        if (last_is_oneshot_state  != ((get_mods() | get_oneshot_mods()) & MOD_MASK_SHIFT)) {
            last_is_oneshot_state   = ((get_mods() | get_oneshot_mods()) & MOD_MASK_SHIFT);
            is_oneshot_redraw = true;
        }

        if (is_shifted_redraw) {
            bool is_shifted = (get_mods() | get_weak_mods()) & MOD_MASK_SHIFT;
            if (is_shifted) {
                qp_rect(qp_display, 0, 0, 240, 106, HSV_GREEN, true);
                qp_rect(qp_display, 0, 212, 240, 320, HSV_GREEN, true);
                if (is_shifted_redraw) {
                    qp_drawtext_recolor(qp_display, 40, 40, font, "SHIFTIN'", HSV_BLACK, HSV_GREEN);
                    qp_drawtext_recolor(qp_display, 35, 255, font, "HOLDIN'", HSV_BLACK, HSV_GREEN);
                }
            } else {
                qp_rect(qp_display, 0, 0, 240, 106, HSV_BLACK, true);
                qp_rect(qp_display, 0, 212, 240, 320, HSV_BLACK, true);
            }
        }
        if (is_oneshot_redraw) {
            bool is_oneshot = (get_oneshot_mods() | get_mods()) & MOD_MASK_SHIFT;
            if (is_oneshot) {
                qp_rect(qp_display, 0, 0, 240, 106, HSV_GREEN, true);
                qp_rect(qp_display, 0, 212, 240, 320, HSV_GREEN, true);
                if (is_oneshot_redraw) {
                    qp_drawtext_recolor(qp_display, 40, 40, font, "SHIFTIN'", HSV_BLACK, HSV_GREEN);
                    qp_drawtext_recolor(qp_display, 20, 255, font, "ONESHOT", HSV_BLACK, HSV_GREEN);
                }
            } else {
                qp_rect(qp_display, 0, 0, 240, 106, HSV_BLACK, true);
                qp_rect(qp_display, 0, 212, 240, 320, HSV_BLACK, true);
            }
        }
    }
    qp_flush(qp_display);
}
