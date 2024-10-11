# how custom matrix scans are handled in QMK-land
There seems to be many ways to slice this, so I will lay out three scenarios:
- how QMK vanilla matrix scans work
- how a ROW2COL implementation works
- how a COL2ROW implementation works
- how the previous/new matrix implementation works

# QMK's matrix scan
```c
uint8_t matrix_scan(void) {
    matrix_row_t curr_matrix[MATRIX_ROWS] = {0};

#if defined(DIRECT_PINS) || (DIODE_DIRECTION == COL2ROW)
    // Set row, read cols
    for (uint8_t current_row = 0; current_row < ROWS_PER_HAND; current_row++) {
        matrix_read_cols_on_row(curr_matrix, current_row);
    }
#elif (DIODE_DIRECTION == ROW2COL)
    // Set col, read rows
    matrix_row_t row_shifter = MATRIX_ROW_SHIFTER;
    for (uint8_t current_col = 0; current_col < MATRIX_COLS; current_col++, row_shifter <<= 1) {
        matrix_read_rows_on_col(curr_matrix, current_col, row_shifter);
    }
#endif

    bool changed = memcmp(raw_matrix, curr_matrix, sizeof(curr_matrix)) != 0;
    if (changed) memcpy(raw_matrix, curr_matrix, sizeof(curr_matrix));

#ifdef SPLIT_KEYBOARD
    changed = debounce(raw_matrix, matrix + thisHand, ROWS_PER_HAND, changed) | matrix_post_scan();
#else
    changed = debounce(raw_matrix, matrix, ROWS_PER_HAND, changed);
    matrix_scan_kb();
#endif
    return (uint8_t)changed;
}
```

# matrix comparison
```c
/* diode directions */
#define COL2ROW 0
#define ROW2COL 1 // whyfore?

/* matrix state(1:on, 0:off) */
extern matrix_row_t raw_matrix[MATRIX_ROWS]; // raw values
extern matrix_row_t matrix[MATRIX_ROWS];     // debounced values
// snip

__attribute__((weak)) void matrix_read_rows_on_col(matrix_row_t current_matrix[], uint8_t current_col, matrix_row_t row_shifter) {
    bool key_pressed = false;

    // Select col
    if (!select_col(current_col)) { // select col
        return;                     // skip NO_PIN col
    }
    matrix_output_select_delay();

    // For each row...
    for (uint8_t row_index = 0; row_index < ROWS_PER_HAND; row_index++) {
        // Check row pin state
        if (readMatrixPin(row_pins[row_index]) == 0) {
            // Pin LO, set col bit
            current_matrix[row_index] |= row_shifter;
            key_pressed = true;
        } else {
            // Pin HI, clear col bit
            current_matrix[row_index] &= ~row_shifter;
        }
    }

    // Unselect col
    unselect_col(current_col);
    matrix_output_unselect_delay(current_col, key_pressed); // wait for all Row signals to go HIGH
}

uint8_t matrix_scan(void) {
    matrix_row_t curr_matrix[MATRIX_ROWS] = {0};

#if defined(DIRECT_PINS) || (DIODE_DIRECTION == ROW2COL)
    // Set col, read rows // ct: this is backwards...uhhh right?
    // so what is this row shifter doing?
    // #define MATRIX_ROW_SHIFTER ((matrix_row_t)1)
    // elpekenin: IIRC that's just a "disguised" 1 that gets shifted to the left once(ie multiplied by 2) on each iteration of the scanning matrix procedure - it is a bitmask, basically
    // 
    matrix_row_t row_shifter = MATRIX_ROW_SHIFTER; 
    // what does the fourth thing in a for loop do?
    // init current_col; conditional of while current_col less than cols; increment current_col and left-shift row bits by 1?
    // ternary operator, apparently
    // so every current_col increment we also bit-shift row_shifter left by one position.
    // for each col, read 
    for (uint8_t current_col = 0; current_col < MATRIX_COLS; current_col++, row_shifter <<= 1) {
        matrix_read_rows_on_col(curr_matrix, current_col, row_shifter);
        // expanded...
        // Select col
        if (!select_col(current_col)) { // select col: setPinOutput_writeLow(pin);
            return;                     // skip NO_PIN col
        }

        // For each row...
        for (uint8_t row_index = 0; row_index < ROWS_PER_HAND; row_index++) {
            // Check row pin state
            // readMatrixPin: (readPin(pin) == MATRIX_INPUT_PRESSED_STATE) ? 0 : 1;
            if (readMatrixPin(row_pins[row_index]) == 0) {
                // Pin LO, set col bit
                current_matrix[row_index] |= row_shifter;
                key_pressed = true;
            } else {
                // Pin HI, clear col bit
                current_matrix[row_index] &= ~row_shifter;
            }
        }

        // Unselect col: setPinOutput_writeHigh(pin);
        unselect_col(current_col);
        }
#endif

    bool changed = memcmp(raw_matrix, curr_matrix, sizeof(curr_matrix)) != 0;
    if (changed) memcpy(raw_matrix, curr_matrix, sizeof(curr_matrix));

#ifdef SPLIT_KEYBOARD
    changed = debounce(raw_matrix, matrix + thisHand, ROWS_PER_HAND, changed) | matrix_post_scan();
#else
    changed = debounce(raw_matrix, matrix, ROWS_PER_HAND, changed);
    matrix_scan_kb();
#endif
    return (uint8_t)changed;
}
```


https://discord.com/channels/440868230475677696/440868230475677698/1115752917740298351
Bit shift works by moving whatever you start with over some number of places. If we start with decimal numbers that we're all used to it would look like this:

1 << 0 == 1

This is because you started with a 1 and moved it to the left 0 places.

1 << 1 == 10

This took the 1 and moved it to the left 1 place so it became a 10. If we moved it 2 places it would be 100, and so on.

The same thing happens with binary numbers except the places are powers of 2 instead of powers of 10. So instead of the places being 1, 10, 100, etc. they are 1, 2, 4, 8, 16, etc.

1 << 0 == 1

This is still true because 2^0 is 1, but 

1 << 1 == 2

because 2^1 is 2. In binary that's the 2s place.

So in your case you're shifting 1 by 0 places for Mac resulting in selecting layer 1 and by 2 places for Windows resulting in selecting layer 4 which you don't have.