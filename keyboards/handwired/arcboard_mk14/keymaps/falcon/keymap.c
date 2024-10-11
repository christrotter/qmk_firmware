#include QMK_KEYBOARD_H
#include "arcboard_mk14.h"
#include "rgb_ledmaps.h"
#if defined(CONSOLE_ENABLED)
    #include "print.h"
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QWERTY] = LAYOUT( \
    KC_A, KC_1
),
[_UPPER] = LAYOUT( \
    KC_B, KC_2
),
[_UPPER2] = LAYOUT( \
    KC_C, KC_3
),
[_UPPER3] = LAYOUT( \
    KC_D, KC_4
),
};

// ledmaps for keys
const keysledmap keysledmaps[] = {
    [_QWERTY] = LEDMAP_KEYS(
    BLUE, BLUE, BLUE,           WHITE, WHITE, WHITE,        WHITE, WHITE, WHITE,      WHITE, WHITE, WHITE
    ),
    [_UPPER] = LEDMAP_KEYS(
    WHITE, WHITE, WHITE,        PURPLE, PURPLE, PURPLE,     WHITE, WHITE, WHITE,      WHITE, WHITE, WHITE
    ),
    [_UPPER2] = LEDMAP_KEYS(
    WHITE, WHITE, WHITE,        WHITE, WHITE, WHITE,        GREEN, GREEN, GREEN,      WHITE, WHITE, WHITE
    ),
    [_UPPER3] = LEDMAP_KEYS(
    WHITE, WHITE, WHITE,        WHITE, WHITE, WHITE,        WHITE, WHITE, WHITE,      RED, RED, RED
    ),
};

void set_rgb_range_keys(uint8_t led_start, uint8_t led_last, int layer) {
    uint8_t val = rgb_matrix_get_val();
    int i = 0;
    HSV hsv = {
        .h = (keysledmaps[layer])[i][0],
        .s = (keysledmaps[layer])[i][1],
        .v = val,
    };
    RGB rgb = hsv_to_rgb(hsv);
    for (int i = led_start; i <= led_last; i++) {
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (clockwise) {
        layer_on(get_highest_layer(layer_state) + 1);
    } else {
        layer_clear();
    }
    return false;
}


__attribute__((weak)) void keyboard_post_init_keymap(void) {}
void                       keyboard_post_init_user(void) {
    #ifdef CONSOLE_ENABLE
        debug_enable=true;
        debug_matrix=true;
        debug_keyboard=true;
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
