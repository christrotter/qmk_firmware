// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "arcpedals_mk3.h"
#include "keymap.h"
#include "raw_hid.h"

// 1st layer on the cycle
#define LAYER_CYCLE_START 0
// Last layer on the cycle
#define LAYER_CYCLE_END   2

#if defined(RGB_MATRIX_LEDMAPS_ENABLED)
    #include "rgb_ledmaps.h"
#endif

__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) { return true; }
__attribute__((weak)) void post_process_record_keymap(uint16_t keycode, keyrecord_t *record) {}
void                       post_process_record_user(uint16_t keycode, keyrecord_t *record) { post_process_record_keymap(keycode, record); }

void toggle_keyboard_dragscroll(void) {
  uint8_t data[32];
  memset(data, 0, 32);
  data[0] = _RELAY_FROM_DEVICE;
  data[1] = _TOGGLE_DRAGSCROLL;
  printf("Raw-hid: Send data: %u %u %u\n", data[0], data[1], data[2]);
  raw_hid_send(data, 32);
}

void toggle_keyboard_oneshot_gui(void) {
  uint8_t data[32];
  memset(data, 0, 32);
  data[0] = _RELAY_FROM_DEVICE;
  data[1] = _TOGGLE_ONESHOT_GUI;
  printf("Raw-hid: Send data: %u %u %u\n", data[0], data[1], data[2]);
  raw_hid_send(data, 32);
}

void toggle_keyboard_rect(void) {
  uint8_t data[32];
  memset(data, 0, 32);
  data[0] = _RELAY_FROM_DEVICE;
  data[1] = _TOGGLE_KB_RECT;
  printf("Raw-hid: Send data: %u %u %u\n", data[0], data[1], data[2]);
  raw_hid_send(data, 32);
}

void send_layer_colour(uint8_t layer_colour) {
  uint8_t data[32];
  memset(data, 0, 32);
  // data[0] = _DIRECT_TO_HOST;
  data[0] = _RELAY_FROM_DEVICE;
  data[1] = _DIRECT_TO_HOST;
  data[2] = layer_colour;
  xprintf("Raw-hid: Send layer colour: %u %u %u\n", data[0], data[1], data[2]);
  raw_hid_send(data, 32);
}

#if defined(CONSOLE_ENABLE)
    #include "print.h"
    void keyboard_post_init_user(void) {
        // if (is_keyboard_left()) {
        //     print("I AM THE LEFT SIDE.");
        // } else {
        //     print("I AM THE RIGHT SIDE.");
        // }
        // Customise these values to desired behaviour
        debug_enable=true;
        // debug_matrix=true;
        // debug_keyboard=true;
        // debug_mouse=true;
        // eeconfig_init();
        
        // now, we want to reset the led indicator on the monitor to the correct layer
        // have to put a wait in as other stuff is starting up in the background
        wait_ms(2000);
        send_layer_colour(1);
    }
#endif



/*
    Physical layout:
               #### LEFT FOOT ####            ###               #### RIGHT FOOT ####
    botL, botR, topL, topR,         desk1     ###      botL, botR, topL, topR,         desk1
    sideL, sideR, heelL, heelR,     desk2     ###      sideL, sideR, heelL, heelR,     desk2

    should lay this out nicer...
*/

// MS_WH_ things are inverted for reasons i did not dig into
// top toe are in order on both sides for reasons i did not dig into
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_SCROLL] = LAYOUT(
        KC_MS_WH_DOWN, KC_MS_WH_DOWN, KC_KB_ONESHOT_GUI, KC_KB_ONESHOT_GUI,      _______,    KC_MS_WH_UP, KC_MS_WH_UP, KC_KB_ONESHOT_GUI, KC_KB_ONESHOT_GUI,          _______,
        KC_KB_DRAGSCROLL, KC_KB_RECT, KC_CYCLE_LAYERS, KC_CYCLE_LAYERS,          _______,    KC_KB_DRAGSCROLL, KC_KB_RECT, KC_CYCLE_LAYERS, KC_CYCLE_LAYERS,    _______
    ),
    [_FUSION] = LAYOUT(
        _______, KC_LGUI, _______, _______,                                 _______,    KC_MS_BTN3, _______, _______, _______,                              _______,
        KC_MS_WH_RIGHT, KC_MS_WH_LEFT, KC_CYCLE_LAYERS, KC_CYCLE_LAYERS,    _______,    KC_MS_WH_UP, KC_MS_WH_DOWN, KC_CYCLE_LAYERS, KC_CYCLE_LAYERS,       _______
    ),
    [_MGMT] = LAYOUT(
        _______, _______, QK_BOOT, EE_CLR,                                  _______,    _______, _______, EE_CLR, QK_BOOT,                                  _______,
        _______, _______, KC_CYCLE_LAYERS, KC_CYCLE_LAYERS,                 _______,    _______, _______, KC_CYCLE_LAYERS, KC_CYCLE_LAYERS,                 _______
    )
};

