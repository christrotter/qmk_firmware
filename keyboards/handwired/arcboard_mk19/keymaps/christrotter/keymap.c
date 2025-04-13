// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "arcboard_mk19.h"
#include "keymap.h"
#include "raw_hid.h"

#if defined(CONSOLE_ENABLE)
    #include "print.h"
    void keyboard_post_init_user(void) {
        // Customise these values to desired behaviour
        debug_enable=true;
        // debug_matrix=true;
        // debug_keyboard=true;
        // debug_mouse=true;
    }
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

bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;
bool is_sup_alt_tab_active = false;
uint16_t sup_alt_tab_timer = 0;

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
// KC_LEFT, KC_DOWN, KC_RIGHT, KC_UP,_______,
// KC_LEFT, KC_UP, KC_DOWN, KC_RIGHT,_______,
// KC_LEFT, _______, KC_DOWN, KC_UP, KC_RIGHT,
// monitor input source change: ctrl alt shift v

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
        KC_ESC, _______, _______, _______, _______, INPUT_CHG,                  KC_MULTILNE, KC_ESC, OSM(MOD_LSFT), OSM(MOD_LSFT), OSM(MOD_LSFT),      KC_MACSHOT,MAGIPLAY,_______,REC_MAXIMIZE, _______, KC_F12,                KC_LEFT, KC_UP, KC_DOWN, KC_RIGHT,_______,
        KC_TILD,LT(0,KC_1),LT(0,KC_2),LT(0,KC_3),LT(0,KC_4),LT(0,KC_5),     KC_NO, KC_PGUP, SUP_ALT_TAB,                                      LT(0,KC_6),LT(0,KC_7),LT(0,KC_8),LT(0,KC_9), KC_0, KC_EQUAL,     KC_NO, LGUI(KC_TILD), KC_PGDN,
        KC_TAB, KC_Q, LT(0,KC_W),HOME_E, LT(0,KC_R),LT(0,KC_T),             MEET_HAND, REC_6TH_BL, REC_6TH_BM, REC_6TH_BR,                           KC_Y, KC_U, LT(0,KC_I),KC_O, KC_P, KC_MINUS,                     REC_MINIMIZE, REC_66_RIGHT, REC_50_RIGHT, REC_33_RIGHT,
        KC_LSFT, LT(0,KC_A), HOME_S,  HOME_D,  HOME_F, KC_G,                _______, REC_6TH_TL, REC_6TH_TM, REC_6TH_TR,                             KC_H, HOME_J, HOME_K, HOME_L, KC_QUOT, KC_SCLN,                        REC_MAXIMIZE, REC_33_LEFT, REC_50_LEFT, REC_66_LEFT,
        DRAG_SCROLL,LT(0,KC_Z),LT(0,KC_X),LT(0,KC_C),LT(0,KC_V),LT(0,KC_B),                                                         LT(0,KC_N),HOME_M,KC_COMM,KC_DOT,KC_SLASH,KC_ESC,
        KC_BSPC, MO(_NAV), KC_DEL, KC_ESC, KC_LSFT, OSM(MOD_LSFT),                                                                  KC_SPACE,  KC_ENTER,   MO(_SYMBOLS), MO(_NAV), KC_LSFT, KC_MULTILNE
    ),
    [_MOUSE] = LAYOUT(
        _______, _______, _______, _______, _______, _______,           _______,_______,_______,_______,_______,                    _______, _______, _______, _______, _______, _______,                       _______,_______,_______,_______,_______,
        _______, _______, _______, _______, _______, _______,           _______,_______,_______,                                    _______, _______, _______, _______, _______, _______,                       _______,_______,_______,
        _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______,                         KC_CHRMBACK, KC_CHRMFWD, _______, _______, _______, _______,                _______, _______, _______, _______,
        _______, _______, KC_MS_BTN2, KC_MS_BTN3, KC_MS_BTN1, _______,  _______, _______, _______, _______,                         _______, KC_MS_BTN1, KC_MS_BTN3, KC_MS_BTN2, _______, _______,              _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                                                                       _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                                                                       _______, _______, _______, _______, _______, _______
    ),
    [_SYMBOLS] = LAYOUT(
        _______,  _______, _______, _______, _______, _______,          _______,_______,_______,_______,_______,                    _______, _______, _______, _______, _______, _______,                       _______,_______,_______,_______,_______,
        _______, _______, _______, _______, _______, _______,           _______,_______,_______,                                    KC_MACSHOT, MAGIPLAY, _______, _______, _______, _______,                   _______,_______,_______,
        _______, KC_EXLM, KC_AT,   KC_LPRN, KC_RPRN, KC_AMPR,           _______, _______, _______, _______,                         KC_PPLS, KC_1,    KC_2,    KC_3,    KC_PMNS, KC_EQUAL,                      _______, _______, _______, _______,
        _______, KC_HASH, KC_DLR,  KC_LCBR, KC_RCBR, KC_GRV,            _______, _______, _______, _______,                         KC_PAST, KC_4,    KC_5,    KC_6,    KC_0,    KC_COMM,                       _______, _______, _______, _______,
        _______, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_PIPE,                                                                       KC_DOT,  KC_7,    KC_8,    KC_9,    KC_BSLS, _______,
        _______, _______, _______, _______, _______, _______,                                                                       _______, _______, _______, _______, _______, _______
    ),
    [_NAV] = LAYOUT(
        EE_CLR,  QK_BOOT, _______, _______, _______, _______,           _______,_______,_______,_______,_______,                    EE_CLR,  QK_BOOT, _______, _______, _______, _______,                       _______,_______,_______,_______,_______,
        _______, _______, _______, _______, _______, _______,           _______,_______,_______,                                    _______, _______, KC_SFTARROW_U, _______, _______, _______,                 _______,_______,_______,
        _______, _______, _______, LGUI(KC_TILD), _______, LT(0,KC_YAY),_______, _______, _______, _______,                         KC_HOME, KC_ITRMSPCE_L, KC_UP, KC_ITRMSPCE_R, KC_END, _______,              _______, _______, _______, _______,
        _______, KC_TAB_L, KC_TAB_R, KC_TAB_L, KC_TAB_R,_______,        _______, _______, _______, _______,                         KC_ALTARROW_L, KC_LEFT, KC_DOWN, KC_RIGHT, KC_ALTARROW_R,  _______,         _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                                                                       KC_SFTGUIARROW_L, KC_SFTALTARROW_L, KC_SFTARROW_D, KC_SFTALTARROW_R, KC_SFTGUIARROW_R, _______,
        _______, _______, _______, _______, KC_MACLOCK, _______,                                                                    _______, _______, _______, _______, _______, _______
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
    RED, ___n___, ___n___, ___n___, ___n___, SPRING,    ___n___, SPRING, GREEN, RED,        ORANGE, PINK, ___n___, BLUE, ___n___, SPRING,           GREEN, GREEN, GREEN, GREEN,
    CYAN, ___n___, ___n___, ___n___, ___n___, ___n___,                                      ___n___, ___n___, ___n___, ___n___, ___n___,    CYAN,
    GOLD, ___n___, ___n___, HRM_CTL, ___n___, ___n___,                                      ___n___, ___n___, ___n___, ___n___, ___n___,    CYAN, 
    GREEN, ___n___, HRM_ALT, HRM_GUI, HRM_SFT, ___n___,                                     ___n___, HRM_SFT, HRM_GUI, HRM_ALT, ___n___, ___n___, 
    ORANGE, ___n___, ___n___, ___n___, ___n___, ___n___,                                    ___n___, HRM_CTL, ___n___, ___n___, ___n___,     RED,
    GREEN, GREEN, ESC, DEL, TOG_NAV, RED,                                                   GREEN, GREEN, TOG_NAV, TOG_SYM, ENTER, SPACE,
    ___n___, GREEN, ORANGE, RED, ___n___, GREEN, ORANGE, RED,                                BLUE, YELLOW, ORANGE, GREEN, RED, PURPLE, PINK, CYAN
    ),
   [_MOUSE]   = LEDMAP(
    RED, ___n___, ___n___, ___n___, ___n___, SPRING,    ___n___, SPRING, GREEN, RED,        ORANGE, PINK, ___n___, BLUE, ___n___, SPRING,           GREEN, GREEN, GREEN, GREEN,
    CYAN, ___n___, ___n___, ___n___, ___n___, ___n___,                                      ___n___, ___n___, ___n___, ___n___, ___n___,    CYAN,
    GOLD, ___n___, ___n___, ___n___, ___n___, ___n___,                                       RED, GREEN, ___n___, ___n___, ___n___,    CYAN, 
    GREEN, ___n___, BLUE, PURPLE, PINK, ___n___,                                            ___n___, PINK, PURPLE, BLUE, ___n___, ___n___, 
    ORANGE, ___n___, ___n___, ___n___, ___n___, ___n___,                                    ___n___, ___n___, ___n___, ___n___, ___n___,     RED,
    GREEN, GREEN, ESC, DEL, TOG_NAV, RED,                                                   GREEN, GREEN, TOG_NAV, TOG_SYM, ENTER, SPACE,
    ___n___, GREEN, ORANGE, RED, ___n___, GREEN, ORANGE, RED,                                BLUE, YELLOW, ORANGE, GREEN, RED, PURPLE, PINK, CYAN
    ),
   [_SYMBOLS]   = LEDMAP(
    RED, ___n___, ___n___, ___n___, ___n___, SPRING,    ___n___, SPRING, GREEN, RED,        ORANGE, PINK, ___n___, BLUE, ___n___, SPRING,           GREEN, GREEN, GREEN, GREEN,
    CYAN, ___n___, ___n___, ___n___, ___n___, ___n___,                                      ORANGE, MAGIPLY, ___n___, ___n___, ___n___, ___n___,
    GOLD, GOLD, GREEN, PURPLE, PURPLE, GREEN,                                               GREEN, CYAN, CYAN, CYAN, ___n___,    ___n___, 
    GREEN, CYAN, YELLOW, MAGENT, MAGENT, BLUE,                                              GREEN, CYAN, CYAN, CYAN, CYAN, ___n___, 
    ORANGE, GOLD, GREEN, PINK, PINK, CYAN,                                                  RED, CYAN, CYAN, CYAN, GOLD, ___n___,
    GREEN, GREEN, ESC, DEL, TOG_NAV, RED,                                                   GREEN, GREEN, TOG_NAV, TOG_SYM, ENTER, SPACE,
    ___n___, GREEN, ORANGE, RED, ___n___, GREEN, ORANGE, RED,                                BLUE, YELLOW, ORANGE, GREEN, RED, PURPLE, PINK, CYAN
    ),
   [_NAV]   = LEDMAP(
    RED, ___n___, ___n___, ___n___, ___n___, SPRING,    ___n___, SPRING, GREEN, RED,        RED, ORANGE, ___n___, ___n___, ___n___, ___n___,        GREEN, GREEN, GREEN, GREEN,
    CYAN, ___n___, ___n___, ___n___, ___n___, ___n___,                                      ___n___, ___n___, ___n___, ___n___, ___n___,    ___n___,
    GOLD, ___n___, ___n___, CYAN, ___n___, PURPLE,                                          GREEN,    CYAN,   GREEN,    CYAN,     RED,    ___n___, 
    GREEN, BLUE,  SPRING,    PINK,    CYAN, ___n___,                                        YELLOW,   GREEN,   GREEN,   GREEN,  YELLOW, ___n___, 
    ORANGE, ___n___, ___n___, ___n___, ___n___, ___n___,                                    PURPLE,  ORANGE,  ORANGE,  ORANGE,  PURPLE, ___n___,
    GREEN, YELLOW, ESC, DEL, TOG_NAV, RED,                                                  GREEN, GREEN, TOG_NAV, TOG_SYM, ENTER, SPACE,
    ___n___, GREEN, ORANGE, RED, ___n___, GREEN, ORANGE, RED,                                BLUE, YELLOW, ORANGE, GREEN, RED, PURPLE, PINK, CYAN
    ),
};
#endif // RGB_MATRIX_LEDMAPS_ENABLED

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!(process_record_keymap(keycode, record) && true)) {
        return false;
    }
    #if defined(DRAGSCROLL_ENABLE)
        if (keycode == DRAG_SCROLL && record->event.pressed) {
            set_scrolling = !set_scrolling;
            return false;
        }
    #endif
    // now we check for specific keycodes...
    #if defined(CUSTOM_KEYCODES)
        switch (keycode) {
            case ALT_TAB:
                if (record->event.pressed) {
                  if (!is_alt_tab_active) {
                    is_alt_tab_active = true;
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
                  if (!is_alt_tab_active) {
                    is_alt_tab_active = true;
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
                  if (!is_sup_alt_tab_active) {
                    is_sup_alt_tab_active = true;
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
            case LT(0,KC_TILD):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(LCMD(KC_TILD)); // hold for command+letter
                return false;
            }
            return true;
            case LT(0,KC_1):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(LCMD(KC_1)); // hold for command+letter
                return false;
            }
            return true;
            case LT(0,KC_2):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(LCMD(KC_2)); // hold for command+letter
                return false;
            }
            return true;
            case LT(0,KC_3):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(LCMD(KC_3)); // hold for command+letter
                return false;
            }
            return true;
            case LT(0,KC_4):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(LCMD(KC_4)); // hold for command+letter
                return false;
            }
            return true;
            case LT(0,KC_5):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(LCMD(KC_5)); // hold for command+letter
                return false;
            }
            return true;
            case LT(0,KC_6):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(LCMD(KC_6)); // hold for command+letter
                return false;
            }
            return true;
            case LT(0,KC_7):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(LCMD(KC_7)); // hold for command+letter
                return false;
            }
            return true;
            case LT(0,KC_8):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(LCMD(KC_8)); // hold for command+letter
                return false;
            }
            return true;
            case LT(0,KC_9):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(LCMD(KC_9)); // hold for command+letter
                return false;
            }
            return true;
            case LT(0,KC_Z):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(LCMD(KC_Z)); // hold for command+letter
                return false;
            }
            return true;
            case LT(0,KC_X):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(LCMD(KC_X)); // hold for command+letter
                return false;
            }
            return true;
            case LT(0,KC_C):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(LCMD(KC_C)); // hold for command+letter
                return false;
            }
            return true;
            case LT(0,KC_V):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(LCMD(KC_V)); // hold for command+letter
                return false;
            }
            return true;
            case LT(0,KC_B):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(LCMD(KC_B)); // hold for command+letter
                return false;
            }
            return true;
            case LT(0,KC_A):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(LCMD(KC_A)); // hold for command+letter
                return false;
            }
            return true;
            case LT(0,KC_R):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(LCMD(KC_R)); // hold for command+letter
                return false;
            }
            return true;
            case LT(0,KC_W):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(LCMD(KC_W)); // hold for command+letter
                return false;
            }
            return true;
            case LT(0,KC_T):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(LCMD(KC_T)); // hold for command+letter
                return false;
            }
            return true;
            case LT(0,KC_N):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(LCMD(LSFT(KC_N))); // hold for command+letter
                return false;
            }
            return true;
            case LT(0,KC_I):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(LCMD(KC_I)); // hold for command+letter
                return false;
            }
            return true;
            case LT(0,KC_MPLY):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(KC_MNXT); // hold for command+letter
                return false;
            }
            return true;
    }
    #endif // end CUSTOM_KEYCODES (for troubleshooting)
    return true;
}

