// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include QMK_KEYBOARD_H
#include "arcboard_mk19.h"
#include "print.h"

#if defined(RAW_ENABLE)
    #include "hid_functionality.h"
#endif

#if defined(CONSOLE_ENABLE)
    #include "print.h"
#endif

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

// lvgl stuff
static lv_obj_t* layer_label = NULL; // Label to display current layer name

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

const char *current_layer_name(void) {
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            return "qw";
        case _NAV:
            return "na";
        case _SYMBOLS:
            return "sy";
        case _MOUSE:
            return "mo";
        case _RECT:
            return "re";
        case _VSCODE:
            return "vs";
        case _FUSION:
            return "fu";
        case _CHROME:
            return "ch";
        case _KICAD:
            return "ki";
        case _MGMT:
            return "mg";
    }
    return "unknown";
}

void create_ring_widget(void) {
    // Create a full black background
    lv_obj_set_style_bg_color(lv_scr_act(), lv_color_black(), 0);
    
    // Create the arc widget (ring)
    lv_obj_t* ring = lv_arc_create(lv_scr_act());
    
    // Configure the arc to be a complete circle
    lv_arc_set_bg_angles(ring, 0, 360);
    lv_arc_set_angles(ring, 0, 360);
    
    // Remove the knob that would appear on the arc
    lv_obj_remove_style(ring, NULL, LV_PART_KNOB);
    
    // Make it non-interactive
    lv_obj_clear_flag(ring, LV_OBJ_FLAG_CLICKABLE);
    
    // Center the ring in the display
    lv_obj_center(ring);
    
    // Set size to create a ring around the edge (adjust as needed)
    lv_obj_set_size(ring, 220, 220);
    
    // Style the arc to be white
    lv_obj_set_style_arc_color(ring, lv_color_white(), LV_PART_INDICATOR);
    lv_obj_set_style_arc_width(ring, 10, LV_PART_INDICATOR); // Adjust width as needed
    
    // Background of the arc should be transparent
    lv_obj_set_style_arc_color(ring, lv_color_black(), LV_PART_MAIN);
    lv_obj_set_style_arc_width(ring, 10, LV_PART_MAIN);

    // Create a label for the layer name
    layer_label = lv_label_create(lv_scr_act());
    lv_label_set_text(layer_label, current_layer_name());
    lv_obj_center(layer_label);
    
    // Style the label to be white and larger
    lv_obj_set_style_text_color(layer_label, lv_color_white(), 0);
    lv_obj_set_style_text_font(layer_label, &lv_font_montserrat_48, 0); 
    
    // Create the VSCode image once but hide it initially
    // vscode_image = lv_img_create(lv_scr_act());
    // lv_img_set_src(vscode_image, &ui_img_816699078);
    // // lv_img_set_src(vscode_image, &vscode_hi_res);
    // lv_obj_set_width( vscode_image, LV_SIZE_CONTENT);  /// 1
    // lv_obj_set_height( vscode_image, LV_SIZE_CONTENT);   /// 1
    // lv_obj_set_align(vscode_image, LV_ALIGN_CENTER);
    // lv_obj_add_flag( vscode_image, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
    // lv_obj_add_flag(vscode_image, LV_OBJ_FLAG_HIDDEN); // Hide initially
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
    qp_set_viewport_offsets(display, 82, 18); // for qp_rotation_0
    // if using horizontal orientation, use below, and reverse your x and y numbers when using QP draw functions
    // display = qp_st7789_make_spi_device(284, 76, DISPLAY_CS_PIN, DISPLAY_DC_PIN, DISPLAY_RST_PIN, DISPLAY_SPI_DIVISOR, DISPLAY_SPI_MODE);
    // qp_set_viewport_offsets(display, 18, 82); // for qp_rotation_270
    qp_init(display, QP_ROTATION_0);

    if (qp_lvgl_attach(display)) {     // Attach LVGL to the display
        create_ring_widget();
    }    
}

