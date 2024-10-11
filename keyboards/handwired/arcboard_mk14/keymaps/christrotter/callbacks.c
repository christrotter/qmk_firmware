// Copyright 2021 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "callbacks.h"

/*
    Add reconfigurable functions here, for keymap customization.
    This allows for a global, userspace functions, and continued
    customization of the keymap.
    - Use _keymap instead of _user functions in the keymaps
    - Call user matrix init, set default RGB colors, and then call the keymap's init function
*/
__attribute__((weak)) void matrix_init_keymap(void) {}
void matrix_init_user(void) {
    matrix_init_keymap();
}


// No global matrix scan code, so just run keymap's matrix scan function
__attribute__((weak)) void matrix_scan_keymap(void) {}
void                       matrix_scan_user(void) {
    matrix_scan_keymap();
}

// This section defines what happens on the slave side re: custom code!!!
#ifdef SPLIT_KEYBOARD
__attribute__((weak)) void matrix_slave_scan_keymap(void) {}
void                       matrix_slave_scan_user(void) {
    matrix_slave_scan_keymap();
}
#endif
