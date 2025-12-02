// Copyright 2025 Chris Trotter (@christrotter)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "arcboard_mk20.h"

#if defined(QUANTUM_PAINTER_ENABLE)
#include <qp.h>
#include "qp_internal.h"
#include "qp_comms.h"
#include "qp_st77xx_opcodes.h"
#include "qp_st7789_opcodes.h"
#include "qp_tft_panel.h"

// set up the display
#include "qp_st7789.h"
static painter_device_t display;

// fonts
#include "graphics/futura40.qff.c"
static painter_font_handle_t font;

#include "graphics/font_thintel15.qff.c"
static painter_font_handle_t font_thintel;

// images
#include "graphics/vscode-icon.qgf.h"
static painter_image_handle_t icon_vscode;

#include "graphics/qmk-icon.qgf.h"
static painter_image_handle_t icon_qmk;

#include "graphics/fusion-icon.qgf.h"
static painter_image_handle_t icon_fusion;

#include "graphics/chrome-icon.qgf.h"
static painter_image_handle_t icon_chrome;

#include "graphics/kicad-icon.qgf.h"
static painter_image_handle_t icon_kicad;

#include "graphics/default-app.qgf.h"
static painter_image_handle_t icon_default;

#include "graphics/mouse-icon.qgf.h"
static painter_image_handle_t icon_mouse;

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

#endif

void keyboard_post_init_user(void) {
    // debug_enable=true;
    // debug_matrix=true;
    // debug_keyboard=true;
    // debug_mouse=true;
    #if defined(QUANTUM_PAINTER_ENABLE)
        display = qp_st7789_make_spi_device(LCD_WIDTH, LCD_HEIGHT, DISPLAY_CS_PIN, DISPLAY_DC_PIN, DISPLAY_RST_PIN, DISPLAY_SPI_DIVISOR, DISPLAY_SPI_MODE);
        qp_set_viewport_offsets(display, 82, 18); // for qp_rotation_0

        font = qp_load_font_mem(font_futura40);
        font_thintel = qp_load_font_mem(font_thintel15);
        icon_vscode = qp_load_image_mem(gfx_vscode_icon);
        icon_qmk = qp_load_image_mem(gfx_qmk_icon);
        icon_fusion = qp_load_image_mem(gfx_fusion_icon);
        icon_chrome = qp_load_image_mem(gfx_chrome_icon);
        icon_kicad = qp_load_image_mem(gfx_kicad_icon);
        icon_default = qp_load_image_mem(gfx_default_app);
        icon_mouse = qp_load_image_mem(gfx_mouse_icon);

        qp_init(display, QP_ROTATION_0);
        qp_clear(display);
        // blank out the display to clear static
        qp_rect(display, 0, 0, LCD_WIDTH, LCD_HEIGHT, HSV_BLACK, true);
        qp_drawimage(display, (LCD_WIDTH - icon_qmk->width) / 2, (LCD_HEIGHT - icon_qmk->height) / 2, icon_qmk);
        qp_flush(display);

    #endif
}

// /**
//  * @brief Render the matrix scan rate to the display
//  *
//  * @param device device to render to
//  * @param font font to render with
//  * @param x x position to start rendering
//  * @param y y position to start rendering
//  * @param force_redraw do we forcibly redraw the scan rate
//  * @param curr_hsv painter colors
//  */
// void painter_render_scan_rate(painter_device_t device, painter_font_handle_t font, uint16_t x, uint16_t y,
//                               bool force_redraw, dual_hsv_t *curr_hsv) {
//     static uint32_t last_scan_rate = 0;
//     if (last_scan_rate != get_matrix_scan_rate() || force_redraw) {
//         last_scan_rate = get_matrix_scan_rate();
//         char buf[6]    = {0};
//         x += qp_drawtext_recolor(device, x, y, font, "SCANS: ", curr_hsv->primary.h, curr_hsv->primary.s,
//                                  curr_hsv->primary.v, 0, 0, 0);
//         snprintf(buf, sizeof(buf), "%5lu", get_matrix_scan_rate());
//         qp_drawtext_recolor(device, x, y, font, buf, curr_hsv->secondary.h, curr_hsv->secondary.s,
//                             curr_hsv->secondary.v, 0, 0, 0);
//     }
// }