void update_layer_display(void) {
    static uint32_t last_layer_state = 0;
    
    // Only update if the layer has changed
    if (last_layer_state != layer_state) {
        last_layer_state = layer_state;
        
        if (layer_label != NULL) {
            // Hide the VSCode image for all layers first
            // if (vscode_image != NULL) {
            //     lv_obj_add_flag(vscode_image, LV_OBJ_FLAG_HIDDEN);
            // }
            
            // Update the label text with the current layer name
            lv_label_set_text(layer_label, current_layer_name());
            
            // Optional: You can add animation or color changes based on layer
            switch (get_highest_layer(layer_state)) {
                case _QWERTY:
                    lv_obj_set_style_text_color(layer_label, lv_color_white(), 0);
                    break;
                case _NAV:
                    lv_obj_set_style_text_color(layer_label, lv_color_hex(0x00FFFF), 0); // Cyan
                    break;
                case _SYMBOLS:
                    lv_obj_set_style_text_color(layer_label, lv_color_hex(0xFFFF00), 0); // Yellow
                    break;
                case _MOUSE:
                    lv_obj_set_style_text_color(layer_label, lv_color_hex(0xFF00FF), 0); // Magenta
                    break;
                case _RECT:
                    lv_obj_set_style_text_color(layer_label, lv_color_hex(0xFF0000), 0); // Red
                    break;
                case _VSCODE:
                    lv_obj_set_style_text_color(layer_label, lv_color_hex(0xFF55FF), 0); // Magenta
                    break;
                case _FUSION:
                    lv_obj_set_style_text_color(layer_label, lv_color_hex(0xFF7800), 0); // orange
                    break;
                case _CHROME:
                    lv_obj_set_style_text_color(layer_label, lv_color_hex(0x00FFFF), 0); // cyan
                    break;
                case _KICAD:
                    lv_obj_set_style_text_color(layer_label, lv_color_hex(0x5cacf0), 0); // bluey
                    break;
                case _MGMT:
                    lv_obj_set_style_text_color(layer_label, lv_color_hex(0xFF0000), 0); // red
                    break;
                    // Show the VSCode image
                    // if (vscode_image != NULL) {
                    //     lv_obj_clear_flag(vscode_image, LV_OBJ_FLAG_HIDDEN);
                    // }
                default:
                    lv_obj_set_style_text_color(layer_label, lv_color_white(), 0); // Default to white
                    break;
            }
        }
    }
}


void housekeeping_task_user(void) {
    static uint32_t last_draw = 0;
    // if (timer_elapsed32(last_draw) > 160) { // Throttle to 30fps
    //     qp_rect(display, 
    //         0, 0, 
    //         76, 284, 
    //         HSV_BLACK,  // White: H=0, S=0, V=255
    //         true
    //     );
    // }
    if (timer_elapsed32(last_draw) > 33) { // Throttle to 30fps
        last_draw = timer_read32();
        
        // static const char *text = "C";
        // 
        // // Get text dimensions
        // int16_t text_width = qp_textwidth(font, text);
        // 
        // // Calculate centered position
        // int16_t x_centered = (76 - text_width) / 2;
        // int16_t y_centered = (284 - font->line_height) / 2;
        // 
        // qp_drawtext_recolor(display, x_centered, y_centered, font, text, 
        //                    HSV_WHITE,
        //                    HSV_BLACK);
        update_layer_display();
    }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
        KC_A
    ),
    [_MOUSE] = LAYOUT(
        _______
    ),
    [_SYMBOLS] = LAYOUT(
        _______ 
    ),
    [_NAV] = LAYOUT(
        _______
    ),
    [_RECT] = LAYOUT(
        _______
    ),
    [_VSCODE] = LAYOUT(
        _______
    ),
    [_FUSION] = LAYOUT(
        _______
    ),
    [_CHROME] = LAYOUT(
        _______
    ),
    [_KICAD] = LAYOUT(
        _______
    ),
    [_MGMT] = LAYOUT(
        _______
    ),
};
