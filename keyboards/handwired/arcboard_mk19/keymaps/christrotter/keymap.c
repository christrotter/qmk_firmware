// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "arcboard_mk19.h"
#include "keymap.h"

#if defined(RAW_ENABLE)
    #include "hid_functionality.h"
#endif

#if defined(CONSOLE_ENABLE)
    #include "print.h"
#endif

#if defined(QUANTUM_PAINTER_ENABLE)
    #include "ui.h"
#endif

#if defined(ENCODER_MAP_ENABLE)
    #include "encoder_maps.c"
#endif

#if defined(POINTING_DEVICE_ENABLE)
    #include "pointing.c"
#endif

#if defined(RGB_MATRIX_LEDMAPS_ENABLED)
    #include "rgb_ledmaps.h"
#endif

uint16_t alt_tab_timer = 0;
uint16_t sup_alt_tab_timer = 0;

void keyboard_post_init_user(void) {
    // Customise these values to desired behaviour
    debug_enable=true;
    // debug_matrix=true;
    // debug_keyboard=true;
    // debug_mouse=true;
    init_ui();   // Initialise the display
}

__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) { return true; }
__attribute__((weak)) void post_process_record_keymap(uint16_t keycode, keyrecord_t *record) {}
void                       post_process_record_user(uint16_t keycode, keyrecord_t *record) { post_process_record_keymap(keycode, record); }


