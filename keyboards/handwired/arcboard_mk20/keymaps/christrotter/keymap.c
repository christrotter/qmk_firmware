// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "arcboard_mk20.h"
#include "keymap.h"

#if defined(RAW_ENABLE)
    #include "hid_functionality.h"
#endif

#if defined(RGB_MATRIX_LEDMAPS_ENABLED)
    #include "rgb_ledmaps.h"
#endif

#if defined(QUANTUM_PAINTER_ENABLE)
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
#endif

void keyboard_post_init_user(void) {
    // Customise these values to desired behaviour
    debug_enable=true;
    debug_matrix=true;
    debug_keyboard=true;
    // debug_mouse=true;
    #if defined(QUANTUM_PAINTER_ENABLE)
    font = qp_load_font_mem(font_futura40);
    // setPinOutput(DISPLAY_BL_PIN);
    // writePinLow(DISPLAY_BL_PIN);
    
    display = qp_st7789_make_spi_device(76, 284, DISPLAY_CS_PIN, DISPLAY_DC_PIN, DISPLAY_RST_PIN, DISPLAY_SPI_DIVISOR, DISPLAY_SPI_MODE);
    qp_set_viewport_offsets(display, 82, 18); // for qp_rotation_0
    // if using horizontal orientation, use below, and reverse your x and y numbers when using QP draw functions
    // display = qp_st7789_make_spi_device(284, 76, DISPLAY_CS_PIN, DISPLAY_DC_PIN, DISPLAY_RST_PIN, DISPLAY_SPI_DIVISOR, DISPLAY_SPI_MODE);
    // qp_set_viewport_offsets(display, 18, 82); // for qp_rotation_270
    qp_init(display, QP_ROTATION_0);

    if (qp_lvgl_attach(display)) {     // Attach LVGL to the display
        create_ring_widget();
    }    
    #endif
}

#if defined(QUANTUM_PAINTER_ENABLE)
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
#endif


