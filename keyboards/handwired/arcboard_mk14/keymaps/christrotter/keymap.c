/*
 * Copyright 2020 Christopher Courtney <drashna@live.com> (@drashna)
 * Copyright 2021 Quentin LEBASTARD <qlebastard@gmail.com>
 * Copyright 2022 Charly Delay <charly@codesink.dev> (@0xcharly)
 * Copyright 2022 Chris Trotter <ctrotter@gmail.com> (@christrotter)
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

#include QMK_KEYBOARD_H

#if defined(POINTING_DEVICE_ENABLE) && defined(DRAGSCROLL_ENABLE)
    #define DRAG_TOG DRAG_SCROLL
    bool set_scrolling = false;
#else
    #define DRAG_TOG KC_NO
#endif

#define XXX KC_NO

#define KC_CAD	LALT(LCTL(KC_DEL))
#define KC_MACLOCK	LGUI(LCTL(KC_Q))
#define KC_MACSHOT	LGUI(LSFT(KC_4))
// move between mac workspaces
#define KC_SPCLEFT	LCTL(KC_LEFT)
#define KC_SPCRGHT	LCTL(KC_RIGHT)
#define KC_ITRMSPCE_L  LGUI(KC_LEFT) // iterm switch spaces left
#define KC_ITRMSPCE_R  LGUI(KC_RIGHT) // iterm switch spaces right
#define KC_ITRMPANE_L  LGUI(LSFT(KC_LEFT)) // iterm switch panes left
#define KC_ITRMPANE_R  LGUI(LSFT(KC_RIGHT)) // iterm switch panes right
// move between tabs // this sort of worked...
#define KC_TAB_L	LGUI(LALT(KC_LEFT))
#define KC_TAB_R	LGUI(LALT(KC_RIGHT))

#define KC_MULTILNE	LGUI(LALT(KC_LSFT))

#define KC_CHRMBACK LGUI(KC_LBRC)
#define KC_CHRMFWD LGUI(KC_RBRC)

// we want to handle word movement (nav) and word select (symbols) on the arrow cluster
// KC_LEFT, KC_UP, KC_DOWN, KC_RIGHT
#define KC_SFTGUIARROW_L LGUI(LSFT(KC_LEFT))
#define KC_SFTGUIARROW_R LGUI(LSFT(KC_RIGHT))
#define KC_ALTARROW_L LALT(KC_LEFT)
#define KC_ALTARROW_R LALT(KC_RIGHT)
#define KC_SFTALTARROW_L LALT(LSFT(KC_LEFT))
#define KC_SFTALTARROW_R LALT(LSFT(KC_RIGHT))
#define KC_SFTARROW_U LSFT(KC_UP)
#define KC_SFTARROW_D LSFT(KC_DOWN)

#define ZOOM_MUTE LSFT(LGUI(KC_COMM))

// to help with the nature of the trackball bearings, let's try using macos' zoom functionality
// #define KC_MAC_ZOOM LALT(KC_LCTL)

enum custom_keycodes {
    KC_YAY = SAFE_RANGE,
};
// can we have a single enum list? // i don't get how this works, obvs
enum {
    TD_SHIFT
};

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    // we want to tap for oneshot, double tap to hold on, double tap to hold off
    // so tap= oneshot shift, doubletap= toggle shift on
    [TD_SHIFT] = ACTION_TAP_DANCE_DOUBLE(OSM(MOD_LSFT), KC_CAPS),
    //
};

// Left-hand home row mods
#define HOME_E LCTL_T(KC_E)
#define HOME_S LALT_T(KC_S)
#define HOME_D LGUI_T(KC_D)
#define HOME_F LSFT_T(KC_F)
// Right-hand home row mods
#define HOME_J RSFT_T(KC_J)
#define HOME_K RGUI_T(KC_K)
#define HOME_L LALT_T(KC_L)
#define HOME_M RCTL_T(KC_M)

// Media keys
#define MAGIPLAY LT(0,KC_MPLY)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
// clang-format off
    /* row,col
     * ,------------------------------------------------,                             ,------------------------------------------------,
     * |  1,1 |  1,2 |  1,3 |  1,4 |  1,5 |  1,6 |  1,7 |                             |  1,1 |  1,2 |  1,3 |  1,4 |  1,5 |  1,6 |  1,7 |
     * |------+------+------+------+------+------+------|                             |------+------+------+------+------+------+------|
     * |  2,1 |  2,2 |  2,3 |  2,4 |  2,5 |  2,6 |  2,7 |                             |  2,1 |  2,2 |  2,3 |  2,4 |  2,5 |  2,6 |  2,7 |
     * |------+------+------+------+------+------+------|                             |------+------+------+------+------+------+------|
     * |  3,1 |  3,2 |  3,3 |  3,4 |  3,5 |  3,6 |  3,7 |                             |  3,1 |  3,2 |  3,3 |  3,4 |  3,5 |  3,6 |  3,7 |
     * |------+------+------+------+------+------+------|                             |------+------+------+------+------+------+------|
     * |  4,1 |  4,2 |  4,3 |  4,4 |  4,5 |  4,6 |  4,7 |                             |  4,1 |  4,2 |  4,3 |  4,4 |  4,5 |  4,6 |  4,7 |
     * |------+------+------+------+------+------+------|                             |------+------+------+------+------+------+------|
     * |  5,1 |  5,2 |  5,3 |  5,4 |  5,5 |  5,6 |  5,7 |                             |  5,1 |  5,2 |  5,3 |  5,4 |  5,5 |  5,6 |  5,7 |
     * |------+------+------+------+------+------+------+------,        ,------|------+------+----+-+----+-+------+------+------|------|
     *               |  6,1 | 6,2  |             | 7,1  | 7,2  |        | 7,1  | trackball | 7,5  | 7,6  | |  6,1 | 6,2  |
     *               `------+------+------+------+------+------|        '-+----'-+-----,---+------+------+ '------+------+
     *                             | 7,6  | 7,5  | 7,4  | 7,3  |                 | 7,3 | 7,4  |
     *                             '------+------+------+------'              ,--+-----+------'
     *                                                                       | 7,2  |
     *                                                                        '------'
     * Sorry about the reversing of the left thumb column...wiring from underneath causes natural mirroring!
     */
