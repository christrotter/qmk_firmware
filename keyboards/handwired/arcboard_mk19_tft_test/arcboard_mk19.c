#include "arcboard_mk19.h"
#include <qp.h>
#include "qp_st7789.h"

void keyboard_post_init_kb(void) {
    display = painter_device_t qp_st7789_make_spi_device(76, 284, DISPLAY_CS_PIN, DISPLAY_DC_PIN, DISPLAY_RST_PIN, DISPLAY_SPI_DIVISOR, DISPLAY_SPI_MODE);
    qp_init(display, QP_ROTATION_0);

    // setPinOutput(DISPLAY_BL_PIN);
    // writePinHigh(DISPLAY_BL_PIN);

    qp_rect(display, 0, 0, 75, 283, 255, 0, 255, true);

    keyboard_post_init_user();
}
