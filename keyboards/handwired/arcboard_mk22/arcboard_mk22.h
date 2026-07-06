#pragma once

#include "quantum.h"
#include "color.h"
#include QMK_KEYBOARD_H

// really want to have these in the keymap....
enum userspace_layers {
    _QWERTY             = 0,
    FIRST_DEFAULT_LAYER = 0
    // _MOUSE,
    // _SYMBOLS,
    // _NAV,
    // _RECT,
    // _VSCODE,
    // _FUSION,
    // _CHROME,
    // _KICAD,
    // _MGMT,
};

#if defined(RGB_MATRIX_LEDMAPS_ENABLED)
    #include "rgb_ledmaps.h"
#endif

#define _MACROS _MOUSE

// #define HSV_MOONLANDER 5, 5, KEYS_BRIGHTNESS
// Just a handy defines to make our ledmaps look better
// braces work here because
#define RED \
    { HSV_RED }
#define CORAL \
    { HSV_CORAL }
#define ORANGE \
    { HSV_ORANGE }
#define GOLDEN \
    { HSV_GOLDENROD }
#define GOLD \
    { HSV_GOLD }
#define YELLOW \
    { HSV_YELLOW }
#define CHART \
    { HSV_CHARTREUSE }
#define GREEN \
    { HSV_GREEN }
#define SPRING \
    { HSV_SPRINGGREEN }
#define TURQ \
    { HSV_TURQUOISE }
#define TEAL \
    { HSV_TEAL }
#define CYAN \
    { HSV_CYAN }
#define AZURE \
    { HSV_AZURE }
#define BLUE \
    { HSV_BLUE }
#define PURPLE \
    { HSV_PURPLE }
#define MAGENT \
    { HSV_MAGENTA }
#define PINK \
    { HSV_PINK }
#define BLACK \
    { HSV_BLACK }
#define BACKGROUND_SILVER 25, 25, KEYS_BRIGHTNESS
#define RING_ORANGE 15, 255, INDICATOR_BRIGHTNESS_RING

// indicator colours
#define INDICATOR_BG \
    HSV_CYAN
#define INDICATOR_SHIFT \
    HSV_GREEN

#if defined(POINTING_DEVICE_ENABLE)
    enum board_keycodes {
        DRAGSCROLL_MODE = 0xFFF0, // copilot suggests not reusing SAFE_RANGE, but rather something very high, so using 0xFFF0 arbitrarily
        DRAGSCROLL_MODE_TOGGLE,
    };
    #define DRGSCRL DRAGSCROLL_MODE
    #define DRG_TOG DRAGSCROLL_MODE_TOGGLE

    bool kb_get_pointer_dragscroll_enabled(void);
    void kb_set_pointer_dragscroll_enabled(bool enable);
#endif // POINTING_DEVICE_ENABLE

bool kb_get_super_alt_tab_state(void);
void kb_set_super_alt_tab_active(void);
void kb_set_super_alt_tab_off(void);

bool kb_get_alt_tab_state(void);
void kb_set_alt_tab_active(void);
void kb_set_alt_tab_off(void);

void keyboard_post_init_transport_sync(void);
void housekeeping_task_transport_sync(void);

void matrix_init_sub_kb(void);
void matrix_scan_sub_kb(void);
bool process_record_user_rgb_matrix(uint16_t keycode, keyrecord_t *record); //_user should not be in the keyboard.c

