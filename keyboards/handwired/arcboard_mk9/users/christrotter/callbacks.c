// Copyright 2021 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "christrotter.h"
#ifdef CONSOLE_ENABLE
    #include "print.h"
    #include "stdio.h"
#endif

__attribute__((weak)) void keyboard_pre_init_keymap(void) {}
void                       keyboard_pre_init_user(void) {
    userspace_config.raw = eeconfig_read_user();
    keyboard_pre_init_keymap();
}
/*
    Add reconfigurable functions here, for keymap customization.
    This allows for a global, userspace functions, and continued
    customization of the keymap.
    - Use _keymap instead of _user functions in the keymaps
    - Call user matrix init, set default RGB colors, and then call the keymap's init function
*/
__attribute__((weak)) void matrix_init_keymap(void) {}
void                       matrix_init_user(void) {

    matrix_init_keymap();

}

__attribute__((weak)) void keyboard_post_init_keymap(void) {}
void                       keyboard_post_init_user(void) {
#if defined(CUSTOM_RGB_MATRIX)
    keyboard_post_init_rgb_matrix();
#endif
#if defined(SPLIT_KEYBOARD) && defined(SPLIT_TRANSACTION_IDS_USER)
    keyboard_post_init_transport_sync();
#endif

    keyboard_post_init_keymap();

} // end keyboard_post_init_user

#ifdef RGB_MATRIX_ENABLE
void rgb_matrix_update_pwm_buffers(void);
#endif

// No global matrix scan code, so just run keymap's matrix
// scan function
__attribute__((weak)) void matrix_scan_keymap(void) {}
void                       matrix_scan_user(void) {
    static bool has_ran_yet;
    if (!has_ran_yet) {
        has_ran_yet = true;
        startup_user();
    }
#if defined(CUSTOM_RGB_MATRIX)
    // if we have custom rgb matrix, call this function during the matrix scan
    // don't forget we also have to run this on the slave sync
    matrix_scan_rgb_matrix();
#endif
    #ifdef CONSOLE_ENABLE
        debug_enable=true;
        //dprint("spam the console on every keypress with this, and be sure to end with... \n");
    #endif

    matrix_scan_keymap();

} // end matrix_scan_user

// on layer change, no matter where the change was initiated
// Then runs keymap's layer change check
// I think this is how it does the automagic mouse layer switching?
__attribute__((weak)) layer_state_t layer_state_set_keymap(layer_state_t state) { return state; }
layer_state_t                       layer_state_set_user(layer_state_t state) {
    if (!is_keyboard_master()) {
        return state;
    }

#if defined(CUSTOM_POINTING_DEVICE)
    state = layer_state_set_pointing(state);
#endif

    state = layer_state_set_keymap(state);
    return state;

} // end layer_state_t - layer_state_set_user

// Runs state check and changes underglow color and animation
__attribute__((weak)) layer_state_t default_layer_state_set_keymap(layer_state_t state) { return state; }
layer_state_t                       default_layer_state_set_user(layer_state_t state) {
    if (!is_keyboard_master()) {
        return state;
    }

    state = default_layer_state_set_keymap(state);

    return state;
} // end layer_state_t - default_layer_state_set_user

// not sure what this does...
//__attribute__((weak)) void led_set_keymap(uint8_t usb_led) {}
//void                       led_set_user(uint8_t usb_led) { led_set_keymap(usb_led); }

// this does something w. eeprom??
__attribute__((weak)) void eeconfig_init_keymap(void) {}
void                       eeconfig_init_user(void) {
    userspace_config.raw              = 0;
    userspace_config.rgb_layer_change = true;
    eeconfig_update_user(userspace_config.raw);
    eeconfig_init_keymap();
} // end eeconfig_init_user

// This section defines what happens on the slave side re: custom code!!!
#ifdef SPLIT_KEYBOARD
__attribute__((weak)) void matrix_slave_scan_keymap(void) {}
void                       matrix_slave_scan_user(void) {
    // if we have custom rgb matrix, call this function during the matrix scan
#    ifdef RGB_MATRIX_ENABLE
    matrix_scan_rgb_matrix();
#    endif

    matrix_slave_scan_keymap();

} // end matrix_slave_scan_user
#endif
