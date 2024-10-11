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

#pragma once

#include "quantum.h"

#if defined(CONSOLE_ENABLE)
    #define DEBUG_MATRIX_SCAN_RATE
#endif

#if defined(POINTING_DEVICE_ENABLE) && defined(DRAGSCROLL_ENABLE)
    #define DRAG_TOG DRAG_SCROLL
    bool set_scrolling;
#else
    #define DRAG_TOG KC_NO
#endif

#define XXX KC_NO
#define __LED__ KC_NO

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
#define ZOOM_VID LSFT(LGUI(KC_DOT))

// single button to reset layer
#define KC_LAYER_RESET TO(_QWERTY)

enum custom_keycodes {
    KC_YAY = SAFE_RANGE,
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

// google docs zoom
#define GDOCZMIN LGUI(LALT(KC_PPLS))
#define GDOCZMOU LGUI(LALT(KC_PMNS))

#if defined(RGB_MATRIX_LEDMAPS_ENABLED)
    // constants across all layers, vs. setting key-led-slots individually
    // note: these cannot have braces e.g. #define HRM_SFT {GREEN} blows up the evaluation of the [3] part of the int[KEYS_COUNT][3]; sees it as one item
    #define ___n___ {0, 0, 0}
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
#endif

// encoder button mapping
    // left, flat
    #define FAL1_L0_BT KC_NO
    #define FAL1_L1_BT KC_NO
    #define FAL1_L2_BT KC_NO
    #define FAL1_L3_BT KC_NO
    // left, angled
    #define FAL2_L0_BT KC_NO
    #define FAL2_L1_BT KC_NO
    #define FAL2_L2_BT KC_NO
    #define FAL2_L3_BT KC_NO
    // right, angled - full-time layer selector
    #define FAL3_L0_BT KC_LAYER_RESET
    #define FAL3_L1_BT KC_LAYER_RESET
    #define FAL3_L2_BT KC_LAYER_RESET
    #define FAL3_L3_BT KC_LAYER_RESET
    // right, flat
    #define FAL4_L0_BT KC_MACSHOT
    #define FAL4_L1_BT KC_MUTE
    #define FAL4_L2_BT KC_NO
    #define FAL4_L3_BT MAGIPLY
