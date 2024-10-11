/*
 * Copyright 2023 Chris Trotter <ctrotter@gmail.com> (@christrotter)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Publicw License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "quantum.h"
#include "arcboard_mk15.h"
#include "keymap.h"

#if defined(RGB_MATRIX_LEDMAPS_ENABLED)
    #include "rgb_ledmaps.h"
#endif

#if defined(CONSOLE_ENABLE)
    #include "print.h"
#endif

void keyboard_post_init_user(void) {
    // I could not get the set_cpi_on_side to work properly.

    // if (is_keyboard_left()) {
    //     // pointing_device_set_cpi_on_side(true, LEFT_PMW_CPI);    //Set cpi on left side to a low value for slower scrolling.
    //     pointing_device_set_cpi(LEFT_PMW_CPI);
    //     uprintf("Our Left CPI:  %d \n", pointing_device_get_cpi());
    // } else {
    //     // pointing_device_set_cpi_on_side(false, RIGHT_PMW_CPI);  //Set cpi on right side to a reasonable value for mousing.
    //     // pointing_device_set_cpi_on_side(false, RIGHT_PMW_CPI);
    //     pointing_device_set_cpi(RIGHT_PMW_CPI);
    //     uprintf("Our Right CPI: %d \n", pointing_device_get_cpi());
    // }

    #if defined(CONSOLE_ENABLE)
        // Customise these values to desired behaviour
        // debug_enable=true;
        // debug_matrix=true;
        // debug_keyboard=true;
        // debug_mouse=true;
    #endif
}

#if defined(TAP_DANCE_ENABLE)
// Tap Dance definitions
enum {
    TD_SHIFT
};
tap_dance_action_t tap_dance_actions[] = {
    // we want to tap for oneshot, double tap to hold on, double tap to hold off
    // so tap= oneshot shift, doubletap= toggle shift on
    [TD_SHIFT] = ACTION_TAP_DANCE_DOUBLE(OSM(MOD_LSFT), KC_CAPS),
};
#endif

// clang-format off
    /* row,col
     * .------+------+------+------+------+------.                                                       .------+------+------+------+------+------.
     * |  1,1 |  1,2 |  1,3 |  1,4 |  1,5 |  1,6 |                                                       |  1,1 |  1,2 |  1,3 |  1,4 |  1,5 |  1,6 |
     * |------+------+------+------+------+------|                                                       |------+------+------+------+------+------|
     * |  2,1 |  2,2 |  2,3 |  2,4 |  2,5 |  2,6 |                                                       |  2,1 |  2,2 |  2,3 |  2,4 |  2,5 |  2,6 |
     * |------+------+------+------+------+------|                                                       |------+------+------+------+------+------|
     * |  3,1 |  3,2 |  3,3 |  3,4 |  3,5 |  3,6 |                                                       |  3,1 |  3,2 |  3,3 |  3,4 |  3,5 |  3,6 |
     * |------+------+------+------+------+------|                                                       |------+------+------+------+------+------|
     * |  4,1 |  4,2 |  4,3 |  4,4 |  4,5 |  4,6 |                                                       |  4,1 |  4,2 |  4,3 |  4,4 |  4,5 |  4,6 |
     * '------+------+------+------+------+------+------+------+------.             .------+------+------+------+------+------+------+------+------'
     *        |  trackball  |  5,1 |  5,2 |------|  6,1 |  6,2 |  6,3 |             |  6,1 |  6,2 |  6,3 |------|  5,1 |  5,2 |  trackball  |
     *        '-------------+------+------+------+------+------+------'             +------+------+------+------+------+------+-------------'
     *                      |  5,3 |  5,4 |  5,5 |  6,3 |  6,4 |                    |  6,3 |  6,4 |             |  5,3 |  5,4 |  5,5 |
     *                      '------+------+------+------+------' .------.  .------. '------+------'             +------+------+------'
     *                             |  5,6 |          |  6,5 |    |  6,6 |  |  6,6 |     |  6,5 |                       |  5,6 |
     *                             '------'          '------'    '------'  '------'     '------'                       '------'
     * 5,1-5,6  = thumb keys
     * 6,1-6,4  = 5-way/dpad up/down/left/right
     * 6,5      = 5-way/dpad button
     * 6,6      = falcon button
     */
