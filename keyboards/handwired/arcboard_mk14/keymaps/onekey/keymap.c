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

// ledmaps for keys
const keysledmap keysledmaps[] = {
    [_QWERTY] = LEDMAP_KEYS(
    YELLOW, YELLOW, YELLOW
    ),
    [_UPPER] = LEDMAP_KEYS(
    PINK, PINK, PINK
    ),
};
// ledmaps for indicators
const ind1ledmap ind1ledmaps[] = {
    [0] = LEDMAP_IND1(
    BLACK, BLACK
    ),
    [1]  = LEDMAP_IND1(
    GREEN, GREEN
    ),
};
const ind2ledmap ind2ledmaps[] = {
    [0] = LEDMAP_IND2(
    BLACK, BLACK
    ),
    [1]  = LEDMAP_IND2(
    PURPLE, PURPLE
    ),
};

// the non-DRY-ness of these functions is unfortunate, but I could not figure out how to pass in the ledmap as an argument
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
void set_rgb_range_ind1(uint8_t led_start, uint8_t led_last, int layer) {
    uint8_t val = rgb_matrix_get_val();
    int i = 0;
    HSV hsv = {
        .h = (ind1ledmaps[layer])[i][0],
        .s = (ind1ledmaps[layer])[i][1],
        .v = val,
    };
    RGB rgb = hsv_to_rgb(hsv); // something in here was blowing up the i count
    for (int i = led_start; i <= led_last; i++) {
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }
}
void set_rgb_range_ind2(uint8_t led_start, uint8_t led_last, int layer) {
    uint8_t val = rgb_matrix_get_val();
    int i = 0;
    HSV hsv = {
        .h = (ind2ledmaps[layer])[i][0],
        .s = (ind2ledmaps[layer])[i][1],
        .v = val,
    };
    RGB rgb = hsv_to_rgb(hsv); // something in here was blowing up the i count
    for (int i = led_start; i <= led_last; i++) {
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    set_rgb_range_keys(KEYS_LED_MIN, KEYS_LED_MAX, get_highest_layer(layer_state | default_layer_state));

    bool is_shifted = (get_mods() | get_weak_mods()) & MOD_MASK_SHIFT;
    if (is_shifted) {
        set_rgb_range_ind1(IND1_LED_MIN, IND1_LED_MAX, 1);
    } else {
        set_rgb_range_ind1(IND1_LED_MIN, IND1_LED_MAX, 0);
    }
    bool is_oneshot = (get_oneshot_mods() | get_mods()) & MOD_MASK_SHIFT;
    if (is_oneshot) {
        set_rgb_range_ind2(IND2_LED_MIN, IND2_LED_MAX, 1);
    } else {
        set_rgb_range_ind2(IND2_LED_MIN, IND2_LED_MAX, 0);
    }
    return false;
}

__attribute__((weak)) void keyboard_post_init_keymap(void) {}
void                       keyboard_post_init_user(void) {
    #ifdef CONSOLE_ENABLE
        debug_enable=true;
        //debug_matrix=true;
        //debug_keyboard=true;
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
