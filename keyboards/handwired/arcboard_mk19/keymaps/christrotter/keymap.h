// Copyright 2023 Chris Trotter (@christrotter)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

#if defined(POINTING_DEVICE_ENABLE) && defined(DRAGSCROLL_ENABLE)
    bool set_scrolling;
#else
    #define DRAG_SCROLL KC_NO
#endif

#if defined(QUANTUM_PAINTER_ENABLE)
    // #include "lvgl.h"
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
#define KC_CHRMFWD  LGUI(KC_RBRC)

#define INPUT_CHG LCTL(LALT(LSFT(KC_V)))

// rectangle macros; for moving things around on the monitors
// #define REC_LEFT_HALF       LCTL(LALT(KC_LEFT))
// #define REC_RIGHT_HALF      LCTL(LALT(KC_RIGHT))
#define REC_MAXIMIZE        LCTL(LALT(KC_ENTER))
#define REC_MINIMIZE        LGUI(KC_M)
#define REC_33_LEFT         LCTL(LALT(KC_D))
#define REC_50_LEFT         LCTL(LALT(KC_LEFT))
#define REC_66_LEFT         LCTL(LALT(KC_E))
#define REC_33_RIGHT        LCTL(LALT(KC_G))
#define REC_50_RIGHT        LCTL(LALT(KC_RIGHT))
#define REC_66_RIGHT        LCTL(LALT(KC_T))

// rectangle quadrants
#define REC_TOP_RIGHT        LCTL(LALT(KC_W))
#define REC_BOT_RIGHT        LCTL(LALT(KC_W))
#define REC_TOP_LEFT        LCTL(LALT(KC_W))
#define REC_BOT_LEFT        LCTL(LALT(KC_W))

// rectangle sixths
#define REC_6TH_TL        LGUI(LALT(LSFT(KC_1)))
#define REC_6TH_TM        LGUI(LALT(LSFT(KC_2)))
#define REC_6TH_TR        LGUI(LALT(LSFT(KC_3)))
#define REC_6TH_BL        LGUI(LALT(LSFT(KC_4)))
#define REC_6TH_BM        LGUI(LALT(LSFT(KC_5)))
#define REC_6TH_BR        LGUI(LALT(LSFT(KC_6)))

// #define REC_LEFT_HALF       LCTL(LALT(KC_LEFT))
// #define REC_PREV_MONITOR    LCTL(LALT(LGUI(KC_LEFT)))
// #define REC_NEXT_MONITOR    LCTL(LALT(LGUI(KC_RIGHT)))

// we want to handle word movement (nav) and word select (symbols) on the arrow cluster
// KC_LEFT, KC_UP, KC_DOWN, KC_RIGHT
#define KC_SFTGUIARROW_L    LGUI(LSFT(KC_LEFT))
#define KC_SFTGUIARROW_R    LGUI(LSFT(KC_RIGHT))
#define KC_ALTARROW_L       LALT(KC_LEFT)
#define KC_ALTARROW_R       LALT(KC_RIGHT)
#define KC_SFTALTARROW_L    LALT(LSFT(KC_LEFT))
#define KC_SFTALTARROW_R    LALT(LSFT(KC_RIGHT))
#define KC_SFTARROW_U       LSFT(KC_UP)
#define KC_SFTARROW_D       LSFT(KC_DOWN)

#define ZOOM_IN LGUI(KC_PLUS)
#define ZOOM_OUT LGUI(KC_MINUS)

#define SHEET_LEFT LALT(KC_UP)
#define SHEET_RIGHT LALT(KC_DOWN)

#define ZOOM_MUTE   LSFT(LGUI(KC_COMM))
#define ZOOM_VID    LSFT(LGUI(KC_DOT))

#define MEET_HAND   LGUI(LCTL(KC_H))
#define MEET_MUTE   LGUI(KC_D)
#define MEET_VID    LGUI(KC_E)

// single button to reset layer
#define KC_LAYRST TO(_QWERTY)

enum custom_keycodes {
    KC_YAY = SAFE_RANGE,
    DRAG_SCROLL,
    ALT_TAB,
    SFT_ALT_TAB,
    SUP_ALT_TAB,
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

#if defined(RGB_MATRIX_LEDMAPS_ENABLED)
    // where...the _L# = layer numbers
    // and...
    // FAL1 = left2 (flat)
    // FAL2 = left1 (angled)
    // FAL3 = right1(angled)
    // FAL4 = right2(flat)

    // left, flat
    #define FAL1_IN_L0 HSV_CYAN
    #define FAL1_OUT_L0 HSV_BLUE
    #define FAL1_IN_L1 HSV_RED
    #define FAL1_OUT_L1 HSV_ORANGE
    #define FAL1_IN_L2 HSV_CORAL
    #define FAL1_OUT_L2 HSV_GREEN
    #define FAL1_IN_L3 HSV_MOONLANDER
    #define FAL1_OUT_L3 HSV_MOONLANDER
    // left, angled
    #define FAL2_IN_L0 HSV_GOLDENROD
    #define FAL2_OUT_L0 HSV_GOLD
    #define FAL2_IN_L1 HSV_YELLOW
    #define FAL2_OUT_L1 HSV_GREEN
    #define FAL2_IN_L2 HSV_BLUE
    #define FAL2_OUT_L2 HSV_SPRINGGREEN
    #define FAL2_IN_L3 HSV_MOONLANDER
    #define FAL2_OUT_L3 HSV_BLUE
    // right, angled
    #define FAL3_IN_L0 HSV_CYAN
    #define FAL3_OUT_L0 HSV_SPRINGGREEN
    #define FAL3_IN_L1 HSV_SPRINGGREEN
    #define FAL3_OUT_L1 HSV_CYAN
    #define FAL3_IN_L2 HSV_MOONLANDER
    #define FAL3_OUT_L2 HSV_MOONLANDER
    #define FAL3_IN_L3 HSV_SPRINGGREEN
    #define FAL3_OUT_L3 HSV_GREEN
    // right, flat
    #define FAL4_IN_L0 HSV_CYAN
    #define FAL4_OUT_L0 HSV_BLUE
    #define FAL4_IN_L1 HSV_BLUE
    #define FAL4_OUT_L1 HSV_PURPLE
    #define FAL4_IN_L2 HSV_MOONLANDER
    #define FAL4_OUT_L2 HSV_MOONLANDER
    #define FAL4_IN_L3 HSV_SPRINGGREEN
    #define FAL4_OUT_L3 HSV_GREEN
#endif

// encoder button mapping // uhhh why do we have this again...
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
