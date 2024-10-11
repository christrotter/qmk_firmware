// Copyright 2018-2022 Nick Brassel (@tzarc)
// Copyright 2020-2023 alin m elena (@alinelena, @drFaustroll)
// Copyright 2023 Stefan Kerkmann (@karlk90)
// Copyright 2023 (@burkfers)
// SPDX-License-Identifier: GPL-3.0-or-later

#include "quantum.h"
#include "spi_master.h"
#if defined(CONSOLE_ENABLE)
    #include "print.h"
#endif
// todo remove rows_count here, too
static const uint16_t row_values[ROWS_COUNT] = ROWS;
static const pin_t latch_pin = SPI_MATRIX_LATCH_PIN;

void matrix_init_custom(void) {
    setPinOutput(SPI_MATRIX_CHIP_SELECT_PIN_COLS);
    writePinHigh(SPI_MATRIX_CHIP_SELECT_PIN_COLS);
    setPinOutput(SPI_MATRIX_CHIP_SELECT_PIN_ROWS);
    writePinHigh(SPI_MATRIX_CHIP_SELECT_PIN_ROWS);
    setPinOutput(latch_pin);
    writePinLow(latch_pin);
    if (!(is_keyboard_left())) {
        setPinOutput(PMW33XX_CS_PIN);
        writePinHigh(PMW33XX_CS_PIN);
    }
    spi_init();
}

static inline void write_to_rows(uint16_t value) {
    uint8_t message[2] = {(uint8_t)(value & 0xFF), (value >> 8) & 0xFF}; // cut 0xABCD into {0xAB, 0xCD}
    spi_start(SPI_MATRIX_CHIP_SELECT_PIN_ROWS, true, SPI_MODE, SPI_MATRIX_DIVISOR);
    // printf("set row to: %u | %u \n", message[0], message[1]);
    spi_transmit(message, 2);
    spi_stop();
}

// /**
//  * @brief Helper function to wait until a pin  has reached the wanted target
//  * state. This only works for Push-Pull pins with enabled input stage.
//  */
static void __time_critical_func(write_and_wait_for_pin)(pin_t pin, uint8_t target_state) {
    writePin(pin, target_state);
    rtcnt_t start = chSysGetRealtimeCounterX();
    rtcnt_t end   = start + MS2RTC(REALTIME_COUNTER_CLOCK, 20);
    while (chSysIsCounterWithinX(chSysGetRealtimeCounterX(), start, end)) {
        if (readPin(pin) == target_state) {
            return;
        }
    }
}

/*
    what are we trying to accomplish in the scan?
    for each row:
    - set row high
    - check all cols
    - build the matrix object's "this row" entry

    compare the matrix object to the last one

    in order to check the cols, we need to get the 589 registers to transfer data from latch into register
    - set row high i.e. this sets up our environment state
    - set latch high; shift registers now transfer their data from latch to register
    - set latch low; shift registers now ready to transfer data out serial line
    - spi_start on the columns CS pin; spi_receive; spi_stop on cols CS pin
    done.

*/

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    // TODO replace ROWS_COUNT with a sizeof or array_size or something
    static matrix_row_t temp_matrix[ROWS_COUNT] = {0};
    
    for (uint8_t row = 0; row < (ROWS_COUNT); row++) {
        uint8_t temp_col_receive[MATRIX_COLS_SHIFT_REGISTER_COUNT] = {0};
        uint16_t temp_col_state;

        // set_row_high(row);
        write_to_rows(row_values[row]);

        // get the shift registers to move data from latch to register
        write_and_wait_for_pin(latch_pin, 1);
        write_and_wait_for_pin(latch_pin, 0);

        // read the cols shift register contents over serial
        // spi_start(SPI_MATRIX_CHIP_SELECT_PIN_COLS, true, SPI_MODE, SPI_MATRIX_DIVISOR);
        // spi_stop();
        spi_start(SPI_MATRIX_CHIP_SELECT_PIN_COLS, true, SPI_MODE, SPI_MATRIX_DIVISOR);
        spi_receive((uint8_t*)temp_col_receive, MATRIX_COLS_SHIFT_REGISTER_COUNT);
        spi_stop();

        temp_col_state = temp_col_receive[0] | (temp_col_receive[1] << 8);
        // if (temp_col_state != 0) {
        //     printf("row/row_val/col0/col1/col: [ %u / %u / %u / %u / %u ] \n", row, row_values[row], temp_col_receive[0], temp_col_receive[1], temp_col_state);
        // }
        temp_matrix[row] = temp_col_state;
    }
    bool matrix_has_changed = memcmp(current_matrix, temp_matrix, sizeof(temp_matrix)) != 0;
    if (matrix_has_changed) {
        memcpy(current_matrix, temp_matrix, sizeof(temp_matrix));
    }
    return matrix_has_changed;
}
