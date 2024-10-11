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
#include "arcboard_mk17.h"
#include "keymap.h"

#ifdef MACCEL_ENABLE
    #include "maccel.h"
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

#if defined(CONSOLE_ENABLE)
    #include "print.h"
    void keyboard_post_init_user(void) {
        // Customise these values to desired behaviour
        // debug_enable=true;
        // debug_matrix=true;
        // debug_keyboard=true;
        // debug_mouse=true;

        #if defined(POINTING_DEVICE_ENABLE)
            pointing_device_set_cpi_on_side(true, LEFT_PMW_CPI);
            pointing_device_set_cpi_on_side(false, RIGHT_PMW_CPI);
        #endif
    }
#endif

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

__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) { return true; }
__attribute__((weak)) void post_process_record_keymap(uint16_t keycode, keyrecord_t *record) {}
void                       post_process_record_user(uint16_t keycode, keyrecord_t *record) { post_process_record_keymap(keycode, record); }

#if defined(QUANTUM_PAINTER_ENABLE)
    #include "qp_st7789.h"
    #include <qp.h>
    #include "graphics/futura40.qff.c"
    static painter_font_handle_t font;
    static painter_device_t display;
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
        }
        return "unknown";
    }

    void init_ui(void) {
        font = qp_load_font_mem(font_futura40);
        display = qp_st7789_make_spi_device(320, 240, DISPLAY_CS_PIN, DISPLAY_DC_PIN, DISPLAY_RST_PIN, DISPLAY_SPI_DIVISOR, 3);
        qp_init(display, QP_ROTATION_270);
        // could not get the backlight feature working, sorry elpekenin!
        setPinOutput(DISPLAY_LED_PIN);
        writePinHigh(DISPLAY_LED_PIN);

        qp_rect(display, 0, 0, 320, 240, HSV_BLACK, true);
        qp_flush(display);
    }

    void draw_ui_user(void) {
        uint16_t width;
        uint16_t height;
        qp_get_geometry(display, &width, &height, NULL, NULL, NULL);
        #if defined(CONSOLE_ENABLE)
            char buf[32] = {0};
        #endif
        bool layer_state_redraw = false;
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
            #if defined(CONSOLE_ENABLE)
                snprintf(buf, sizeof(buf), "%s", layer_name);
            #endif
            int mouse_layer = strcmp(layer_name, mouse);
            int qwerty_layer = strcmp(layer_name, qwerty);
            int nav_layer = strcmp(layer_name, nav);
            int symbols_layer = strcmp(layer_name, symbols);
            if (qwerty_layer==0) {
                // qp_rect(display, 0, 106, 240, 212, HSV_WHITE, true);
                qp_drawtext_recolor(display, 35, ypos, font, "  QWERTY  ", HSV_WHITE, HSV_BLACK);
            }
            if (mouse_layer==0) {
                // qp_rect(display, 0, 106, 240, 212, HSV_BLUE, true);
                qp_drawtext_recolor(display, 45, ypos, font, "  MOUSE  ", HSV_WHITE, HSV_BLACK);
            }
            if (nav_layer==0) {
                // qp_rect(display, 0, 106, 240, 212, HSV_CHARTREUSE, true);
                qp_drawtext_recolor(display, 75, ypos, font, "    NAV    ", HSV_WHITE, HSV_BLACK);
            }
            if (symbols_layer==0) {
                // qp_rect(display, 0, 106, 240, 212, HSV_PINK, true);
                qp_drawtext_recolor(display, 25, ypos, font, " SYMBOLS ", HSV_WHITE, HSV_BLACK);
            }
        }
        qp_flush(display);
    }

void housekeeping_task_user(void) {
    if (qp_lvgl_attach(display)) {
        draw_ui_user();
    }
}

#endif // QUANTUM_PAINTER_ENABLE


// this might be handy...
// KC_MCTL (pops mission control - the thing used to re-order 'spaces')