void housekeeping_task_user(void) {
    #if defined(QUANTUM_PAINTER_ENABLE)
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
    #endif
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
        KC_TILD, LGUI(KC_1), _______, KC_TAB_L, QK_LAYER_LOCK, AM_Toggle, KC_1,     KC_MACSHOT,KC_CHROMEWIN,KC_TAB_R,MAGIPLAY, LGUI(KC_9), KC_EQUAL, KC_3,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_2,                                 KC_Y, KC_U, LT(0,KC_I),KC_O, KC_P, KC_MINUS, KC_4,       
        _______, KC_A, KC_S,  KC_D,  KC_F, KC_G,                                    KC_H, KC_J, KC_K, HOME_L, KC_QUOT, KC_SCLN,         
        DRAGSCROLL_MODE_TOGGLE, KC_Z, KC_X, KC_C, KC_V, KC_B,                       LT(0,KC_N),HOME_M,KC_COMM,KC_DOT,KC_SLASH,OSM(MOD_LGUI),         
        KC_BSPC, MO(_NAV), KC_DEL, _______, INPUT_CHG, KC_ESC,                      KC_SPACE,  KC_ENTER,   MO(_SYMBOLS), MO(_NAV), _______, OSL(_RECT),         
        KC_FINDER, OSM(MOD_LSFT), OSM(MOD_LSFT), KC_ESC, _______,                   KC_LEFT, KC_UP, KC_DOWN, KC_RIGHT,_______
    ),
    [_MOUSE] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______,      _______,_______,_______,_______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______,      KC_CHRMBACK,KC_CHRMFWD,_______,_______, _______, _______,   _______,        
        _______, _______, _______, _______, _______, _______,               _______,KC_MS_BTN1, KC_MS_BTN3, KC_MS_BTN2, _______, _______,         
        _______, _______, _______, _______, _______, _______,               _______,_______,_______,_______, _______, _______,         
        _______, _______, _______, _______, _______, _______,               _______,_______,_______,_______, _______, _______,         
        _______, _______, _______, _______, _______,                        _______,_______,_______,_______, _______
    ),
    [_SYMBOLS] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______,      _______,_______,_______,_______, _______, _______, _______,
        _______, KC_EXLM, KC_AT,   KC_LPRN, KC_RPRN, KC_AMPR, _______,      KC_PPLS, KC_1,    KC_2,    KC_3,    KC_PMNS, KC_EQUAL, _______,
        _______, KC_HASH, KC_DLR,  KC_LCBR, KC_RCBR, KC_GRV,                KC_PAST, KC_4,    KC_5,    KC_6,    KC_0,    KC_COMM,
        _______, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_PIPE,               KC_DOT,  KC_7,    KC_8,    KC_9,    KC_BSLS, _______,
        _______, _______, _______, _______, _______, _______,               _______,_______,_______,_______, _______, _______,
        _______, _______, _______, _______, _______,                        _______,_______,_______,_______, _______
    ),
    [_NAV] = LAYOUT(
        OSL(_MGMT), _______, _______, _______, _______, _______, _______,   _______,_______,KC_SFTARROW_U,_______, _______, OSL(_MGMT), _______,
        _______, _______, _______, _______, _______, LT(0,KC_YAY), _______, KC_HOME, KC_ITRMSPCE_L, KC_UP, KC_ITRMSPCE_R, KC_END, _______, _______,
        _______, _______, _______, _______, _______, _______,               KC_ALTARROW_L, KC_LEFT, KC_DOWN, KC_RIGHT, KC_ALTARROW_R, _______,
        _______, _______, _______, _______, _______, _______,               KC_SFTGUIARROW_L, KC_SFTALTARROW_L, KC_SFTARROW_D, KC_SFTALTARROW_R, KC_SFTGUIARROW_R, _______,
        _______, _______, _______, _______, _______, KC_MACLOCK,               _______,_______,_______,_______, _______, _______,
        _______, _______, _______, _______, _______,                        _______,_______,_______,_______, _______
    ),
    [_RECT] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______,      REC_6TH_TL, REC_6TH_TM, REC_6TH_TR, _______, REC_MINIMIZE, REC_MAXIMIZE, _______,
        _______, _______, _______, _______, _______, _______, _______,      REC_6TH_BL, REC_6TH_BM, REC_6TH_TR, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,               REC_33_LEFT, REC_66_LEFT, REC_33_MID, REC_66_RIGHT, REC_33_RIGHT, _______,
        _______, _______, _______, _______, _______, _______,               REC_50_LEFT, REC_50_RIGHT, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,               _______,_______,_______,_______, _______, _______,
        _______, _______, _______, _______, _______,                        _______,_______,_______,_______, _______
    ),
    [_VSCODE] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______,      _______,_______,_______,_______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,      _______,_______,_______,_______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,               _______,_______,_______,_______, _______, _______,
        _______, _______, _______, _______, _______, _______,               _______,_______,_______,_______, _______, _______,
        _______, _______, _______, _______, _______, _______,               _______,_______,_______,_______, _______, _______,
        KC_MULTILNE, _______, _______, _______, _______,                        _______,_______,_______,_______, _______
    ),
    [_FUSION] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______,      _______,_______,_______,_______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,      _______,_______,_______,_______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,               _______,_______,_______,_______, _______, _______,
        _______, _______, _______, _______, _______, _______,               _______,_______,_______,_______, _______, _______,
        _______, _______, _______, _______, _______, _______,               _______,_______,_______,_______, _______, _______,
        _______, _______, _______, _______, _______,                        _______,_______,_______,_______, _______
    ),
    [_CHROME] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______,      _______,_______,_______,_______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,      _______,_______,_______,_______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,               _______,_______,_______,_______, _______, _______,
        _______, _______, _______, _______, _______, _______,               _______,_______,_______,_______, _______, _______,
        _______, _______, _______, _______, _______, _______,               _______,_______,_______,_______, _______, _______,
        LGUI(KC_TILD), _______, _______, _______, _______,                        _______,_______,_______,_______, _______
    ),
    [_KICAD] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______,      _______,_______,_______,_______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,      _______,_______,_______,_______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,               _______,_______,_______,_______, _______, _______,
        _______, _______, _______, _______, _______, _______,               _______,_______,_______,_______, _______, _______,
        _______, _______, _______, _______, _______, _______,               _______,_______,_______,_______, _______, _______,
        KC_KICAD_INSPECT, _______, _______, _______, _______,                        _______,_______,_______,_______, _______
    ),
    [_MGMT] = LAYOUT(
        EE_CLR,  QK_BOOT, _______, _______, _______, _______, _______,      _______,_______,_______,_______, QK_BOOT, EE_CLR, _______,
        _______, _______, _______, _______, _______, _______, _______,      _______,_______,_______,_______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,               _______,_______,_______,_______, _______, _______,
        _______, _______, _______, _______, _______, _______,               _______,_______,_______,_______, _______, _______,
        _______, _______, _______, _______, _______, _______,               _______,_______,_______,_______, _______, _______,
        _______, _______, _______, _______, _______,                        _______,_______,_______,_______, _______
    ),
};

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_QWERTY]   =  {
        ENCODER_CCW_CW(KC_VOLU, KC_VOLD),
        ENCODER_CCW_CW(KC_TAB_L, KC_TAB_R),
        ENCODER_CCW_CW(KC_TAB_L, KC_TAB_R),
        ENCODER_CCW_CW(KC_VOLU, KC_VOLD),
        ENCODER_CCW_CW(KC_TAB_L, KC_TAB_R),
        ENCODER_CCW_CW(KC_TAB_L, KC_TAB_R)
    },
    [_MOUSE] =  {
        ENCODER_CCW_CW(KC_VOLU, KC_VOLD),
        ENCODER_CCW_CW(KC_TAB_L, KC_TAB_R),
        ENCODER_CCW_CW(KC_TAB_L, KC_TAB_R),
        ENCODER_CCW_CW(KC_VOLU, KC_VOLD),
        ENCODER_CCW_CW(KC_TAB_L, KC_TAB_R),
        ENCODER_CCW_CW(KC_TAB_L, KC_TAB_R)
    },
    [_SYMBOLS] =  {
        ENCODER_CCW_CW(KC_VOLU, KC_VOLD),
        ENCODER_CCW_CW(KC_TAB_L, KC_TAB_R),
        ENCODER_CCW_CW(KC_TAB_L, KC_TAB_R),
        ENCODER_CCW_CW(KC_VOLU, KC_VOLD),
        ENCODER_CCW_CW(KC_TAB_L, KC_TAB_R),
        ENCODER_CCW_CW(KC_TAB_L, KC_TAB_R)
    },
    [_NAV] =  {
        ENCODER_CCW_CW(KC_VOLU, KC_VOLD),
        ENCODER_CCW_CW(KC_TAB_L, KC_TAB_R),
        ENCODER_CCW_CW(KC_TAB_L, KC_TAB_R),
        ENCODER_CCW_CW(KC_VOLU, KC_VOLD),
        ENCODER_CCW_CW(KC_TAB_L, KC_TAB_R),
        ENCODER_CCW_CW(KC_TAB_L, KC_TAB_R)
    },
    [_RECT] =  {
        ENCODER_CCW_CW(KC_VOLU, KC_VOLD),
        ENCODER_CCW_CW(KC_TAB_L, KC_TAB_R),
        ENCODER_CCW_CW(KC_TAB_L, KC_TAB_R),
        ENCODER_CCW_CW(KC_VOLU, KC_VOLD),
        ENCODER_CCW_CW(KC_TAB_L, KC_TAB_R),
        ENCODER_CCW_CW(KC_TAB_L, KC_TAB_R)
    },
    [_VSCODE] =  {
        ENCODER_CCW_CW(KC_VOLU, KC_VOLD),
        ENCODER_CCW_CW(KC_TAB_L, KC_TAB_R),
        ENCODER_CCW_CW(KC_TAB_L, KC_TAB_R),
        ENCODER_CCW_CW(KC_VOLU, KC_VOLD),
        ENCODER_CCW_CW(KC_TAB_L, KC_TAB_R),
        ENCODER_CCW_CW(KC_TAB_L, KC_TAB_R)
    },
    [_FUSION] =  {
        ENCODER_CCW_CW(KC_VOLU, KC_VOLD),
        ENCODER_CCW_CW(KC_TAB_L, KC_TAB_R),
        ENCODER_CCW_CW(KC_TAB_L, KC_TAB_R),
        ENCODER_CCW_CW(KC_VOLU, KC_VOLD),
        ENCODER_CCW_CW(KC_TAB_L, KC_TAB_R),
        ENCODER_CCW_CW(KC_TAB_L, KC_TAB_R)
    },
    [_CHROME] =  {
        ENCODER_CCW_CW(KC_VOLU, KC_VOLD),
        ENCODER_CCW_CW(KC_TAB_L, KC_TAB_R),
        ENCODER_CCW_CW(KC_TAB_L, KC_TAB_R),
        ENCODER_CCW_CW(KC_VOLU, KC_VOLD),
        ENCODER_CCW_CW(KC_TAB_L, KC_TAB_R),
        ENCODER_CCW_CW(KC_TAB_L, KC_TAB_R)
    },
    [_KICAD] =  {
        ENCODER_CCW_CW(KC_VOLU, KC_VOLD),
        ENCODER_CCW_CW(KC_TAB_L, KC_TAB_R),
        ENCODER_CCW_CW(KC_TAB_L, KC_TAB_R),
        ENCODER_CCW_CW(KC_VOLU, KC_VOLD),
        ENCODER_CCW_CW(KC_TAB_L, KC_TAB_R),
        ENCODER_CCW_CW(KC_TAB_L, KC_TAB_R)
    },
    [_MGMT] =  {
        ENCODER_CCW_CW(KC_VOLU, KC_VOLD),
        ENCODER_CCW_CW(KC_TAB_L, KC_TAB_R),
        ENCODER_CCW_CW(KC_TAB_L, KC_TAB_R),
        ENCODER_CCW_CW(KC_VOLU, KC_VOLD),
        ENCODER_CCW_CW(KC_TAB_L, KC_TAB_R),
        ENCODER_CCW_CW(KC_TAB_L, KC_TAB_R)
    },
};