// clang-format on

[_QWERTY] = LAYOUT(
    XXX    , XXX,     XXX,     XXX,     XXX,     XXX,      XXX,                 KC_A,     XXX,     XXX,     XXX,     XXX,     XXX,     XXX,
    KC_GRV,LT(0,KC_1),LT(0,KC_2),LT(0,KC_3),LT(0,KC_4),LT(0,KC_5), XXX,         XXX,LT(0,KC_6),LT(0,KC_7),LT(0,KC_8),LT(0,KC_9),KC_0,KC_EQUAL,
    KC_TAB , KC_Q,LT(0,KC_W),HOME_E, LT(0,KC_R),LT(0,KC_T),  XXX,               XXX,   KC_Y,   KC_U,LT(0,KC_I), KC_O,   KC_P,   KC_MINUS,
    KC_LSFT, LT(0,KC_A),  HOME_S,  HOME_D,  HOME_F , KC_G,   XXX,               XXX,KC_H,  HOME_J, HOME_K, HOME_L, KC_QUOT,KC_SCLN,
    DRAG_TOG,LT(0,KC_Z),LT(0,KC_X),LT(0,KC_C),LT(0,KC_V),LT(0,KC_B),XXX,       XXX, LT(0,KC_N), HOME_M, KC_COMM,KC_DOT, KC_SLASH, ZOOM_MUTE,
                      KC_DOWN, KC_UP,                                                                      KC_LEFT, KC_RIGHT,
            KC_BSPC, MO(_NAV), KC_DEL, KC_ESC, XXX, OSM(MOD_LSFT),     KC_MULTILNE, XXX, MO(_SYMBOLS), XXX, KC_ENTER,KC_SPACE
),
[_MOUSE] = LAYOUT(
    _______, _______, _______, _______, _______, _______, _______,              _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______,              _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______,              _______, KC_CHRMBACK, KC_CHRMFWD, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______,              _______, DRAG_TOG, KC_MS_BTN1,KC_MS_BTN3,KC_MS_BTN2, _______, _______,
    _______, _______, _______, _______, _______, _______, _______,              _______, _______, _______, _______, _______, _______, _______,
                      _______, _______,                                                                      _______, _______,
    _______, _______ , _______ , _______, _______, _______,                       _______, _______, _______, _______, _______, _______
),
[_SYMBOLS] = LAYOUT(
    _______, _______, _______, _______, _______, _______, _______,              _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______,              _______, KC_MACSHOT, MAGIPLAY, _______, _______, _______, _______,
    _______, KC_EXLM, KC_AT,   KC_LPRN, KC_RPRN, KC_AMPR, _______,              _______, KC_PPLS, KC_1,    KC_2,    KC_3,    KC_PMNS, KC_EQUAL,
    _______, KC_HASH, KC_DLR,  KC_LCBR, KC_RCBR, KC_GRV,  _______,              _______, KC_PAST, KC_4,    KC_5,    KC_6,    KC_0,    KC_COMM,
    _______, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_PIPE, _______,              _______, KC_DOT,  KC_7,    KC_8,    KC_9,    KC_BSLS, _______,
                      _______, _______,                                                                      _______, _______,
               _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______
),
[_NAV] = LAYOUT(
    _______, _______, _______, _______, _______, _______, _______,                       _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______,                       _______, _______, _______, KC_SFTARROW_U, _______, _______, KC_F12,
    _______, _______, _______, LGUI(KC_TILD), _______, LT(0,KC_YAY), _______,            _______, KC_HOME, KC_ITRMSPCE_L, KC_UP, KC_ITRMSPCE_R, KC_END, _______,
    _______, KC_TAB_L, KC_TAB_R, KC_SPCLEFT, KC_SPCRGHT, KC_PGUP, _______,               _______, KC_ALTARROW_L, KC_LEFT, KC_DOWN, KC_RIGHT, KC_ALTARROW_R, _______,
    _______, _______, _______, _______, _______, DRAG_TOG, KC_PGDN,                       _______, KC_SFTGUIARROW_L, KC_SFTALTARROW_L, KC_SFTARROW_D, KC_SFTALTARROW_R, KC_SFTGUIARROW_R, _______,
                      _______, _______,                                                                      _______, _______,
                _______, _______, _______, KC_MACLOCK, _______, _______,          _______, _______, _______, _______, _______, _______
)
};