// KC_F on thumb and 5way rows == falcon button
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QWERTY] = LAYOUT(
    KC_TILD,LT(0,KC_1),LT(0,KC_2),LT(0,KC_3),LT(0,KC_4),LT(0,KC_5),     LT(0,KC_6),LT(0,KC_7),LT(0,KC_8),LT(0,KC_9),KC_0,KC_EQUAL,
    KC_TAB , KC_Q,LT(0,KC_W),HOME_E, LT(0,KC_R),LT(0,KC_T),             KC_Y,   KC_U,LT(0,KC_I), KC_O,   KC_P,   KC_MINUS,
    KC_LSFT, LT(0,KC_A),  HOME_S,  HOME_D,  HOME_F , KC_G,              KC_H,  HOME_J, HOME_K, HOME_L, KC_QUOT, KC_SCLN,
    DRAG_SCROLL,LT(0,KC_Z),LT(0,KC_X),LT(0,KC_C),LT(0,KC_V),LT(0,KC_B),    LT(0,KC_N), HOME_M, KC_COMM, KC_DOT, KC_SLASH, MEET_MUTE,
    KC_BSPC, MO(_NAV), KC_DEL, KC_ESC, OSM(MOD_LSFT), KC_1,             KC_MULTILNE, MO(_NAV), MO(_SYMBOLS), KC_ENTER, KC_SPACE, KC_LAYRST,
    KC_UP, KC_MULTILNE, OSM(MOD_LSFT), OSM(MOD_LSFT), KC_B, KC_2,       KC_N, KC_UP, KC_LEFT, KC_DOWN, KC_RIGHT, KC_MACSHOT
),
[_MOUSE] = LAYOUT(
    _______, _______, _______, _______, EE_CLR, QK_BOOT,               QK_BOOT, EE_CLR, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,               KC_CHRMBACK, KC_CHRMFWD, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,               KC_CHRMBACK, KC_MS_BTN1,KC_MS_BTN3,KC_MS_BTN2, _______, _______,
    _______, _______, _______, _______, _______, _______,               KC_CHRMFWD, KC_MS_BTN1,KC_MS_BTN3,KC_MS_BTN2, _______, MEET_VID,
    _______, _______, _______, _______, _______, _______,                 _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,                 _______, _______, _______, _______, _______, KC_MUTE
),
[_SYMBOLS] = LAYOUT(
    _______, _______, _______, _______, _______, _______,               KC_MACSHOT, MAGIPLAY, _______, _______, _______, _______,
    _______, KC_EXLM, KC_AT,   KC_LPRN, KC_RPRN, KC_AMPR,               KC_PPLS, KC_1,    KC_2,    KC_3,    KC_PMNS, KC_EQUAL,
    _______, KC_HASH, KC_DLR,  KC_LCBR, KC_RCBR, KC_GRV,                KC_PAST, KC_4,    KC_5,    KC_6,    KC_0,    KC_COMM,
    _______, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_PIPE,               KC_DOT,  KC_7,    KC_8,    KC_9,    KC_BSLS, _______,
    _______, _______, _______, _______, _______, _______,                 _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,                 _______, _______, _______, _______, _______, _______
),
[_NAV] = LAYOUT(
    _______, _______, _______, _______, _______, _______,               _______, _______, KC_SFTARROW_U, _______, _______, KC_F12,
    _______, _______, _______, LGUI(KC_TILD), _______, LT(0,KC_YAY),    KC_HOME, KC_ITRMSPCE_L, KC_UP, KC_ITRMSPCE_R, KC_END, _______,
    _______, KC_TAB_L, KC_TAB_R, KC_SPCLEFT, KC_SPCRGHT, _______,       KC_ALTARROW_L, KC_LEFT, KC_DOWN, KC_RIGHT, KC_ALTARROW_R, _______,
    _______, _______, _______, _______, _______, _______,               KC_SFTGUIARROW_L, KC_SFTALTARROW_L, KC_SFTARROW_D, KC_SFTALTARROW_R, KC_SFTGUIARROW_R, _______,
    _______, _______, _______ , KC_MACLOCK, _______,_______,            KC_TAB_R, KC_SPCRGHT, KC_TAB_L, KC_B, KC_SPCLEFT, KC_F,
    _______, _______, _______ , _______, _______, _______,                _______, _______, _______, _______, _______, MAGIPLAY
)
};

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
            // uprintf("Scrolling bool: %s \n", set_scrolling ? "true" : "false");
            return false;
        }
    #endif
    // now we check for specific keycodes...
    // note there is a macos bug that means any unicode ending in 0 doesn't register.
    #if defined(CUSTOM_KEYCODES)
        switch (keycode) {
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

#if defined(RGB_MATRIX_LEDMAPS_ENABLED)
// the indicator LEDs are mapped using the flags and for loop.
// Right thumb: KC_MULTILNE, OSM(MOD_LSFT), MO(_SYMBOLS), KC_ENTER, KC_SPACE, MAGIPLAY,
const ledmap ledmaps[] = {
    [_QWERTY]   = LEDMAP(
      CYAN, ___n___, ___n___, ___n___, ___n___, ___n___,            ___n___, ___n___, ___n___, ___n___, ___n___,    CYAN,
      GOLD, ___n___, ___n___, HRM_CTL, ___n___, ___n___,           ___n___, ___n___, ___n___, ___n___, ___n___,    CYAN,
     GREEN, ___n___, HRM_ALT, HRM_GUI, HRM_SFT, ___n___,           ___n___, HRM_SFT, HRM_GUI, HRM_ALT, ___n___, ___n___,
     ORANGE, ___n___, ___n___, ___n___, ___n___, ___n___,           ___n___, HRM_CTL, ___n___, ___n___, ___n___,     RED,
     DEL,     TOG_NAV, DEL,     ESC,     SHIFT, ___n___,            GREEN,   TOG_NAV,   TOG_SYM, ENTER,   SPACE, ___n___,
    ___n___, ___n___, ___n___, ___n___, ___n___, ___n___,          ___n___, ___n___, ___n___, ___n___, ___n___, ___n___
   ),
   [_MOUSE]     = LEDMAP(
      ___n___,   ___n___, ___n___, ___n___, YELLOW, RED,               RED,  YELLOW, ___n___, ___n___, ___n___, ___n___,
      GOLD, ___n___, ___n___, ___n___, ___n___, ___n___,               RED,   GREEN, ___n___, ___n___, ___n___, ___n___,
     GREEN, ___n___, ___n___, ___n___, ___n___, ___n___,               RED,    CYAN,    PINK,    CYAN, ___n___, ___n___,
     ORANGE, ___n___, ___n___, ___n___, ___n___, ___n___,         GREEN,    CYAN,    PINK,    CYAN, ___n___,     RED,
     DEL,     TOG_NAV, DEL,     ESC,     SHIFT, ___n___,           GREEN,   TOG_NAV,   TOG_SYM, ENTER,   SPACE, ___n___,
    ___n___, ___n___, ___n___, ___n___, ___n___, ___n___,          ___n___, ___n___, ___n___, ___n___, ___n___, ___n___
   ),
   [_SYMBOLS]   = LEDMAP(
      CYAN, ___n___, ___n___, ___n___, ___n___, ___n___,          ORANGE, MAGIPLY, ___n___, ___n___, ___n___, ___n___,
      GOLD,    GOLD,   GREEN,  PURPLE,  PURPLE,   GREEN,           GREEN,    CYAN,    CYAN,    CYAN, ___n___, ___n___,
     GREEN,    CYAN,  YELLOW,  MAGENT,  MAGENT,    BLUE,           GREEN,    CYAN,    CYAN,    CYAN,    CYAN, ___n___,
    ORANGE,    GOLD,   GREEN,   PINK,     PINK,    CYAN,             RED,    CYAN,    CYAN,    CYAN,    GOLD,     RED,
     DEL,     TOG_NAV, DEL,     ESC,     SHIFT, ___n___,           GREEN,   TOG_NAV,   TOG_SYM, ENTER,   SPACE, ___n___,
    ___n___, ___n___, ___n___, ___n___, ___n___, ___n___,          ___n___, ___n___, ___n___, ___n___, ___n___, ___n___
   ),
   [_NAV]       = LEDMAP(
      CYAN, ___n___, ___n___, ___n___, ___n___, ___n___,           ___n___, ___n___,  ORANGE, ___n___, ___n___,  YELLOW,
      GOLD, ___n___, ___n___,    CYAN, ___n___,  PURPLE,             GREEN,    CYAN,   GREEN,    CYAN,     RED, ___n___,
     GREEN,    BLUE,  SPRING,    PINK,    CYAN,   GREEN,            YELLOW,   GREEN,   GREEN,   GREEN,  YELLOW, ___n___,
     ORANGE, ___n___, ___n___, ___n___, ___n___,     RED,            PURPLE,  ORANGE,  ORANGE,  ORANGE,  PURPLE,  RED,
     DEL,     TOG_NAV, DEL,   YELLOW,     SHIFT, ___n___,            GREEN,   TOG_NAV,   TOG_SYM, ENTER,   SPACE, ___n___,
    ___n___, ___n___, ___n___, ___n___, ___n___, ___n___,          ___n___, ___n___, ___n___, ___n___, ___n___, ___n___
   ),
};
#endif // RGB_MATRIX_LEDMAPS_ENABLED