// clang-format on

// left = up
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QWERTY] = LAYOUT(
    KC_TILD,LT(0,KC_1),LT(0,KC_2),LT(0,KC_3),LT(0,KC_4),LT(0,KC_5),     LT(0,KC_6),LT(0,KC_7),LT(0,KC_8),LT(0,KC_9),KC_0,KC_EQUAL,
    KC_TAB , KC_Q,LT(0,KC_W),HOME_E, LT(0,KC_R),LT(0,KC_T),             KC_Y,   KC_U,LT(0,KC_I), KC_O,   KC_P,   KC_MINUS,
    KC_LSFT, LT(0,KC_A),  HOME_S,  HOME_D,  HOME_F , KC_G,              KC_H,  HOME_J, HOME_K, HOME_L, KC_QUOT,KC_SCLN,
    ZOOM_VID,LT(0,KC_Z),LT(0,KC_X),LT(0,KC_C),LT(0,KC_V),LT(0,KC_B),    LT(0,KC_N), HOME_M, KC_COMM,KC_DOT, KC_SLASH, ZOOM_MUTE,
    MO(_NAV), KC_ESC, KC_DEL, OSM(MOD_LSFT), KC_TAB, GDOCZMIN,            KC_DOWN, KC_RIGHT, KC_UP, KC_B, KC_LEFT, KC_F,
    KC_BSPC, KC_DEL, KC_MULTILNE, KC_TAB, OSM(MOD_LSFT), KC_F,        KC_MULTILNE, KC_SPACE, OSM(MOD_LSFT),MO(_SYMBOLS), KC_ENTER, MAGIPLAY,
    __LED__, __LED__, __LED__, __LED__, __LED__, __LED__,               __LED__, __LED__, __LED__, __LED__, __LED__, __LED__,
    __LED__, __LED__, __LED__, __LED__, __LED__, __LED__,               __LED__, __LED__, __LED__, __LED__, __LED__, __LED__,
    __LED__, __LED__, __LED__, __LED__, __LED__, __LED__,               __LED__, __LED__, __LED__, __LED__, __LED__, __LED__,
    __LED__, __LED__, __LED__, __LED__, __LED__, __LED__,               __LED__, __LED__, __LED__, __LED__, __LED__, __LED__,
    __LED__, __LED__,                                                   __LED__, __LED__
),
[_MOUSE] = LAYOUT(
    QK_BOOT, EE_CLR, _______, _______, _______, _______,               _______, _______, _______, _______, EE_CLR, QK_BOOT,
    _______, _______, _______, _______, _______, _______,               KC_CHRMBACK, KC_CHRMFWD, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,               KC_CHRMBACK, KC_MS_BTN1,KC_MS_BTN3,KC_MS_BTN2, _______, _______,
    _______, _______, _______, _______, _______, _______,               KC_CHRMFWD, KC_MS_BTN1,KC_MS_BTN3,KC_MS_BTN2, _______, _______,
    _______, _______, _______, _______, _______, _______,               _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,               _______, _______, _______, _______, _______, _______,
    __LED__, __LED__, __LED__, __LED__, __LED__, __LED__,               __LED__, __LED__, __LED__, __LED__, __LED__, __LED__,
    __LED__, __LED__, __LED__, __LED__, __LED__, __LED__,               __LED__, __LED__, __LED__, __LED__, __LED__, __LED__,
    __LED__, __LED__, __LED__, __LED__, __LED__, __LED__,               __LED__, __LED__, __LED__, __LED__, __LED__, __LED__,
    __LED__, __LED__, __LED__, __LED__, __LED__, __LED__,               __LED__, __LED__, __LED__, __LED__, __LED__, __LED__,
    __LED__, __LED__,                                                   __LED__, __LED__
),
[_SYMBOLS] = LAYOUT(
    _______, _______, _______, _______, _______, _______,               KC_MACSHOT, MAGIPLAY, _______, _______, _______, _______,
    _______, KC_EXLM, KC_AT,   KC_LPRN, KC_RPRN, KC_AMPR,               KC_PPLS, KC_1,    KC_2,    KC_3,    KC_PMNS, KC_EQUAL,
    _______, KC_HASH, KC_DLR,  KC_LCBR, KC_RCBR, KC_GRV,                KC_PAST, KC_4,    KC_5,    KC_6,    KC_0,    KC_COMM,
    _______, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_PIPE,               KC_DOT,  KC_7,    KC_8,    KC_9,    KC_BSLS, _______,
    _______, _______, _______, _______, _______, _______,               _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,               _______, _______, _______, _______, _______, _______,
    __LED__, __LED__, __LED__, __LED__, __LED__, __LED__,               __LED__, __LED__, __LED__, __LED__, __LED__, __LED__,
    __LED__, __LED__, __LED__, __LED__, __LED__, __LED__,               __LED__, __LED__, __LED__, __LED__, __LED__, __LED__,
    __LED__, __LED__, __LED__, __LED__, __LED__, __LED__,               __LED__, __LED__, __LED__, __LED__, __LED__, __LED__,
    __LED__, __LED__, __LED__, __LED__, __LED__, __LED__,               __LED__, __LED__, __LED__, __LED__, __LED__, __LED__,
    __LED__, __LED__,                                                   __LED__, __LED__
),
[_NAV] = LAYOUT(
    _______, _______, _______, _______, _______, _______,               _______, _______, KC_SFTARROW_U, _______, _______, KC_F12,
    _______, _______, _______, LGUI(KC_TILD), _______, LT(0,KC_YAY),    KC_HOME, KC_ITRMSPCE_L, KC_UP, KC_ITRMSPCE_R, KC_END, _______,
    _______, KC_TAB_L, KC_TAB_R, KC_SPCLEFT, KC_SPCRGHT, _______,       KC_ALTARROW_L, KC_LEFT, KC_DOWN, KC_RIGHT, KC_ALTARROW_R, _______,
    _______, _______, _______, _______, _______, _______,              KC_SFTGUIARROW_L, KC_SFTALTARROW_L, KC_SFTARROW_D, KC_SFTALTARROW_R, KC_SFTGUIARROW_R, _______,
    _______, _______, _______ , _______, _______,KC_MACLOCK,            KC_TAB_R, KC_SPCRGHT, KC_TAB_L, KC_B, KC_SPCLEFT, KC_F,
    _______, _______, _______ , _______, _______, _______,              _______, _______, _______, _______, _______, _______,
    __LED__, __LED__, __LED__, __LED__, __LED__, __LED__,               __LED__, __LED__, __LED__, __LED__, __LED__, __LED__,
    __LED__, __LED__, __LED__, __LED__, __LED__, __LED__,               __LED__, __LED__, __LED__, __LED__, __LED__, __LED__,
    __LED__, __LED__, __LED__, __LED__, __LED__, __LED__,               __LED__, __LED__, __LED__, __LED__, __LED__, __LED__,
    __LED__, __LED__, __LED__, __LED__, __LED__, __LED__,               __LED__, __LED__, __LED__, __LED__, __LED__, __LED__,
    __LED__, __LED__,                                                   __LED__, __LED__
)
};