__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) { return true; }

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!(process_record_keymap(keycode, record)
        #if defined(RGB_MATRIX_LEDMAPS_ENABLED)
            && process_record_user_rgb_matrix(keycode, record)
        #endif
        #ifdef CUSTOM_POINTING_DEVICE
            && process_record_pointing(keycode, record)
        #endif
          && true)) {
        return false;
    }
    #if defined(DRAGSCROLL_ENABLE)
        if (keycode == DRAG_SCROLL && record->event.pressed) {
            set_scrolling = !set_scrolling;
        }
    #endif
    // now we check for specific keycodes...
    #ifdef CUSTOM_KEYCODES
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

__attribute__((weak)) void post_process_record_keymap(uint16_t keycode, keyrecord_t *record) {}
void                       post_process_record_user(uint16_t keycode, keyrecord_t *record) { post_process_record_keymap(keycode, record); }

#ifdef RGB_MATRIX_LEDMAPS_ENABLED

#define ___n___ {0, 0, 0}

// constants across all layers, vs. setting key-led-slots individually
#define TOG_MSE BLUE
#define TOG_NAV CHART
#define TOG_SYM PINK
#define DRAG ORANGE
#define MAGIPLY PINK
#define HOME GREEN
#define END RED
#define PGUP GREEN
#define PGDN RED
#define SPACE GREEN
#define ENTER CYAN
#define SHIFT GREEN
#define BCKSPC RED
#define DEL RED
#define ESC RED
#define CMD PURPLE
#define HRM_CTL BLUE
#define HRM_ALT YELLOW
#define HRM_GUI PURPLE
#define HRM_SFT GREEN

#define IND1 WHITE

