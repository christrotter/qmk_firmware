#include QMK_KEYBOARD_H
#include "arcboard_mk14.h"
#if defined(CONSOLE_ENABLED)
    #include "print.h"
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QWERTY] = LAYOUT( \
    OSM(MOD_LSFT), KC_1, MO(_UPPER), KC_NO, KC_NO, KC_NO, KC_NO
),
[_UPPER] = LAYOUT( \
    OSM(MOD_LSFT), KC_1, MO(_UPPER), KC_NO, KC_NO, KC_NO, KC_NO
),
};

// pimoroni defines
uint8_t white = 200;
uint8_t red = 0;
uint8_t green = 0;
uint8_t blue = 0;


bool set_scrolling = false;
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (set_scrolling) {
        mouse_report.h = mouse_report.x;
        mouse_report.v = mouse_report.y;
        mouse_report.x = mouse_report.y = 0;
    }
    return mouse_report;
}

__attribute__((weak)) void keyboard_post_init_keymap(void) {}
void                       keyboard_post_init_user(void) {
    //pimoroni_trackball_set_cpi(100);
    //pimoroni_trackball_set_rgbw(red,green,blue,white);
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
