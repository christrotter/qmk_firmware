#include QMK_KEYBOARD_H
#include "arcboard_mk14.h"
#if defined(CONSOLE_ENABLED)
    #include "print.h"
#endif


// button press = last in row
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QWERTY] = LAYOUT( \
    KC_LEFT, KC_UP, KC_RIGHT, KC_DOWN, KC_ENTER
)
};

__attribute__((weak)) void keyboard_post_init_keymap(void) {}
void                       keyboard_post_init_user(void) {
    #ifdef CONSOLE_ENABLE
        debug_enable=true;
        //debug_matrix=true;
        //debug_keyboard=true;
        debug_mouse=true;
        #ifdef POINTING_DEBUG_ENABLE
            debug_mouse=true;
        #endif
    #endif
    keyboard_post_init_keymap();
}

__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) { return true; }

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!(process_record_keymap(keycode, record)
        #if defined(RGB_MATRIX_LEDMAPS_ENABLED)
            && process_record_user_rgb_matrix(keycode, record)
        #endif
          && true)) {
        return false;
    }
    return true;
}

__attribute__((weak)) void post_process_record_keymap(uint16_t keycode, keyrecord_t *record) {}
void                       post_process_record_user(uint16_t keycode, keyrecord_t *record) { post_process_record_keymap(keycode, record); }