#if defined(RGB_MATRIX_LEDMAPS_ENABLED)
// the indicator LEDs are mapped using the flags and for loop.
/*
    Physical layout:
               #### LEFT FOOT ####            ###               #### RIGHT FOOT ####
    botL(1), botR(2), topL(3), topR(4),         desk1     ###      botL, botR, topL, topR,         desk1
    sideL(5), sideR(6), heelL(7), heelR(8),     desk2     ###      sideL, sideR, heelL, heelR,     desk2

    should lay this out nicer...
*/

// these need to match the wiring flippage;
const ledmap ledmaps[] = {
    [_SCROLL]   = LEDMAP(
      L_B1_L0,L_B1_L0,L_B1_L0,L_B2_L0,L_B2_L0,L_B2_L0,L_B3_L0,L_B3_L0,L_B3_L0,L_B4_L0,L_B4_L0,L_B4_L0,L_B5_L0,L_B5_L0,L_B5_L0,L_B6_L0,L_B6_L0,L_B6_L0,L_B7_L0,L_B7_L0,L_B7_L0,L_B8_L0,L_B8_L0,L_B8_L0, \
      R_B1_L0,R_B1_L0,R_B1_L0,R_B2_L0,R_B2_L0,R_B2_L0,R_B3_L0,R_B3_L0,R_B3_L0,R_B4_L0,R_B4_L0,R_B4_L0,R_B5_L0,R_B5_L0,R_B5_L0,R_B6_L0,R_B6_L0,R_B6_L0,R_B7_L0,R_B7_L0,R_B7_L0,R_B8_L0,R_B8_L0,R_B8_L0
    ),
    [_FUSION]   = LEDMAP(
      L_B1_L2,L_B1_L2,L_B1_L2,L_B2_L2,L_B2_L2,L_B2_L2,L_B3_L2,L_B3_L2,L_B3_L2,L_B4_L2,L_B4_L2,L_B4_L2,L_B5_L2,L_B5_L2,L_B5_L2,L_B6_L2,L_B6_L2,L_B6_L2,L_B7_L2,L_B7_L2,L_B7_L2,L_B8_L2,L_B8_L2,L_B8_L2, \
      R_B1_L2,R_B1_L2,R_B1_L2,R_B2_L2,R_B2_L2,R_B2_L2,R_B3_L2,R_B3_L2,R_B3_L2,R_B4_L2,R_B4_L2,R_B4_L2,R_B5_L2,R_B5_L2,R_B5_L2,R_B6_L2,R_B6_L2,R_B6_L2,R_B7_L2,R_B7_L2,R_B7_L2,R_B8_L2,R_B8_L2,R_B8_L2
    ),
    [_MGMT]     = LEDMAP(
      L_B1_L3,L_B1_L3,L_B1_L3,L_B2_L3,L_B2_L3,L_B2_L3,L_B3_L3,L_B3_L3,L_B3_L3,L_B4_L3,L_B4_L3,L_B4_L3,L_B5_L3,L_B5_L3,L_B5_L3,L_B6_L3,L_B6_L3,L_B6_L3,L_B7_L3,L_B7_L3,L_B7_L3,L_B8_L3,L_B8_L3,L_B8_L3, \
      R_B1_L3,R_B1_L3,R_B1_L3,R_B2_L3,R_B2_L3,R_B2_L3,R_B3_L3,R_B3_L3,R_B3_L3,R_B4_L3,R_B4_L3,R_B4_L3,R_B5_L3,R_B5_L3,R_B5_L3,R_B6_L3,R_B6_L3,R_B6_L3,R_B7_L3,R_B7_L3,R_B7_L3,R_B8_L3,R_B8_L3,R_B8_L3
    )
};
#endif // RGB_MATRIX_LEDMAPS_ENABLED

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!(process_record_keymap(keycode, record)
        #if defined(RGB_MATRIX_LEDMAPS_ENABLED)
            && process_record_user_rgb_matrix(keycode, record)
        #endif
        )) {
        return false;
    }

    // now we check for specific keycodes...
    #if defined(CUSTOM_KEYCODES)
      switch (keycode) {
        case KC_KB_DRAGSCROLL:
          if (record->event.pressed) {
              toggle_keyboard_dragscroll();
              return false;
          }
          return true;
        case KC_KB_ONESHOT_GUI:
          if (record->event.pressed) {
              toggle_keyboard_oneshot_gui();
              return false;
          }
          return true;
        case KC_KB_RECT:
          if (record->event.pressed) {
              toggle_keyboard_rect();
              return false;
          }
          return true;
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

// now, on layer change, we want to emit the layer number to the app, as a guarantee that the led colour will be correct.
layer_state_t layer_state_set_user(layer_state_t state) {
  // this could potentially be improved by changing to send_layer_colour(get_highest_layer(state));
  switch (get_highest_layer(state)) {
  case 0:
      send_layer_colour(1);
      break;
  case 1:
      send_layer_colour(3);
      break;
  case 2:
      send_layer_colour(4);
      break;
  }
return state;
}
