#include "arcboard_mk19.h"
#include <qp.h>
#include QMK_KEYBOARD_H
#include "qp_st7789.h"
#include "print.h"

static painter_device_t display;

void keyboard_post_init_kb(void) {
    print("Display initializing.\n");
    setPinOutput(DISPLAY_LED_PIN);
    writePinLow(DISPLAY_LED_PIN);
    display = qp_st7789_make_spi_device(76, 284, DISPLAY_CS_PIN, DISPLAY_DC_PIN, DISPLAY_RST_PIN, DISPLAY_SPI_DIVISOR, DISPLAY_SPI_MODE);
    qp_init(display, QP_ROTATION_0);
    qp_rect(display, 10, 10, 50, 50, 255, 0, 255, true);
    
    keyboard_post_init_user();
}
