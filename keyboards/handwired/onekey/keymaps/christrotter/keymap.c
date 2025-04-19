// Copyright 2023 Chris Trotter (@christrotter)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include "keymap.h"
#include "raw_hid.h"
#include "onekey.h"
#include "print.h"


#if defined(CONSOLE_ENABLE)
    #include "print.h"
    void keyboard_post_init_user(void) {
        // Customise these values to desired behaviour
        debug_enable=true;
        // debug_matrix=true;
        debug_keyboard=true;
        // debug_mouse=true;
    }
#endif


enum keycodes {
  KC_TEST = QK_USER,
};

typedef enum {
    _LAYER = 0,
} relay_data_type;

__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) { return true; }
__attribute__((weak)) void post_process_record_keymap(uint16_t keycode, keyrecord_t *record) {}
void                       post_process_record_user(uint16_t keycode, keyrecord_t *record) { post_process_record_keymap(keycode, record); }

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_DEFAULT] = LAYOUT(
    KC_TEST
)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!(process_record_keymap(keycode, record)
          && true)) {
        return false;
    }

    // now we check for specific keycodes...
    #if defined(CUSTOM_KEYCODES)
        switch (keycode) {
            case KC_TEST:
                if (record->event.pressed) {
                    dprintf("KC_TEST pressed\n");
                    uint8_t data[32];
                    memset(data, 0, 32);
                    data[0] = _RELAY_FROM_DEVICE;
                    data[1] = _LAYER;
                    data[2] = get_highest_layer(state);
                    printf("Sending data...\n");
                    dprintf("Sending data...\n");
                    raw_hid_send(data, 32);
                    return false;
                }
            return true;
    }
    #endif // end CUSTOM_KEYCODES (for troubleshooting)
    return true;
}

void raw_hid_receive_kb(uint8_t *data, uint8_t length) {
    printf("usb-hid data incoming...\n");
    dprintf("Receive data: %u %u %u \n", data[0], data[1], data[2]);
}