// TODO do we need this?
__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) { return true; }

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!(process_record_keymap(keycode, record)
        #if defined(RGB_MATRIX_LEDMAPS_ENABLED)
            && process_record_user_rgb_matrix(keycode, record)
        #endif
        #if defined(CUSTOM_POINTING_DEVICE)
            && process_record_pointing(keycode, record)
        #endif
          && true)) {
        return false;
    }
    #if defined(DRAGSCROLL_ENABLE)
        if (keycode == DRAG_SCROLL && record->event.pressed) {
            set_scrolling = !set_scrolling;
            uprintf("Scrolling bool: %s \n", set_scrolling ? "true" : "false");
        }
    #endif
    // now we check for specific keycodes...
    #if defined(CUSTOM_KEYCODES)
        switch (keycode) {
                case LT(0,KC_YAY):
                if (record->event.pressed) {
                    // when keycode YAY is pressed
                    SEND_STRING("\\o/");
                } else {
                    // when keycode YAY is released
                }
                return true;
                case LT(0,KC_TILD):
                if (!record->tap.count && record->event.pressed) {
                    tap_code16(LCMD(KC_TILD)); // hold for command+letter
                    return false;
                }
                return true;             // Return true for normal processing of tap keycode
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
                // a bunch of these are commented out cuz homerow mods in play
//                case LT(0,KC_S):
//                if (!record->tap.count && record->event.pressed) {
//                    tap_code16(LCMD(KC_S)); // hold for command+letter
//                    return false;
//                }
//                return true;             // Return true for normal processing of tap keycode
                case LT(0,KC_Z):
                if (!record->tap.count && record->event.pressed) {
                    tap_code16(LCMD(KC_Z)); // hold for command+letter
                    return false;
                }
                return true;             // Return true for normal processing of tap keycode
                case LT(0,KC_X):
                if (!record->tap.count && record->event.pressed) {
                    tap_code16(LCMD(KC_X)); // hold for command+letter
                    return false;
                }
                return true;             // Return true for normal processing of tap keycode
                case LT(0,KC_C):
                if (!record->tap.count && record->event.pressed) {
                    tap_code16(LCMD(KC_C)); // hold for command+letter
                    return false;
                }
                return true;             // Return true for normal processing of tap keycode
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
//                case LT(0,KC_K):
//                if (!record->tap.count && record->event.pressed) {
//                    tap_code16(LCMD(KC_K)); // hold for command+letter
//                    return false;
//                }
//                return true;
//                case LT(0,KC_L):
//                if (!record->tap.count && record->event.pressed) {
//                    tap_code16(LCMD(KC_L)); // hold for command+letter
//                    return false;
//                }
//                return true;
                case LT(0,KC_T):
                if (!record->tap.count && record->event.pressed) {
                    tap_code16(LCMD(KC_T)); // hold for command+letter
                    return false;
                }
                return true;
//                case LT(0,KC_F):
//                if (!record->tap.count && record->event.pressed) {
//                    tap_code16(LCMD(KC_F)); // hold for command+letter
//                    return false;
//                }
//                return true;
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
// what does this do...
// the bool process_record_keymap is first called, then pulled in by process_record_user, then...
// i.e. 'do we have a record to process: true/false'
// post_process_record_keymap is a drashna thing: takes in the keyrecord itself
// post_process_record_user is a qmk thing: it recurses into post_process_record_kb, which recurses into post_process_record_quantum,
// which calls get_record_keycode which returns get_event_keycode

// still kinda fuzzy on the order of operations/hierarchy here...
// TODO pull this out
__attribute__((weak)) void post_process_record_keymap(uint16_t keycode, keyrecord_t *record) {}
void                       post_process_record_user(uint16_t keycode, keyrecord_t *record) { post_process_record_keymap(keycode, record); }

#if defined(RGB_MATRIX_LEDMAPS_ENABLED)
// the indicator LEDs are mapped using the flags and for loop.

    // MO(_NAV), KC_ESC, KC_DEL, OSM(MOD_LSFT), KC_B, GDOCZMIN,            KC_DOWN, KC_RIGHT, KC_UP, KC_B, KC_LEFT, KC_F,
    // KC_BSPC, DRAG_TOG, KC_MULTILNE, KC_TAB, OSM(MOD_LSFT), KC_F,        KC_MULTILNE, KC_SPACE, OSM(MOD_LSFT),MO(_SYMBOLS), KC_ENTER, MAGIPLAY,
const ledmap ledmaps[] = {
    [_QWERTY]   = LEDMAP(
      CYAN, ___n___, ___n___, ___n___, ___n___, ___n___,              CYAN, ___n___, ___n___, ___n___, ___n___,    CYAN,
      GOLD, ___n___, ___n___, HRM_CTL, ___n___, ___n___,           ___n___, ___n___, ___n___, ___n___, ___n___,    CYAN,
     GREEN, ___n___, HRM_ALT, HRM_GUI, HRM_SFT, ___n___,           ___n___, HRM_SFT, HRM_GUI, HRM_ALT, ___n___, ___n___,
      RED, ___n___, ___n___, ___n___, ___n___, ___n___,           ___n___, HRM_CTL, ___n___, ___n___, ___n___,     RED,
    TOG_NAV,    ESC,     DEL,   SHIFT,    GOLD,    CYAN,             GREEN,   SPACE,   SHIFT, TOG_SYM,   ENTER,    PINK,
     FL_L0, FL_L0, FL_L0, FL_L0, FL_L0, FL_L0,                           FR_L0, FR_L0, FR_L0, FR_L0, FR_L0, FR_L0,
     FL_L0, FL_L0, FL_L0, FL_L0, FL_L0, FL_L0,                           FR_L0, FR_L0, FR_L0, FR_L0, FR_L0, FR_L0,
     ___n___, ___n___, ___n___, ___n___, ___n___, ___n___,         ___n___, ___n___, ___n___, ___n___, ___n___, ___n___,
     ___n___, ___n___, ___n___, ___n___, ___n___, ___n___,         ___n___, ___n___, ___n___, ___n___, ___n___, ___n___,
     ___n___, ___n___,                                             ___n___, ___n___
   ),
   [_MOUSE]     = LEDMAP(
      RED,   YELLOW, ___n___, ___n___, ___n___, ___n___,           ___n___, ___n___, ___n___, ___n___,  YELLOW,     RED,
      GOLD, ___n___, ___n___, ___n___, ___n___, ___n___,               RED,   GREEN, ___n___, ___n___, ___n___, ___n___,
     GREEN, ___n___, ___n___, ___n___, ___n___, ___n___,               RED,    CYAN,    PINK,    CYAN, ___n___, ___n___,
       RED, ___n___, ___n___, ___n___, ___n___, ___n___,             GREEN,    CYAN,    PINK,    CYAN, ___n___,     RED,
    TOG_NAV,    ESC,     DEL,   SHIFT,    GOLD,    CYAN,             GREEN,   SPACE,   SHIFT, TOG_SYM,   ENTER,    PINK,
     FL_L1, FL_L1, FL_L1, FL_L1, FL_L1, FL_L1,                           FR_L1, FR_L1, FR_L1, FR_L1, FR_L1, FR_L1,
     FL_L1, FL_L1, FL_L1, FL_L1, FL_L1, FL_L1,                           FR_L1, FR_L1, FR_L1, FR_L1, FR_L1, FR_L1,
     ___n___, ___n___, ___n___, ___n___, ___n___, ___n___,         ___n___, ___n___, ___n___, ___n___, ___n___, ___n___,
     ___n___, ___n___, ___n___, ___n___, ___n___, ___n___,         ___n___, ___n___, ___n___, ___n___, ___n___, ___n___,
     ___n___, ___n___,                                             ___n___, ___n___
   ),
   [_SYMBOLS]   = LEDMAP(
      CYAN, ___n___, ___n___, ___n___, ___n___, ___n___,          ORANGE, MAGIPLY, ___n___, ___n___, ___n___, ___n___,
      GOLD,    GOLD,   GREEN,  PURPLE,  PURPLE,   GREEN,           GREEN,    CYAN,    CYAN,    CYAN, ___n___, ___n___,
     GREEN,    CYAN,  YELLOW,  MAGENT,  MAGENT,    BLUE,           GREEN,    CYAN,    CYAN,    CYAN,    CYAN, ___n___,
       RED,    GOLD,   GREEN,   PINK,     PINK,    CYAN,             RED,    CYAN,    CYAN,    CYAN,    GOLD,     RED,
    TOG_NAV,    ESC,     DEL,   SHIFT,    GOLD,    CYAN,             GREEN,   SPACE,   SHIFT, TOG_SYM,   ENTER,    PINK,
     FL_L2, FL_L2, FL_L2, FL_L2, FL_L2, FL_L2,                           FR_L2, FR_L2, FR_L2, FR_L2, FR_L2, FR_L2,
     FL_L2, FL_L2, FL_L2, FL_L2, FL_L2, FL_L2,                           FR_L2, FR_L2, FR_L2, FR_L2, FR_L2, FR_L2,
     ___n___, ___n___, ___n___, ___n___, ___n___, ___n___,         ___n___, ___n___, ___n___, ___n___, ___n___, ___n___,
     ___n___, ___n___, ___n___, ___n___, ___n___, ___n___,         ___n___, ___n___, ___n___, ___n___, ___n___, ___n___,
     ___n___, ___n___,                                             ___n___, ___n___
   ),
   [_NAV]       = LEDMAP(
      CYAN, ___n___, ___n___, ___n___, ___n___, ___n___,           ___n___, ___n___,  ORANGE, ___n___, ___n___,  YELLOW,
      GOLD, ___n___, ___n___,    CYAN, ___n___,  PURPLE,             GREEN,    CYAN,   GREEN,    CYAN,     RED, ___n___,
     GREEN,    BLUE,  SPRING,    PINK,    CYAN,   GREEN,            YELLOW,   GREEN,   GREEN,   GREEN,  YELLOW, ___n___,
       RED, ___n___, ___n___, ___n___, ___n___,     RED,            PURPLE,  ORANGE,  ORANGE,  ORANGE,  PURPLE,     RED,
    TOG_NAV,    ESC,     DEL,   SHIFT,    GOLD,  YELLOW,             GREEN,   SPACE,   SHIFT, TOG_SYM,   ENTER,    PINK,
     FL_L3, FL_L3, FL_L3, FL_L3, FL_L3, FL_L3,                           FR_L3, FR_L3, FR_L3, FR_L3, FR_L3, FR_L3,
     FL_L3, FL_L3, FL_L3, FL_L3, FL_L3, FL_L3,                           FR_L3, FR_L3, FR_L3, FR_L3, FR_L3, FR_L3,
     ___n___, ___n___, ___n___, ___n___, ___n___, ___n___,         ___n___, ___n___, ___n___, ___n___, ___n___, ___n___,
     ___n___, ___n___, ___n___, ___n___, ___n___, ___n___,         ___n___, ___n___, ___n___, ___n___, ___n___, ___n___,
     ___n___, ___n___,                                             ___n___, ___n___
   ),
};
#endif // RGB_MATRIX_LEDMAPS_ENABLED

// encoder functions per layer, LEFT        RIGHT
#if defined(ENCODER_MAP_ENABLE)
    const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
        [_QWERTY]   =  { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN),    ENCODER_CCW_CW(TO(_MOUSE), KC_NO)},
        [_MOUSE]    =  { ENCODER_CCW_CW(KC_SPCLEFT, KC_SPCRGHT),            ENCODER_CCW_CW(TO(_SYMBOLS), TO(_QWERTY))},
        [_SYMBOLS]  =  { ENCODER_CCW_CW(GDOCZMIN, GDOCZMOU),            ENCODER_CCW_CW(TO(_NAV), TO(_MOUSE))},
        [_NAV]      =  { ENCODER_CCW_CW(KC_VOLU, KC_VOLD),              ENCODER_CCW_CW(KC_NO, TO(_SYMBOLS))},
    };
#endif

////  POINTING DEVICE SECTION  ////

#if defined(POINTING_DEVICE_ENABLE)
    void pointing_device_init_user(void) {
        set_auto_mouse_enable(true);
    }
    // TODO do we need this?
    void pointing_device_init_kb(void) {
        pointing_device_init_user(); // set auto mouse layer
    }

    report_mouse_t pointing_device_task_combined_user(report_mouse_t left_report, report_mouse_t right_report) {
        left_report.h = left_report.x;
        left_report.v = left_report.y;
        left_report.x = 0;
        left_report.y = 0;
        return pointing_device_combine_reports(left_report, right_report);
    }
#endif
