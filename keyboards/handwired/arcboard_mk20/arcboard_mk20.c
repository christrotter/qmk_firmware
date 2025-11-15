#include "quantum.h"

void keyboard_post_init_kb(void) {
    // turn on the backlight
    setPinOutput(DISPLAY_BL_PIN);
    writePinLow(DISPLAY_BL_PIN);
    keyboard_post_init_user();
}