/*
int16_t qp_drawtext_recolor(
    painter_device_t device, 
    uint16_t x, uint16_t y, 
    painter_font_handle_t font, 
    const char *str, 
    uint8_t hue_fg, uint8_t sat_fg, uint8_t val_fg, 
    uint8_t hue_bg, uint8_t sat_bg, uint8_t val_bg);

*/

void render_scan_rate(uint16_t x, uint16_t y) {
    static uint32_t last_scan_rate = 0;
    if (last_scan_rate != get_matrix_scan_rate()) {
        last_scan_rate = get_matrix_scan_rate();
        char buf[6]    = {0};
        x += qp_drawtext_recolor(display, x, y, font_thintel, "SCANS: ", HSV_WHITE, HSV_BLACK);
        snprintf(buf, sizeof(buf), "%5lu", get_matrix_scan_rate());
        qp_drawtext_recolor(display, x, y, font_thintel, buf, HSV_WHITE, HSV_BLACK);
    }    
}

#if defined(QUANTUM_PAINTER_ENABLE)
void draw_mouse(void) {
    qp_drawimage(display, (LCD_WIDTH - icon_mouse->width) / 2, (LCD_HEIGHT - icon_mouse->height) / 2, icon_mouse);
}

void update_layer_display(void) {
    // Only update if the layer has changed
    static uint32_t last_layer_state = 0;
    bool automouse = false;
    // ummm is this actually even checking against the layer state?
    if (last_layer_state != layer_state) {
        if (is_auto_mouse_active()) {
            automouse = true;
        }
        qp_rect(display, 0, 0, LCD_WIDTH, (LCD_WIDTH), HSV_BLACK, true);
        last_layer_state = layer_state;
        switch (get_highest_layer(layer_state)) {
            case _QWERTY:
                qp_drawimage(display, (LCD_WIDTH - icon_default->width) / 2, (LCD_HEIGHT - icon_default->height) / 2, icon_default);
                break;
            case _NAV:
                break;
            case _SYMBOLS:
                break;
            case _MOUSE:
                draw_mouse();
                break;
            case _RECT:
                break;
            case _VSCODE:
                if (automouse) {
                    draw_mouse();
                    break;
                }
                qp_drawimage(display, (LCD_WIDTH - icon_vscode->width) / 2, (LCD_HEIGHT - icon_vscode->height) / 2, icon_vscode);
                break;
            case _FUSION:
                if (automouse) {
                    draw_mouse();
                    break;
                }
                qp_drawimage(display, (LCD_WIDTH - icon_fusion->width) / 2, (LCD_HEIGHT - icon_fusion->height) / 2, icon_fusion);
                break;
            case _CHROME:
                if (automouse) {
                    draw_mouse();
                    break;
                }
                qp_drawimage(display, (LCD_WIDTH - icon_chrome->width) / 2, (LCD_HEIGHT - icon_chrome->height) / 2, icon_chrome);
                break;
            case _KICAD:
                if (automouse) {
                    draw_mouse();
                    break;
                }
                qp_drawimage(display, (LCD_WIDTH - icon_kicad->width) / 2, (LCD_HEIGHT - icon_kicad->height) / 2, icon_kicad);
                break;
            case _MGMT:
                break;
            default:
                break;
        }
    }
    render_scan_rate(5, 5);
    qp_flush(display);
}
#endif

void housekeeping_task_user(void) {
    #if defined(QUANTUM_PAINTER_ENABLE)
        static uint32_t last_draw = 0;
        if (timer_elapsed32(last_draw) > 33) { // Throttle to 30fps
            last_draw = timer_read32();
            update_layer_display();
        }
    #endif
}