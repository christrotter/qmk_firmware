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

#include "graphics/construction-icon.qgf.h"
static painter_image_handle_t icon_construction;

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
        icon_construction = qp_load_image_mem(gfx_construction_icon);

        qp_init(display, QP_ROTATION_0);
        qp_clear(display);
        // blank out the display to clear static
        qp_rect(display, 0, 0, LCD_WIDTH, LCD_HEIGHT, HSV_BLACK, true);
        qp_drawimage(display, (LCD_WIDTH - icon_qmk->width) / 2, (LCD_HEIGHT - icon_qmk->height) / 2, icon_qmk);
        qp_flush(display);

    #endif
}

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
// void render_dragtog_state() {
//     static bool last_dragscroll_state = false;
//     bool current_state = kb_get_pointer_dragscroll_enabled();
//     if (last_dragscroll_state != current_state) {
//         last_dragscroll_state = current_state;
//         char buf[12]    = {0};
//         if (current_state) {
//             snprintf(buf, sizeof(buf), "DRAG: ON ");
//         } else {
//             snprintf(buf, sizeof(buf), "DRAG: OFF");
//         }
//         qp_drawtext_recolor(display, 5, LCD_HEIGHT - 20, font_thintel, buf, HSV_WHITE, HSV_BLACK);
//     }
// }

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
        // we want this to draw a 76x76 square that is centered right in the middle of the display
        // uhhh weird choice mr.AI, but ok
        qp_rect(display, (LCD_WIDTH - 76) / 2, (LCD_HEIGHT - 76) / 2, 76, 76, HSV_BLACK, true);
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
                qp_drawimage(display, (LCD_WIDTH - icon_construction->width) / 2, (LCD_HEIGHT - icon_construction->height) / 2, icon_construction);
                break;
            default:
                break;
        }
    }
    render_scan_rate(5, 5);
    qp_flush(display);
}

void oneshot_layer_changed_user(uint8_t layer) {
  if (!layer) {
    qp_rect(display, 0, 0, LCD_WIDTH, LCD_HEIGHT, HSV_BLACK, true);
  }
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