/*
row0 = 8 keys in thumb row, but two are disconnected/useless, just leds in chain
row1 = fkeys 0-5, dpad 6-10 (4 arrows, 1 center push)
row2 = num keys 0-5, extra falcon keys or misc
row3 = letters1 0-5, macro1 6-9
row4 = letters2 0-5, macro2 6-9
row5 = letters3 0-5

info.json helper 
old                             new
row0,  row1  => 8 (0-7)         row10,  row11   => 6 (0-5)
row2,  row3  => 11 (0-10)       row2,  row3   => 10 (0-9)
row4,  row5  => 8 (0-7)         row4,  row5   => 10 (0-9)
row6,  row7  => 10 (0-9)        row4,  row5   => 8 (0-7)
row8,  row9  => 10 (0-9)        row2,  row3   => 11 (0-10)
row10, row11 => 6 (0-5)         row0, row1  => 8 (0-7)

row5,  row11 => 11 (0-10)  
row4,  row10 => 8 (0-7)
row3,  row9  => 10 (0-9)   
row2,  row8  => 10 (0-9)  
row1,  row7  => 6 (0-5)  
row0,  row6  => 8 (0-7)

*/
// will we be keeping the same col count? i.e. macropad is 4x2
// 11 x 6 matrix
// and what does this mean for the ledmaps?
// this is not correct - woo good catch here - the schematic says row8/9, but there _is_ no row8/9!
// dpad = row5 and 11
// macropad = rows 2/3 & 9/10
// um so how do we reconcile pcb-row vs. info.json-row?
/*
// i recall now - cyboard does it completely reversed for reasons i don't understand but he does.
pcb-row0 = json-row5
pcb-row1 = json-row4
pcb-row2 = json-row3
pcb-row3 = json-row2
pcb-row4 = json-row1
pcb-row5 = json-row0 (thumbs)

therefore!!!
dpad = row5 and 11
macropad = rows 3/2 & 9/8
tft buttons = row4:col7&col8

BUT.
Split causes havoc with the ordering, cuz you double the rows.
So we need the pcb to output dpad on row5, macropad on row2&3.

6 rows, 10 cols

    [_OUTLINE] = LAYOUT(
        F-keys row, 5 dpad keys,                                                    F-keys row, 5 dpad keys,
        num-keys row, KC_NO, flat-falcon button,angle-falcon button,                num-keys row, KC_NO, flat-falcon button,angle-falcon button,
        qwert-row, 4 macro keys,                                                    yuio-row, 4 macro keys,
        asdf-row, 4 macro keys,                                                     hjkl-row, 4 macro keys,
        zxcv-row,                                                                   nm,.-row,
        thumb-keys row,                                                             thumb-keys row
    ),
*/
// monitor input source change: ctrl alt shift v

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
        _______, _______, _______, _______, _______, _______,         KC_FINDER, KC_ESC, OSM(MOD_LSFT), _______, OSM(MOD_LSFT),      _______,_______,_______,_______, _______, _______,                KC_LEFT, KC_UP, KC_DOWN, KC_RIGHT,_______,
        KC_TILD,LGUI(KC_1),_______,KC_TAB_L,_______,_______,     KC_NO, _______, SUP_ALT_TAB,                                      KC_MACSHOT,_______,KC_TAB_R,MAGIPLAY, LGUI(KC_9), KC_EQUAL,     KC_NO, LGUI(KC_TILD), _______,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T,             KC_PD_LAYER, _______, _______, _______,                           KC_Y, KC_U, LT(0,KC_I),KC_O, KC_P, KC_MINUS,                     _______, _______, _______, _______,
        _______, KC_A, KC_S,  KC_D,  KC_F, KC_G,                _______, _______, _______, _______,                             KC_H, KC_J, KC_K, HOME_L, KC_QUOT, KC_SCLN,                        _______, _______, _______, _______,
        DRAGSCROLL_MODE_TOGGLE, KC_Z, KC_X, KC_C, KC_V, KC_B,                                                         LT(0,KC_N),HOME_M,KC_COMM,KC_DOT,KC_SLASH,OSM(MOD_LGUI),
        KC_BSPC, MO(_NAV), KC_DEL, KC_ESC, _______, INPUT_CHG,                                                                  KC_SPACE,  KC_ENTER,   MO(_SYMBOLS), MO(_NAV), OSL(_RECT), QK_LAYER_LOCK
    ),
    [_MOUSE] = LAYOUT(
        _______, _______, _______, _______, _______, _______,           _______,_______,_______,_______,_______,                    _______, _______, _______, _______, _______, _______,                       _______,_______,_______,_______,_______,
        _______, _______, _______, _______, _______, _______,           _______,_______,_______,                                    _______, _______, _______, _______, _______, _______,                       _______,_______,_______,
        _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______,                         KC_CHRMBACK, KC_CHRMFWD, _______, _______, _______, _______,                _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______,                         _______, KC_MS_BTN1, KC_MS_BTN3, KC_MS_BTN2, _______, _______,              _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                                                                       _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                                                                       _______, _______, _______, _______, _______, AM_Toggle
    ),
    [_SYMBOLS] = LAYOUT(
        _______,  _______, _______, _______, _______, _______,          _______,_______,_______,_______,_______,                    _______, _______, _______, _______, _______, _______,                       _______,_______,_______,_______,_______,
        _______, _______, _______, _______, _______, _______,           _______,_______,_______,                                    _______, _______, _______, _______, _______, _______,                   _______,_______,_______,
        _______, KC_EXLM, KC_AT,   KC_LPRN, KC_RPRN, KC_AMPR,           _______, _______, _______, _______,                         KC_PPLS, KC_1,    KC_2,    KC_3,    KC_PMNS, KC_EQUAL,                      _______, _______, _______, _______,
        _______, KC_HASH, KC_DLR,  KC_LCBR, KC_RCBR, KC_GRV,            _______, _______, _______, _______,                         KC_PAST, KC_4,    KC_5,    KC_6,    KC_0,    KC_COMM,                       _______, _______, _______, _______,
        _______, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_PIPE,                                                                       KC_DOT,  KC_7,    KC_8,    KC_9,    KC_BSLS, _______,
        _______, _______, _______, _______, _______, _______,                                                                       _______, _______, _______, _______, _______, _______
    ),
    [_NAV] = LAYOUT(
        _______, _______, _______, _______, _______, _______,           _______,_______,_______,_______,_______,                    _______, _______, _______, _______, _______, _______,                       _______,_______,_______,_______,_______,
        EE_CLR,  QK_BOOT, _______, _______, _______, _______,           _______,_______,_______,                                    _______, _______, KC_SFTARROW_U, _______, QK_BOOT, OSL(_MGMT),                 _______,_______,_______,
        _______, _______, _______, _______, _______, LT(0,KC_YAY),      _______, _______, _______, _______,                         KC_HOME, KC_ITRMSPCE_L, KC_UP, KC_ITRMSPCE_R, KC_END, _______,              _______, _______, _______, _______,
        _______, _______, _______, _______, _______,_______,            _______, _______, _______, _______,                         KC_ALTARROW_L, KC_LEFT, KC_DOWN, KC_RIGHT, KC_ALTARROW_R,  _______,         _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                                                                       KC_SFTGUIARROW_L, KC_SFTALTARROW_L, KC_SFTARROW_D, KC_SFTALTARROW_R, KC_SFTGUIARROW_R, _______,
        _______, _______, _______, _______, KC_MACLOCK, _______,                                                                    _______, _______, _______, _______, _______, _______
    ),
    [_RECT] = LAYOUT(
        _______,  _______, _______, _______, _______, _______,           _______,_______,_______,_______,_______,                   _______, _______, _______, _______, _______, _______,                       _______,_______,_______,_______,_______,
        _______, _______, _______, _______, _______, _______,           _______,_______,_______,                                    REC_6TH_TL, REC_6TH_TM, REC_6TH_TR, _______, REC_MINIMIZE, REC_MAXIMIZE,                 _______,_______,_______,
        _______, _______, _______, _______, _______, _______,_______, _______, _______, _______,                                    REC_6TH_BL, REC_6TH_BM, REC_6TH_TR, _______, _______, _______,              _______, _______, _______, _______,
        _______, _______, _______, _______, _______,_______,        _______, _______, _______, _______,                             REC_33_LEFT, REC_66_LEFT, REC_33_MID, REC_66_RIGHT, REC_33_RIGHT, _______,         _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                                                                       REC_50_LEFT, REC_50_RIGHT, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                                                                       _______, _______, _______, _______, _______, _______
    ),
    [_VSCODE] = LAYOUT(
        _______, _______, _______, _______, _______, _______,            KC_MULTILNE, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,            _______, _______, _______,                                 _______, _______, _______, _______, _______, _______,       _______, _______, _______,
        _______, _______, _______, _______, _______, _______,            _______, _______, _______, _______,                        _______, _______, _______, _______, _______, _______,       _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,            _______, _______, _______, _______,                        _______, _______, _______, _______, _______, _______,       _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                                                                       _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                                                                       _______, _______, _______, _______, _______, _______
    ),
    [_FUSION] = LAYOUT(
        _______, _______, _______, _______, _______, _______,            _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,            _______, _______, _______,                                 _______, _______, _______, _______, _______, _______,       _______, _______, _______,
        _______, _______, _______, _______, _______, _______,            _______, _______, _______, _______,                        _______, _______, _______, _______, _______, _______,       _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,            _______, _______, _______, _______,                        _______, _______, _______, _______, _______, _______,       _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                                                                       _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                                                                       _______, _______, _______, _______, _______, _______
    ),
    [_MGMT] = LAYOUT(
        _______, _______, _______, _______, _______, _______,            _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______,
        EE_CLR,  QK_BOOT, _______, _______, _______, _______,            _______, _______, _______,                                 _______, _______, _______, _______, QK_BOOT, EE_CLR,       _______, _______, _______,
        _______, _______, _______, _______, _______, _______,            _______, _______, _______, _______,                        _______, _______, _______, _______, _______, _______,       _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,            _______, _______, _______, _______,                        _______, _______, _______, _______, _______, _______,       _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                                                                       _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                                                                       _______, _______, _______, _______, _______, _______
    ),
};

