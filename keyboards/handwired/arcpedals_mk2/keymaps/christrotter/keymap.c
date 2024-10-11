// Copyright 2023 Chris Trotter (@christrotter)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include "arcpedals_mk2.h"
#include "keymap.h"

#if defined(RGB_MATRIX_LEDMAPS_ENABLED)
    #include "rgb_ledmaps.h"
#endif

#if defined(POINTING_DEVICE_ENABLE)
    #include "pointing.c"
#endif

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

enum keycodes {
  KC_CYCLE_LAYERS = QK_USER,
};
// 1st layer on the cycle
#define LAYER_CYCLE_START 0
// Last layer on the cycle
#define LAYER_CYCLE_END   3

__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) { return true; }
__attribute__((weak)) void post_process_record_keymap(uint16_t keycode, keyrecord_t *record) {}
void                       post_process_record_user(uint16_t keycode, keyrecord_t *record) { post_process_record_keymap(keycode, record); }

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_SCROLL] = LAYOUT(
    // physical layout is:
    //      (LEFT)                                                   (RIGHT)
    // left, toe, ball, right                              -    left, toe, ball, right
    KC_MS_BTN1, KC_MS_WH_DOWN, KC_CYCLE_LAYERS, KC_MS_WH_RIGHT,      KC_MS_WH_LEFT, KC_MS_WH_UP, KC_CYCLE_LAYERS, KC_MS_BTN3
),
[_MOUSE] = LAYOUT(
    KC_NO, KC_MS_BTN3, KC_CYCLE_LAYERS, KC_MS_BTN1,                            KC_NO, KC_MS_BTN1, KC_CYCLE_LAYERS, KC_MS_BTN2
),
[_FUSION] = LAYOUT(
    KC_NO, KC_LGUI, KC_CYCLE_LAYERS, KC_MS_WH_DOWN,              KC_MS_WH_UP, KC_MS_BTN3, KC_CYCLE_LAYERS, KC_NO
),
[_MGMT] = LAYOUT(
    KC_NO, EE_CLR, KC_CYCLE_LAYERS, KC_NO,                              KC_NO, QK_BOOT, KC_CYCLE_LAYERS, KC_NO
)
};

#if defined(RGB_MATRIX_LEDMAPS_ENABLED)
// the indicator LEDs are mapped using the flags and for loop.
const ledmap ledmaps[] = {
    [_SCROLL]   = LEDMAP(
      ORANGE, RED, CYAN, PINK, LAYER_SCROLL, LAYER_SCROLL, LAYER_SCROLL, LAYER_SCROLL,          PINK, GREEN, WHITE, SPRING, LAYER_SCROLL, LAYER_SCROLL, LAYER_SCROLL, LAYER_SCROLL
   ),
   [_MOUSE]     = LEDMAP(
      WHITE, WHITE, WHITE, PINK, LAYER_MOUSE, LAYER_MOUSE, LAYER_MOUSE, LAYER_MOUSE,            WHITE, PINK, WHITE, PURPLE, LAYER_MOUSE, LAYER_MOUSE, LAYER_MOUSE, LAYER_MOUSE
   ),
    [_FUSION]   = LEDMAP(
      RED, PURPLE, WHITE, WHITE, LAYER_FUSION, LAYER_FUSION, LAYER_FUSION, LAYER_FUSION,        PINK, PINK, WHITE, PURPLE, LAYER_FUSION, LAYER_FUSION, LAYER_FUSION, LAYER_FUSION
   ),
   [_MGMT]     = LEDMAP(
      WHITE, RED, RED, WHITE, LAYER_MGMT, LAYER_MGMT, LAYER_MGMT, LAYER_MGMT,                   WHITE, RED, RED, WHITE, LAYER_MGMT, LAYER_MGMT, LAYER_MGMT, LAYER_MGMT
   )
};
#endif // RGB_MATRIX_LEDMAPS_ENABLED


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

    // now we check for specific keycodes...
    #if defined(CUSTOM_KEYCODES)
        switch (keycode) {
            case KC_CYCLE_LAYERS:
              // Our logic will happen on presses, nothing is done on releases
              if (!record->event.pressed) {
                // We've already handled the keycode (doing nothing), let QMK know so no further code is run unnecessarily
                return false;
              }
              uint8_t current_layer = get_highest_layer(layer_state);
              // Check if we are within the range, if not quit
              if (current_layer > LAYER_CYCLE_END || current_layer < LAYER_CYCLE_START) {
                return false;
              }
              uint8_t next_layer = current_layer + 1;
              if (next_layer > LAYER_CYCLE_END) {
                  next_layer = LAYER_CYCLE_START;
              }
              layer_move(next_layer);
              return false;
    }
    #endif // end CUSTOM_KEYCODES (for troubleshooting)
    return true;
}