/* If the shift mod state has changed, redraw accordingly. */
void set_indicator_colour_user(void) {
    bool is_shifted_redraw = false;
    static uint32_t last_is_shifted_state = 0;
    if (last_is_shifted_state  != ((get_mods() | get_weak_mods()) & MOD_MASK_SHIFT)) {
        last_is_shifted_state   = ((get_mods() | get_weak_mods()) & MOD_MASK_SHIFT);
        is_shifted_redraw = true;
    }

    if (is_shifted_redraw ) {
        bool is_shifted = (get_mods() | get_weak_mods()) & MOD_MASK_SHIFT;
        if (is_shifted) {
            #undef IND1
            #define IND1 GREEN
        } else {
            #undef IND1
            #define IND1 WHITE
        }
    }
}



// note the left thumb cluster order is weird - cuz i got the wiring wrong and didn't fix it

const ledmap PROGMEM ledmaps[] = {
    [_QWERTY] = RGB_MATRIX_LAYOUT_LEDMAP(
//    ___n___, ___n___, ___n___, ___n___, ___n___, ___n___, ___n___,              ___n___, ___n___, ___n___, ___n___, ___n___, ___n___, ___n___,
    ___n___, ___n___, GREEN, GREEN, ___n___, ___n___, ___n___,                  IND1, IND1, IND1, IND1, IND1, IND1, IND1,
       CYAN, ___n___, ___n___, ___n___, ___n___, ___n___, ___n___,              ___n___, ___n___, ___n___, ___n___, ___n___, ___n___,    CYAN,
       GOLD, ___n___, ___n___, HRM_CTL, ___n___, ___n___, ___n___,              ___n___, ___n___, ___n___, ___n___, ___n___, ___n___,    CYAN,
      GREEN, ___n___, HRM_ALT, HRM_GUI, HRM_SFT, ___n___, ___n___,              ___n___, ___n___, HRM_SFT, HRM_GUI, HRM_ALT, ___n___, ___n___,
       DRAG, ___n___, ___n___, ___n___, ___n___, ___n___, ___n___,              ___n___, ___n___, HRM_CTL, ___n___, ___n___, ___n___,     RED,
                      ___n___, ___n___,                                                                    ___n___, ___n___,
                          SHIFT, ___n___, ESC, DEL, TOG_NAV,  BCKSPC,              SHIFT, ___n___, TOG_SYM, ___n___, ENTER, SPACE
    ),
    [_MOUSE] = RGB_MATRIX_LAYOUT_LEDMAP(
    ___n___, ___n___, ___n___, ___n___, ___n___, ___n___, ___n___,              ___n___, ___n___, ___n___, ___n___, ___n___, ___n___, ___n___,
       CYAN, ___n___, ___n___, ___n___, ___n___, ___n___, ___n___,              ___n___, ___n___, ___n___, ___n___, ___n___, ___n___, ___n___,
       GOLD, ___n___, ___n___, ___n___, ___n___, ___n___, ___n___,              ___n___,     RED,   GREEN, ___n___, ___n___, ___n___, ___n___,
      GREEN, ___n___, ___n___, ___n___, ___n___, ___n___, ___n___,              ___n___,    DRAG,    CYAN,    PINK,    CYAN, ___n___, ___n___,
       DRAG, ___n___, ___n___, ___n___, ___n___, ___n___, ___n___,              ___n___, ___n___, ___n___, ___n___, ___n___, ___n___,     RED,
                      ___n___, ___n___,                                                                    ___n___, ___n___,
                          SHIFT, ___n___, ESC, DEL, TOG_NAV,  BCKSPC,              SHIFT, ___n___, TOG_SYM, ___n___, ENTER, SPACE
    ),
    [_SYMBOLS] = RGB_MATRIX_LAYOUT_LEDMAP(
    ___n___, ___n___, ___n___, ___n___, ___n___, ___n___, ___n___,              ___n___, ___n___, ___n___, ___n___, ___n___, ___n___, ___n___,
       CYAN, ___n___, ___n___, ___n___, ___n___, ___n___, ___n___,              ___n___,  ORANGE, MAGIPLY, ___n___, ___n___, ___n___, ___n___,
       GOLD,    GOLD,   GREEN,  PURPLE,  PURPLE,   GREEN, ___n___,              ___n___,   GREEN,    CYAN,    CYAN,    CYAN, ___n___, ___n___,
      GREEN,    CYAN,  YELLOW,  MAGENT,  MAGENT,    BLUE, ___n___,              ___n___,   GREEN,    CYAN,    CYAN,    CYAN,    CYAN, ___n___,
       DRAG,    GOLD,   GREEN,   PINK,     PINK,    CYAN, ___n___,              ___n___,     RED,    CYAN,    CYAN,    CYAN,    GOLD,     RED,
                      ___n___, ___n___,                                                                    ___n___, ___n___,
                          SHIFT, ___n___, ESC, DEL, TOG_NAV,  BCKSPC,              SHIFT, ___n___, TOG_SYM, ___n___, ENTER, SPACE
    ),
    [_NAV] = RGB_MATRIX_LAYOUT_LEDMAP(
    ___n___, ___n___, ___n___, ___n___, ___n___, ___n___, ___n___,              ___n___, ___n___, ___n___, ___n___, ___n___, ___n___, ___n___,
       CYAN, ___n___, ___n___, ___n___, ___n___, ___n___, ___n___,              ___n___, ___n___, ___n___,  ORANGE, ___n___, ___n___, ___n___,
       GOLD, ___n___, ___n___,    CYAN, ___n___,  PURPLE, ___n___,              ___n___,   GREEN,    CYAN,   GREEN,    CYAN,     RED, ___n___,
      GREEN,    BLUE,  SPRING,    PINK,    CYAN,   GREEN, ___n___,              ___n___,  YELLOW,   GREEN,   GREEN,   GREEN,  YELLOW, ___n___,
       DRAG, ___n___, ___n___, ___n___, ___n___,     RED, ___n___,              ___n___,  PURPLE,  ORANGE,  ORANGE,  ORANGE,  PURPLE,     RED,
                      ___n___, ___n___,                                                                    ___n___, ___n___,
                        SHIFT, ___n___, YELLOW, DEL, TOG_NAV,  BCKSPC,              SHIFT, ___n___, TOG_SYM, ___n___, ENTER, SPACE
    )
};
#endif // RGB_MATRIX_LEDMAPS_ENABLED