/*
"emoji-coder"
- map of images to text strings e.g. :emoji-name:
- button activates function that sends text string
- function that changes image displayed depending on encoder rotation
*/

void matrix_scan_user(void) {
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 1000) {
      unregister_code(KC_LGUI);
      // unregister_code(KC_LSFT);
      is_alt_tab_active = false;
    }
  }
  if (is_sup_alt_tab_active) {
    if (timer_elapsed(sup_alt_tab_timer) > 50) {
      unregister_code(KC_LGUI);
      is_sup_alt_tab_active = false;
    }
  }
}

typedef enum {
    _LAYER = 0,
} relay_data_type;

void raw_hid_receive_kb(uint8_t *data, uint8_t length) {
    memset(data, 0, 32);
    printf("Receive data: %u %u %u \n", data[0], data[1], data[2]);
    // if (data[0] == _RELAY_TO_DEVICE) {
    //     switch (data[1]) {
    //         case _LAYER:
    //             layer_move(data[2]);
    //             break;
    //     }
    // }
}

layer_state_t layer_state_set_user(layer_state_t state) {
    uint8_t data[32];
    memset(data, 0, 32);
    data[0] = _RELAY_FROM_DEVICE;
    data[1] = _LAYER;
    data[2] = get_highest_layer(state);
    printf("Send data: %u %u %u \n", data[0], data[1], data[2]);
    raw_hid_send(data, 32);

    return state;
}