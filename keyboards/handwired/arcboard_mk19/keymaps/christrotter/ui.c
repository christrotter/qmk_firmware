// Copyright 2023 Chris Trotter (@christrotter)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "arcboard_mk19.h"

#include "graphics/futura40.qff.c"
#include "graphics/awesome.qgf.h"
#include "graphics/disappointed_guy.qgf.h"
#include "graphics/roger.qgf.h"
#include "graphics/qmk-logo.qgf.h"
// #include "graphics/ui_img_816699078.c"
// #include "graphics/vscode_hi_res.c"

bool lcd_power;

static painter_font_handle_t font;
static painter_image_handle_t awesome;
static painter_image_handle_t disappointed_guy;
static painter_image_handle_t roger;
static painter_image_handle_t qmk_logo;
static painter_device_t display1;
static painter_device_t display2;

static lv_obj_t* layer_label = NULL; // Label to display current layer name
// static lv_obj_t* vscode_image = NULL; // VSCode image object

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
        case _RECT:
            return "rect";
        case _VSCODE:
            return "vscode";
        case _FUSION:
            return "fusion";
        case _MGMT:
            return "mgmt";
    }
    return "unknown";
}

/*
    LVGL setup - create your widgets and whatnot here
*/

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

// void add_lvgl_image(void) {
//     // lv_scr_act() is how you call the current screen
//     lv_obj_t * ui_logovscode = lv_img_create(lv_scr_act());
//     lv_img_set_src(ui_logovscode, &ui_img_816699078);
//     lv_obj_set_align( ui_logovscode, LV_ALIGN_CENTER );
// }

/* 
    Everything below here is now runtime/dynamic
*/

void init_ui(void) {
    font = qp_load_font_mem(font_futura40);
    awesome = qp_load_image_mem(gfx_awesome);
    disappointed_guy = qp_load_image_mem(gfx_disappointed_guy);
    roger = qp_load_image_mem(gfx_roger);
    qmk_logo = qp_load_image_mem(gfx_qmk_logo);

    // lol display2_cs_pin for display1?
    display1 = qp_gc9a01_make_spi_device(240, 240, DISPLAY2_CS_PIN, DISPLAY_DC_PIN, DISPLAY_RST_PIN, DISPLAY_SPI_DIVISOR, DISPLAY_SPI_MODE);
    if (is_keyboard_left()) {
        qp_init(display1, QP_ROTATION_90); // the rotation is not working
    } else {
        qp_init(display1, QP_ROTATION_0);
    }
    qp_init(display1, QP_ROTATION_0);
    // when you init display1, b/c they share rst pin, you do something to reset; running it again when init-ing display2 un-does all your init?
    display2 = qp_gc9a01_make_spi_device(240, 240, DISPLAY1_CS_PIN, DISPLAY_DC_PIN, NO_PIN, DISPLAY_SPI_DIVISOR, DISPLAY_SPI_MODE);
    qp_init(display2, QP_ROTATION_270);

    setPinOutput(DISPLAY_LED_PIN);
    writePinHigh(DISPLAY_LED_PIN);

    qp_drawimage(display1, 0, 0, qmk_logo);
    qp_drawimage(display2, 0, 0, qmk_logo);

    qp_flush(display2);
    qp_flush(display1);
    if (qp_lvgl_attach(display1)) {     // Attach LVGL to the display
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
                case _MGMT:
                    lv_obj_set_style_text_color(layer_label, lv_color_hex(0xFF0000), 0); // red
                    break;
                    // Show the VSCode image
                    // if (vscode_image != NULL) {
                    //     lv_obj_clear_flag(vscode_image, LV_OBJ_FLAG_HIDDEN);
                    // }
                    
            }
        }
    }
}

void housekeeping_task_user(void) {
    static uint32_t last_draw = 0;
    lcd_power = (last_input_activity_elapsed() < SCREEN_TIMEOUT) ? 1 : 0;

    setPinOutput(DISPLAY_LED_PIN);
    if (lcd_power) {
        writePinHigh(DISPLAY_LED_PIN);
        if (timer_elapsed32(last_draw) > 33) { // Throttle to 30fps
            last_draw = timer_read32();
            // add functions to update lvgl data here
            update_layer_display();
        }
    } else {
        writePinLow(DISPLAY_LED_PIN);
    }
}