// the indicator LEDs are mapped using the flags and for loop.
// SPRING, ESC, DEL, TOG_NAV, RED, ___n___,
const ledmap ledmaps[] = {
//     [_QWERTY]   = LEDMAP(

   [_QWERTY]   = LEDMAP(
    CYAN, CYAN, ___n___, RED, SPRING, SPRING,                                                   ORANGE,   SPRING,   GREEN,    PINK,    CYAN,    CYAN,
    GOLD   , ___n___, ___n___, ___n___, ___n___, ___n___,                                       ___n___, ___n___, ___n___, ___n___, ___n___,    CYAN, 
    ___n___, ___n___, ___n___, ___n___, ___n___, ___n___,                                       ___n___, ___n___, ___n___, HRM_ALT, ___n___, ___n___, 
    ORANGE, ___n___, ___n___, ___n___, ___n___, ___n___,                                        ___n___, HRM_CTL, ___n___, ___n___, ___n___, HRM_GUI,
    RED, TOG_NAV, RED, ___n___, SPRING, RED,                                                    TOG_RECT,TOG_NAV, TOG_SYM,   ENTER,   SPACE, ___n___,
    ___n___, RED, GREEN, BLUE, BLUE, BLUE, BLUE,                                                         CYAN, CYAN, CYAN, CYAN, BLUE, BLUE, BLUE
    ),
   [_MOUSE]   = LEDMAP(
    ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,                                       ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,
    ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,                                       RED,     GREEN,   ___t___, ___t___, ___t___, ___t___, 
    ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,                                       ___t___, PINK,    PURPLE,  BLUE,    ___t___, ___t___, 
    ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,                                       ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,
    ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,                                       ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,
    ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,                                       ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, ___t___
    ),
   [_SYMBOLS]   = LEDMAP(
    ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,                                       ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,
    ___t___, GOLD, GREEN, PURPLE, PURPLE, GREEN,                                                GREEN, CYAN, CYAN, CYAN, ___t___, ___t___, 
    ___t___, CYAN, YELLOW, MAGENT, MAGENT, BLUE,                                                GREEN, CYAN, CYAN, CYAN, CYAN, ___t___, 
    ___t___, GOLD, GREEN, PINK, PINK, CYAN,                                                     RED, CYAN, CYAN, CYAN, GOLD, ___t___,
    ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,                                       ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,
    ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,                                       ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, ___t___
    ),
   [_NAV]   = LEDMAP(
    RED, ___t___, ___t___, ___t___, ___t___, ___t___,                                            ___t___, ___t___, ___t___, ___t___, ___t___,    RED,
    ___t___, ___t___, ___t___, ___t___, ___t___, PURPLE,                                        GREEN,    CYAN,   GREEN,    CYAN,     RED,    ___t___, 
    ___t___, ___t___, GOLD, YELLOW, GOLD, ___t___,                                       YELLOW,   GREEN,   GREEN,   GREEN,  YELLOW, ___t___, 
    ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,                                       PURPLE,  ORANGE,  ORANGE,  ORANGE,  PURPLE, ___t___,
    YELLOW, ___t___, ___t___, ___t___, ___t___, ___t___,                                       ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,
    ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,                                       ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, ___t___
    ),
    [_RECT]   = LEDMAP(
    ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,                                       GREEN, ORANGE, RED, ___t___, RED,    BLUE,
    ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,                                       GREEN, ORANGE, RED, ___t___, ___t___,    ___t___, 
    ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,                                       RED, YELLOW, GREEN, YELLOW, RED, ___t___, 
    ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,                                       CYAN, PINK, ___t___, ___t___, ___t___, ___t___,
    ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,                                       ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,
    ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,                                       ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, ___t___
    ),
    [_VSCODE]   = LEDMAP(
    ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,                                       ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,
    ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,                                       ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, 
    ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,                                       ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, 
    ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,                                       ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,
    ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,                                       ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,
    ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,                                       ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, ___t___
    ),
    [_FUSION]   = LEDMAP(
    ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,                                       ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,
    ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,                                       ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, 
    ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,                                       ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, 
    ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,                                       ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,
    ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,                                       ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,
    ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,                                       ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, ___t___
    ),
    [_CHROME]   = LEDMAP(
    ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,                                       ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,
    ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,                                       ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, 
    ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,                                       ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, 
    ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,                                       ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,
    ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,                                       ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,
    ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,                                       ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, ___t___
    ),
    [_KICAD]   = LEDMAP(
    ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,                                       ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,
    ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,                                       ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, 
    ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,                                       ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, 
    ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,                                       ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,
    ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,                                       ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,
    ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,                                       ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, ___t___
    ),
    [_MGMT]   = LEDMAP(
    RED, ORANGE, ___t___, ___t___, ___t___, ___t___,                                            ___t___, ___t___, ___t___, ___t___, ORANGE, RED,
    ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,                                       ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, 
    ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,                                       ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, 
    ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,                                       ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,
    ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,                                       ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,
    ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,                                       ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, ___t___
    ),
};