#if defined(RGB_MATRIX_LEDMAPS_ENABLED)
// the indicator LEDs are mapped using the flags and for loop.
// todo: is there 'skip' logic for the ___n___ items?
// there are no macropad things here...we need the ledmap to also be 11x6? maybe
// added macropad, need to ensure indicators are not included...
// dpad added to ledmaps
// macropad is topleft->topright botleft->botright TOP TOP TOP TOP BOT BOT BOT BOT
const ledmap ledmaps[] = {
//     [_QWERTY]   = LEDMAP(

   [_QWERTY]   = LEDMAP(
    ___n___, ___n___, ___n___, ___n___, ___n___, ___n___,    ___n___, BLUE, GREEN, RED,         ___n___, ___n___, ___n___, ___n___, ___n___, ___n___,        GREEN, GREEN, GREEN, GREEN,
    CYAN, CYAN, ___n___, RED, ___n___, ___n___,                                                 ORANGE, ___n___, GREEN, PINK, CYAN,    CYAN,
    GOLD   , ___n___, ___n___, ___n___, ___n___, ___n___,                                       ___n___, ___n___, ___n___, ___n___, ___n___,    CYAN, 
    ___n___, ___n___, ___n___, ___n___, ___n___, ___n___,                                       ___n___, ___n___, ___n___, HRM_ALT, ___n___, ___n___, 
    ORANGE, ___n___, ___n___, ___n___, ___n___, ___n___,                                        ___n___, HRM_CTL, ___n___, ___n___, ___n___,     HRM_GUI,
    SPRING, ___n___, ESC, DEL, TOG_NAV, RED,                                                       CYAN, TOG_RECT, TOG_NAV, TOG_SYM, ENTER, SPACE,
    ___n___, ___n___, ___n___, ___n___, ___n___, ___n___, ___n___, ___n___,                     ___n___, ___n___, ___n___, ___n___, ___n___, ___n___, ___n___, ___n___
    ),
   [_MOUSE]   = LEDMAP(
    ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,   ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,
    ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,                                       ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,
    ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,                                       RED,     GREEN,   ___t___, ___t___, ___t___, ___t___, 
    ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,                                       ___t___, PINK,    PURPLE,  BLUE,    ___t___, ___t___, 
    ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,                                       ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,
    ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,                                       ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,
    ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,                     ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, ___t___
    ),
   [_SYMBOLS]   = LEDMAP(
    ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,    ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,
    ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,                                       ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,
    ___t___, GOLD, GREEN, PURPLE, PURPLE, GREEN,                                                GREEN, CYAN, CYAN, CYAN, ___t___, ___t___, 
    ___t___, CYAN, YELLOW, MAGENT, MAGENT, BLUE,                                                GREEN, CYAN, CYAN, CYAN, CYAN, ___t___, 
    ___t___, GOLD, GREEN, PINK, PINK, CYAN,                                                     RED, CYAN, CYAN, CYAN, GOLD, ___t___,
    ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,                                       ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,
    ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,                     ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, ___t___
    ),
   [_NAV]   = LEDMAP(
    ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,    ___t___, ___t___, ___t___, ___t___,      ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,        ___t___, ___t___, ___t___, ___t___,
    RED, ORANGE, ___t___, ___t___, ___t___, ___t___,                                            ___t___, ___t___, ___t___, ___t___, ORANGE,    RED,
    ___t___, ___t___, ___t___, ___t___, ___t___, PURPLE,                                        GREEN,    CYAN,   GREEN,    CYAN,     RED,    ___t___, 
    ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,                                       YELLOW,   GREEN,   GREEN,   GREEN,  YELLOW, ___t___, 
    ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,                                       PURPLE,  ORANGE,  ORANGE,  ORANGE,  PURPLE, ___t___,
    ___t___, YELLOW, ___t___, ___t___, ___t___, ___t___,                                        ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,
    ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,                     ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, ___t___
    ),
    [_RECT]   = LEDMAP(
    ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,   ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,        ___t___, ___t___, ___t___, ___t___,
    ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,                                       GREEN, ORANGE, RED, ___t___, RED,    BLUE,
    ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,                                       GREEN, ORANGE, RED, ___t___, ___t___,    ___t___, 
    ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,                                       RED, YELLOW, GREEN, YELLOW, RED, ___t___, 
    ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,                                       CYAN, PINK, ___t___, ___t___, ___t___, ___t___,
    ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,                                       ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,
    ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,                     ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, ___t___
    ),
    [_VSCODE]   = LEDMAP(
    ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, SPRING, ___t___, ___t___,    ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,
    ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,                                       ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,
    ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,                                       ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, 
    ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,                                       ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, 
    ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,                                       ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,
    ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,                                       ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,
    ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,                     ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, ___t___
    ),
    [_VSCODE]   = LEDMAP(
        ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, ORANGE, ___t___, ___t___,    ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,
        ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,                                       ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,
        ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,                                       ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, 
        ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,                                       ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, 
        ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,                                       ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,
        ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,                                       ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,
        ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,                     ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, ___t___
        ),
    [_MGMT]   = LEDMAP(
            ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, RED, ___t___, ___t___,    ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,
            RED, ORANGE, ___t___, ___t___, ___t___, ___t___,                                       ___t___, ___t___, ___t___, ___t___, ORANGE, RED,
            ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,                                       ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, 
            ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,                                       ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, 
            ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,                                       ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,
            ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,                                       ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,
            ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, ___t___,                     ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, ___t___, ___t___
            ),
};
#endif // RGB_MATRIX_LEDMAPS_ENABLED

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case ALT_TAB:
            if (record->event.pressed) {
              if (!kb_get_alt_tab_state()) {
                kb_set_alt_tab_active();
                register_code(KC_LGUI);
              }
              alt_tab_timer = timer_read();
              register_code(KC_TAB);
            } else {
              unregister_code(KC_TAB);
            }
            break;
        case SFT_ALT_TAB:
            if (record->event.pressed) {
              if (!kb_get_alt_tab_state()) {
                kb_set_alt_tab_active();
                register_code(KC_LGUI);
              }
              alt_tab_timer = timer_read();
              register_code(KC_LSFT);
              register_code(KC_TAB);
            } else {
              unregister_code(KC_TAB);
              unregister_code(KC_LSFT);
            }
            break;
        case SUP_ALT_TAB:
            if (record->event.pressed) {
              if (!kb_get_super_alt_tab_state()) {
                kb_set_super_alt_tab_active();
                register_code(KC_LGUI);
              }
              sup_alt_tab_timer = timer_read();
              register_code(KC_TAB);
            } else {
              unregister_code(KC_TAB);
            }
            break;
        case LT(0,KC_YAY):
            if (record->event.pressed) {
                SEND_STRING("\\o/");
                return false;
            }
            return true;
        case LT(0,KC_N):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(LCMD(LSFT(KC_N))); // hold for command+letter
                return false;
            }
            return true;
        case LT(0,KC_MPLY):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(KC_MNXT); // hold for command+letter
                return false;
            }
            return true;
        case KC_PD_LAYER:
            if (record->event.pressed) {
                // xprintf("KC_PD_LAYER pressed\n");
                #if defined(RAW_ENABLE)
                    cycle_pedal_layer();
                #endif
                return false;
            }
            return true;
        case KC_FINDER:
            if (record->event.pressed) {
                tap_code16(LCMD(KC_SPACE));
                return false;
            }
            return true;
        case AM_Toggle:
            if(record->event.pressed) { // key down
                auto_mouse_toggle();
                return false;
            } // do nothing on key up
            return true; // prevent further processing of keycode
    }
    return true;
}

void matrix_scan_user(void) {
  if (kb_get_alt_tab_state()) {
    if (timer_elapsed(alt_tab_timer) > 1000) {
      kb_set_alt_tab_off();
      unregister_code(KC_LGUI);
    }
  }
  if (kb_get_super_alt_tab_state()) {
    if (timer_elapsed(sup_alt_tab_timer) > 50) {
      kb_set_super_alt_tab_off();
      unregister_code(KC_LGUI);
    }
  }
}