////  POINTING DEVICE SECTION  ////

#ifdef POINTING_DEVICE_ENABLE
void pointing_device_init_user(void) {
    set_auto_mouse_enable(true);
}
void pointing_device_init_kb(void) {
    pointing_device_init_user(); // set auto mouse layer
}

// We want this specifically for the dragscroll reverse x
#if defined(CUSTOM_DRAGSCROLL)
static void pointing_device_task_custom(report_mouse_t* mouse_report) {
    static int16_t scroll_buffer_x = 0;
    static int16_t scroll_buffer_y = 0;
    if (set_scrolling) {
#    ifdef DRAGSCROLL_REVERSE_X
        scroll_buffer_x -= mouse_report->x;
#    else
        scroll_buffer_x += mouse_report->x;
#    endif // DRAGSCROLL_REVERSE_X
#    ifdef DRAGSCROLL_REVERSE_Y
        scroll_buffer_y -= mouse_report->y;
#    else
        scroll_buffer_y += mouse_report->y;
#    endif // DRAGSCROLL_REVERSE_Y
        mouse_report->x = 0;
        mouse_report->y = 0;
        if (abs(scroll_buffer_x) > DRAGSCROLL_BUFFER_SIZE) {
            mouse_report->h = scroll_buffer_x > 0 ? 1 : -1;
            scroll_buffer_x = 0;
        }
        if (abs(scroll_buffer_y) > DRAGSCROLL_BUFFER_SIZE) {
            mouse_report->v = scroll_buffer_y > 0 ? 1 : -1;
            scroll_buffer_y = 0;
        }
    }
}
#endif

report_mouse_t pointing_device_task_kb(report_mouse_t mouse_report) {
    // code belonging to the 'fix dragscroll inversion' above
    #if defined(CUSTOM_DRAGSCROLL)
        if (!(is_keyboard_left())) {
            pointing_device_task_custom(&mouse_report);
            mouse_report = pointing_device_task_user(mouse_report);
            if (set_scrolling) {
                pointing_device_set_cpi(DRAGSCROLL_CPI);
            } else {
                pointing_device_set_cpi(PMW33XX_CPI);
            }
        }
    #endif
    return mouse_report;
}
#endif
