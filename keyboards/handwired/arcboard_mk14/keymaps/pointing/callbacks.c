#include "callbacks.h"

__attribute__((weak)) void matrix_init_keymap(void) {}
void matrix_init_user(void) {
    matrix_init_keymap();
}

// No global matrix scan code, so just run keymap's matrix scan function
__attribute__((weak)) void matrix_scan_keymap(void) {}
void                       matrix_scan_user(void) {
    matrix_scan_keymap();
}
