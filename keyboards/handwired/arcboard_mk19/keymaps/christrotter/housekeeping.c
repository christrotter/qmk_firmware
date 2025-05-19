// #include "ui.c"
#include "pointing.c"
#include "transactions.h"

void housekeeping_task_user(void) {
    static uint32_t last_draw = 0;
    lcd_power = (last_input_activity_elapsed() < SCREEN_TIMEOUT) ? 1 : 0;

    setPinOutput(DISPLAY_LED_PIN);
    if (lcd_power) {
        writePinHigh(DISPLAY_LED_PIN);
        if (timer_elapsed32(last_draw) > 33) { // Throttle to 30fps
            last_draw = timer_read32();
            // update_layer_display();
            // draw_ui_user();
        }
    } else {
        writePinLow(DISPLAY_LED_PIN);
    }
}