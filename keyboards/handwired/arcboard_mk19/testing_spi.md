
# testing shift registers notes

# real key layout testing
rows are being applied in reverse order....
thumbs are row0
but rows in keywell are in reverse order...
-fkeys are row5, keywell3 is row1

and the split is not being applied properly...
- row0 is tab-qwerty


interesting.  so cyboard hardware looks ok, but the application of the keymap is all over the place.
pin-handedness = right
- pcb-row0 = thumbs   = tab/qwerty  (keymap row6, left)
- pcb-row1 = f-keys   = nm,.        (keymap row11, right)
- pcb-row2 = num-keys = zxcv        (keymap row10, left)
- pcb-row3 = keywell1 = hjkl        (keymap row9, right)
- pcb-row4 = keywell2 = asdf        (keymap row8, left)
- pcb-row5 = keywell3 = yuiop       (keymap row7, right)


# scratchpad for feb3 testing
note: split not connected
removing 1 row: 1344 -> 1407 = +63 improvement
removing 2 rows:1344 -> 1532 = +188 improvement
removing 3 rows:1344 -> 1642 = +298 improvement
removing 4 rows:1344 -> 1759 = +415 improvement
removing 5 rows:1344 -> 1920 = +576 improvement
removing 6 rows:1344 -> 2100 = +756 improvement
removing 7 rows:1344 -> 2315 = +971 improvement
removing 8 rows:1344 -> 2580 = +1236 improvement -> 1675 (split costs 800)
removing prelim SPI call: 2580 -> 3235 = +655 improvement
10 rows = 1450 scan (w. split)

                {"matrix": [20, 0], "x": 0, "y": 0},
                {"matrix": [20, 1], "x": 1, "y": 0},
                {"matrix": [20, 2], "x": 2, "y": 0},
                {"matrix": [20, 3], "x": 3, "y": 0},
                {"matrix": [20, 4], "x": 4, "y": 0},
                {"matrix": [20, 5], "x": 5, "y": 0},
                {"matrix": [20, 6], "x": 5, "y": 0},
                {"matrix": [20, 7], "x": 5, "y": 0},
                {"matrix": [20, 8], "x": 0, "y": 0},
                {"matrix": [20, 9], "x": 1, "y": 0},
                {"matrix": [20, 10], "x": 2, "y": 0},
                {"matrix": [20, 11], "x": 3, "y": 0},
                {"matrix": [20, 12], "x": 4, "y": 0},
                {"matrix": [20, 13], "x": 5, "y": 0},
                {"matrix": [20, 14], "x": 5, "y": 0},
                {"matrix": [20, 15], "x": 5, "y": 0},
                {"matrix": [21, 0], "x": 0, "y": 0},
                {"matrix": [21, 1], "x": 1, "y": 0},
                {"matrix": [21, 2], "x": 2, "y": 0},
                {"matrix": [21, 3], "x": 3, "y": 0},
                {"matrix": [21, 4], "x": 4, "y": 0},
                {"matrix": [21, 5], "x": 5, "y": 0},
                {"matrix": [21, 6], "x": 5, "y": 0},
                {"matrix": [21, 7], "x": 5, "y": 0},
                {"matrix": [21, 8], "x": 0, "y": 0},
                {"matrix": [21, 9], "x": 1, "y": 0},
                {"matrix": [21, 10], "x": 2, "y": 0},
                {"matrix": [21, 11], "x": 3, "y": 0},
                {"matrix": [21, 12], "x": 4, "y": 0},
                {"matrix": [21, 13], "x": 5, "y": 0},
                {"matrix": [21, 14], "x": 5, "y": 0},
                {"matrix": [21, 15], "x": 5, "y": 0},
                {"matrix": [22, 0], "x": 0, "y": 0},
                {"matrix": [22, 1], "x": 1, "y": 0},
                {"matrix": [22, 2], "x": 2, "y": 0},
                {"matrix": [22, 3], "x": 3, "y": 0},
                {"matrix": [22, 4], "x": 4, "y": 0},
                {"matrix": [22, 5], "x": 5, "y": 0},
                {"matrix": [22, 6], "x": 5, "y": 0},
                {"matrix": [22, 7], "x": 5, "y": 0},
                {"matrix": [22, 8], "x": 0, "y": 0},
                {"matrix": [22, 9], "x": 1, "y": 0},
                {"matrix": [22, 10], "x": 2, "y": 0},
                {"matrix": [22, 11], "x": 3, "y": 0},
                {"matrix": [22, 12], "x": 4, "y": 0},
                {"matrix": [22, 13], "x": 5, "y": 0},
                {"matrix": [22, 14], "x": 5, "y": 0},
                {"matrix": [22, 15], "x": 5, "y": 0},
                {"matrix": [23, 0], "x": 0, "y": 0},
                {"matrix": [23, 1], "x": 1, "y": 0},
                {"matrix": [23, 2], "x": 2, "y": 0},
                {"matrix": [23, 3], "x": 3, "y": 0},
                {"matrix": [23, 4], "x": 4, "y": 0},
                {"matrix": [23, 5], "x": 5, "y": 0},
                {"matrix": [23, 6], "x": 5, "y": 0},
                {"matrix": [23, 7], "x": 5, "y": 0},
                {"matrix": [23, 8], "x": 0, "y": 0},
                {"matrix": [23, 9], "x": 1, "y": 0},
                {"matrix": [23, 10], "x": 2, "y": 0},
                {"matrix": [23, 11], "x": 3, "y": 0},
                {"matrix": [23, 12], "x": 4, "y": 0},
                {"matrix": [23, 13], "x": 5, "y": 0},
                {"matrix": [23, 14], "x": 5, "y": 0},
                {"matrix": [23, 15], "x": 5, "y": 0},
                {"matrix": [24, 0], "x": 0, "y": 0},
                {"matrix": [24, 1], "x": 1, "y": 0},
                {"matrix": [24, 2], "x": 2, "y": 0},
                {"matrix": [24, 3], "x": 3, "y": 0},
                {"matrix": [24, 4], "x": 4, "y": 0},
                {"matrix": [24, 5], "x": 5, "y": 0},
                {"matrix": [24, 6], "x": 5, "y": 0},
                {"matrix": [24, 7], "x": 5, "y": 0},
                {"matrix": [24, 8], "x": 0, "y": 0},
                {"matrix": [24, 9], "x": 1, "y": 0},
                {"matrix": [24, 10], "x": 2, "y": 0},
                {"matrix": [24, 11], "x": 3, "y": 0},
                {"matrix": [24, 12], "x": 4, "y": 0},
                {"matrix": [24, 13], "x": 5, "y": 0},
                {"matrix": [24, 14], "x": 5, "y": 0},
                {"matrix": [24, 15], "x": 5, "y": 0},
                {"matrix": [25, 0], "x": 0, "y": 0},
                {"matrix": [25, 1], "x": 1, "y": 0},
                {"matrix": [25, 2], "x": 2, "y": 0},
                {"matrix": [25, 3], "x": 3, "y": 0},
                {"matrix": [25, 4], "x": 4, "y": 0},
                {"matrix": [25, 5], "x": 5, "y": 0},
                {"matrix": [25, 6], "x": 5, "y": 0},
                {"matrix": [25, 7], "x": 5, "y": 0},
                {"matrix": [25, 8], "x": 0, "y": 0},
                {"matrix": [25, 9], "x": 1, "y": 0},
                {"matrix": [25, 10], "x": 2, "y": 0},
                {"matrix": [25, 11], "x": 3, "y": 0},
                {"matrix": [25, 12], "x": 4, "y": 0},
                {"matrix": [25, 13], "x": 5, "y": 0},
                {"matrix": [25, 14], "x": 5, "y": 0},
                {"matrix": [25, 15], "x": 5, "y": 0},
                {"matrix": [26, 0], "x": 0, "y": 0},
                {"matrix": [26, 1], "x": 1, "y": 0},
                {"matrix": [26, 2], "x": 2, "y": 0},
                {"matrix": [26, 3], "x": 3, "y": 0},
                {"matrix": [26, 4], "x": 4, "y": 0},
                {"matrix": [26, 5], "x": 5, "y": 0},
                {"matrix": [26, 6], "x": 5, "y": 0},
                {"matrix": [26, 7], "x": 5, "y": 0},
                {"matrix": [26, 8], "x": 0, "y": 0},
                {"matrix": [26, 9], "x": 1, "y": 0},
                {"matrix": [26, 10], "x": 2, "y": 0},
                {"matrix": [26, 11], "x": 3, "y": 0},
                {"matrix": [26, 12], "x": 4, "y": 0},
                {"matrix": [26, 13], "x": 5, "y": 0},
                {"matrix": [26, 14], "x": 5, "y": 0},
                {"matrix": [26, 15], "x": 5, "y": 0},
                {"matrix": [27, 0], "x": 0, "y": 0},
                {"matrix": [27, 1], "x": 1, "y": 0},
                {"matrix": [27, 2], "x": 2, "y": 0},
                {"matrix": [27, 3], "x": 3, "y": 0},
                {"matrix": [27, 4], "x": 4, "y": 0},
                {"matrix": [27, 5], "x": 5, "y": 0},
                {"matrix": [27, 6], "x": 5, "y": 0},
                {"matrix": [27, 7], "x": 5, "y": 0},
                {"matrix": [27, 8], "x": 0, "y": 0},
                {"matrix": [27, 9], "x": 1, "y": 0},
                {"matrix": [27, 10], "x": 2, "y": 0},
                {"matrix": [27, 11], "x": 3, "y": 0},
                {"matrix": [27, 12], "x": 4, "y": 0},
                {"matrix": [27, 13], "x": 5, "y": 0},
                {"matrix": [27, 14], "x": 5, "y": 0},
                {"matrix": [27, 15], "x": 5, "y": 0},
                {"matrix": [28, 0], "x": 0, "y": 0},
                {"matrix": [28, 1], "x": 1, "y": 0},
                {"matrix": [28, 2], "x": 2, "y": 0},
                {"matrix": [28, 3], "x": 3, "y": 0},
                {"matrix": [28, 4], "x": 4, "y": 0},
                {"matrix": [28, 5], "x": 5, "y": 0},
                {"matrix": [28, 6], "x": 5, "y": 0},
                {"matrix": [28, 7], "x": 5, "y": 0},
                {"matrix": [28, 8], "x": 0, "y": 0},
                {"matrix": [28, 9], "x": 1, "y": 0},
                {"matrix": [28, 10], "x": 2, "y": 0},
                {"matrix": [28, 11], "x": 3, "y": 0},
                {"matrix": [28, 12], "x": 4, "y": 0},
                {"matrix": [28, 13], "x": 5, "y": 0},
                {"matrix": [28, 14], "x": 5, "y": 0},
                {"matrix": [28, 15], "x": 5, "y": 0},
                {"matrix": [29, 0], "x": 0, "y": 0},
                {"matrix": [29, 1], "x": 1, "y": 0},
                {"matrix": [29, 2], "x": 2, "y": 0},
                {"matrix": [29, 3], "x": 3, "y": 0},
                {"matrix": [29, 4], "x": 4, "y": 0},
                {"matrix": [29, 5], "x": 5, "y": 0},
                {"matrix": [29, 6], "x": 5, "y": 0},
                {"matrix": [29, 7], "x": 5, "y": 0},
                {"matrix": [29, 8], "x": 0, "y": 0},
                {"matrix": [29, 9], "x": 1, "y": 0},
                {"matrix": [29, 10], "x": 2, "y": 0},
                {"matrix": [29, 11], "x": 3, "y": 0},
                {"matrix": [29, 12], "x": 4, "y": 0},
                {"matrix": [29, 13], "x": 5, "y": 0},
                {"matrix": [29, 14], "x": 5, "y": 0},
                {"matrix": [29, 15], "x": 5, "y": 0},
                {"matrix": [30, 0], "x": 0, "y": 0},
                {"matrix": [30, 1], "x": 1, "y": 0},
                {"matrix": [30, 2], "x": 2, "y": 0},
                {"matrix": [30, 3], "x": 3, "y": 0},
                {"matrix": [30, 4], "x": 4, "y": 0},
                {"matrix": [30, 5], "x": 5, "y": 0},
                {"matrix": [30, 6], "x": 5, "y": 0},
                {"matrix": [30, 7], "x": 5, "y": 0},
                {"matrix": [30, 8], "x": 0, "y": 0},
                {"matrix": [30, 9], "x": 1, "y": 0},
                {"matrix": [30, 10], "x": 2, "y": 0},
                {"matrix": [30, 11], "x": 3, "y": 0},
                {"matrix": [30, 12], "x": 4, "y": 0},
                {"matrix": [30, 13], "x": 5, "y": 0},
                {"matrix": [30, 14], "x": 5, "y": 0},
                {"matrix": [30, 15], "x": 5, "y": 0},
                {"matrix": [31, 0], "x": 0, "y": 0},
                {"matrix": [31, 1], "x": 1, "y": 0},
                {"matrix": [31, 2], "x": 2, "y": 0},
                {"matrix": [31, 3], "x": 3, "y": 0},
                {"matrix": [31, 4], "x": 4, "y": 0},
                {"matrix": [31, 5], "x": 5, "y": 0},
                {"matrix": [31, 6], "x": 5, "y": 0},
                {"matrix": [31, 7], "x": 5, "y": 0},
                {"matrix": [31, 8], "x": 0, "y": 0},
                {"matrix": [31, 9], "x": 1, "y": 0},
                {"matrix": [31, 10], "x": 2, "y": 0},
                {"matrix": [31, 11], "x": 3, "y": 0},
                {"matrix": [31, 12], "x": 4, "y": 0},
                {"matrix": [31, 13], "x": 5, "y": 0},
                {"matrix": [31, 14], "x": 5, "y": 0},
                {"matrix": [31, 15], "x": 5, "y": 0}


        KC_A,  KC_B,    KC_C,    KC_D,    KC_E,   KC_F,   KC_G,   KC_H,  KC_I, KC_J, KC_K, KC_L, KC_M, KC_N, KC_O, KC_P,
        KC_A,  KC_B,    KC_C,    KC_D,    KC_E,   KC_F,   KC_G,   KC_H,  KC_I, KC_J, KC_K, KC_L, KC_M, KC_N, KC_O, KC_P,
        KC_A,  KC_B,    KC_C,    KC_D,    KC_E,   KC_F,   KC_G,   KC_H,  KC_I, KC_J, KC_K, KC_L, KC_M, KC_N, KC_O, KC_P,
        KC_A,  KC_B,    KC_C,    KC_D,    KC_E,   KC_F,   KC_G,   KC_H,  KC_I, KC_J, KC_K, KC_L, KC_M, KC_N, KC_O, KC_P,
        KC_A,  KC_B,    KC_C,    KC_D,    KC_E,   KC_F,   KC_G,   KC_H,  KC_I, KC_J, KC_K, KC_L, KC_M, KC_N, KC_O, KC_P,
        KC_A,  KC_B,    KC_C,    KC_D,    KC_E,   KC_F,   KC_G,   KC_H,  KC_I, KC_J, KC_K, KC_L, KC_M, KC_N, KC_O, KC_P,
        KC_A,  KC_B,    KC_C,    KC_D,    KC_E,   KC_F,   KC_G,   KC_H,  KC_I, KC_J, KC_K, KC_L, KC_M, KC_N, KC_O, KC_P,
        KC_A,  KC_B,    KC_C,    KC_D,    KC_E,   KC_F,   KC_G,   KC_H,  KC_I, KC_J, KC_K, KC_L, KC_M, KC_N, KC_O, KC_P,
        KC_A,  KC_B,    KC_C,    KC_D,    KC_E,   KC_F,   KC_G,   KC_H,  KC_I, KC_J, KC_K, KC_L, KC_M, KC_N, KC_O, KC_P,
        KC_A,  KC_B,    KC_C,    KC_D,    KC_E,   KC_F,   KC_G,   KC_H,  KC_I, KC_J, KC_K, KC_L, KC_M, KC_N, KC_O, KC_P,
        KC_A,  KC_B,    KC_C,    KC_D,    KC_E,   KC_F,   KC_G,   KC_H,  KC_I, KC_J, KC_K, KC_L, KC_M, KC_N, KC_O, KC_P,
        KC_A,  KC_B,    KC_C,    KC_D,    KC_E,   KC_F,   KC_G,   KC_H,  KC_I, KC_J, KC_K, KC_L, KC_M, KC_N, KC_O, KC_P

# what does the message thing even mean
```c
static inline void write_to_rows(uint16_t value) {
    printf("value: %u \n", value);
    printf("value >> 8: %u \n",(value >> 8));
    printf("(value >> 8) & 0xFF: %u \n",(value >> 8) & 0xFF);
    printf("(value & 0xFF): %u \n",(value & 0xFF));
    uint8_t message[2] = {(value >> 8) & 0xFF, (uint8_t)(value & 0xFF)};
    spi_start(SPI_MATRIX_CHIP_SELECT_PIN_ROWS, false, SPI_MODE, SPI_MATRIX_DIVISOR);
    spi_transmit(message, 2);
    spi_stop();
}
```

```
value: 32768
value >> 8: 128
(value >> 8) & 0xFF: 128
(value & 0xFF): 0
value: 16384
value >> 8: 64
(value >> 8) & 0xFF: 64
(value & 0xFF): 0
value: 8192
value >> 8: 32
(value >> 8) & 0xFF: 32
(value & 0xFF): 0
value: 4096
value >> 8: 16
(value >> 8) & 0xFF: 16
(value & 0xFF): 0
value: 2048
value >> 8: 8
(value >> 8) & 0xFF: 8
(value & 0xFF): 0
value: 1024
value >> 8: 4
(value >> 8) & 0xFF: 4
(value & 0xFF): 0
value: 512
value >> 8: 2
(value >> 8) & 0xFF: 2
(value & 0xFF): 0
value: 256
value >> 8: 1
(value >> 8) & 0xFF: 1
(value & 0xFF): 0
value: 128
value >> 8: 0
(value >> 8) & 0xFF: 0
(value & 0xFF): 128
value: 64
value >> 8: 0
(value >> 8) & 0xFF: 0
(value & 0xFF): 64
value: 32
value >> 8: 0
(value >> 8) & 0xFF: 0
(value & 0xFF): 32
value: 16
value >> 8: 0
(value >> 8) & 0xFF: 0
(value & 0xFF): 16
value: 8
value >> 8: 0
(value >> 8) & 0xFF: 0
(value & 0xFF): 8
value: 4
value >> 8: 0
(value >> 8) & 0xFF: 0
(value & 0xFF): 4
value: 2
value >> 8: 0
(value >> 8) & 0xFF: 0
(value & 0xFF): 2
value: 1
value >> 8: 0
(value >> 8) & 0xFF: 0
(value & 0xFF): 1
```

so value = bit value from ROWS converted to int8, e.g. `0x8000` hex = `32768` int = `10000000 00000000` binary -> 

so `10000000 00000000` in binary looks like this in our output...
```
value: 32768
value >> 8: 128
(value >> 8) & 0xFF: 128
(value & 0xFF): 0
```

From the `config.h`...
- the raw value in our config is `0x8000`

...into `matrix.c`...
- when you `uint16_t value` that it becomes `32768`
- `uint8_t message[2] = {(value >> 8) & 0xFF, (uint8_t)(value & 0xFF)};`
- when you bitshift `10000000 00000000` over to the right 8 bits (`00000000`)...
- ...you get `00000000 10000000`...
- which in base2 = `128` (128 64 32 16 8 4 2 1)
- and b/c we need to send two messages, one for each shift register...

...first shift register...
- the first shift register gets `(value >> 8) & 0xFF` ----> `10000000` (value needs to be bit-shifted cuz the register only understands 8 bits)
- so you take `10000000 00000000` and bitshift >> to get `00000000 100000000`
- the `& 0xFF` is "bitwise AND".  "return only the bits matching hex `FF` aka `11111111`; everything else zero out"
- so, the bitshifted `00000000 100000000` suddenly becomes `100000000`; 
- our first byte of the message is therefore `100000000`, or, set the first (last?) pin HIGH.

...second shift register...
- the second gets `(value & 0xFF)` ----> `10000000 00000000`, but only give me the bits under `11111111`
- so the second byte of the message is therefore `00000000`, or, set NO pins HIGH.


going back to ordering, if we are seeing ROW0 HIGH, when we expect ROW7 HIGH that means our bit message is completely reversed.
what could reverse it?
- the order the row bits are processed
- um


# trying to explain how this works...
`matrix_scan_custom` runs on every loop of the controller.  It runs before any kind of keystroke logic is applied.
the function returns the matrix object with which all other logic runs against.

config data needed: rows = array of bits
1. set up a temporary matrix object (same dimensional sizes as the 'current' matrix)
row0[col0,col1,col2,etc]
row1[col0,col1,col2,etc]
row2[col0,col1,col2,etc]
etc 
2. loop over every row, row0 -> rowX
  - your row loop index should match, positionally, a config item that is a list of hex bits
    - e.g. 8 bits = #define ROWS {0x0080, 0x0040, 0x0020, 0x0010, 0x0008, 0x0004, 0x0002, 0x0001}
  - create a temporary column state object
    - temp_state[col0,col1,col2,etc] e.g. temp_state[01000000] = col1 HIGH in row0
  - set row0 pin high
    - create data-to-transmit from your row pin, 
      - value = 10000000 = set row0 high
    - spi_transmit 2 bytes; your row is 1, all other row pins are 0
  - pull all column shift register data - 1 byte / 8 bits per shift register
    - spi_receive, expect 2 bytes - it receives 8 bits at a time, therefore
    - receive_data[0] = 01000000 & receive_data[1] = 00000000
    - combine the two bytes received into a single 16-bit value
        combined_data = 0100000000000000
    - that becomes our row0
3. 


# trying to revert to full bitmasks
christrotter:handwired/arcboard_mk19:3: Receive all cols: 8 [8 / 0]
christrotter:handwired/arcboard_mk19:3: row iteration: 9 [row index: 4]; col bit received: 8

christrotter:handwired/arcboard_mk19:1: Receive all cols: 1 [1 / 0]
christrotter:handwired/arcboard_mk19:1: row iteration: 7 [row index: 16]; col bit received: 1
christrotter:handwired/arcboard_mk19:1: Receive all cols: 32 [32 / 0]
christrotter:handwired/arcboard_mk19:1: row iteration: 7 [row index: 16]; col bit received: 32

christrotter:handwired/arcboard_mk19:3: Receive all cols: 1 [1 / 0]
christrotter:handwired/arcboard_mk19:3: row iteration: 11 [row index: 1]; col bit received: 1
christrotter:handwired/arcboard_mk19:3: Receive all cols: 33 [33 / 0]
christrotter:handwired/arcboard_mk19:3: row iteration: 11 [row index: 1]; col bit received: 33
christrotter:handwired/arcboard_mk19:2: Receive all cols: 32 [32 / 0]
christrotter:handwired/arcboard_mk19:2: row iteration: 11 [row index: 1]; col bit received: 32



christrotter:handwired/arcboard_mk19:1: col_pin_state: 8 [8 / 0]
christrotter:handwired/arcboard_mk19:1: row iteration: 1 [row index: 1024]; col bit received: 8
christrotter:handwired/arcboard_mk19:1:
christrotter:handwired/arcboard_mk19:1: r/c 01234567
christrotter:handwired/arcboard_mk19:1: 00: 00000000
christrotter:handwired/arcboard_mk19:1: keyboard_report: 00 | 10 00 00 00 00 00




# whyfore is the iteration bumped by one
christrotter:handwired/arcboard_mk19:1: Starting row: 0
christrotter:handwired/arcboard_mk19:1: bitshifted row: 1 message:  1 / 0
christrotter:handwired/arcboard_mk19:1: Starting row: 1
christrotter:handwired/arcboard_mk19:1: bitshifted row: 2 message:  2 / 0
christrotter:handwired/arcboard_mk19:1: Starting row: 2
christrotter:handwired/arcboard_mk19:1: bitshifted row: 4 message:  4 / 0
christrotter:handwired/arcboard_mk19:1: Starting row: 3
christrotter:handwired/arcboard_mk19:1: bitshifted row: 8 message:  8 / 0
christrotter:handwired/arcboard_mk19:1: Starting row: 4
christrotter:handwired/arcboard_mk19:1: bitshifted row: 16 message:  16 / 0

printf("iteration: %u [index: %u]; col received: %u [%u / %u] \n", row, rows[row], col_pin_state, temp_receive[0],(temp_receive[1] << 8));
Trigger col1 to row15:
`iteration: 0 [index: 0]; col received: 1 [1 / 0]`



# add the extra cols/rows to the layout


# split usb-c power
Uhm need to solder the bypass... :D



# split
adding split config starts throwing this:
```c
Compiling: keyboards/handwired/arcboard_mk19/matrix.c                                              keyboards/handwired/arcboard_mk19/matrix.c: In function 'matrix_scan_custom':
keyboards/handwired/arcboard_mk19/matrix.c:32:5: error: iteration 16 invokes undefined behavior [-Werror=aggressive-loop-optimizations]
     write_to_rows(row_values[row]);
     ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
keyboards/handwired/arcboard_mk19/matrix.c:38:5: note: within this loop
     for (uint16_t row = 0; row < (MATRIX_ROWS * 2); row++) {
     ^~~
cc1: all warnings being treated as errors
 [ERRORS]
 |
 |
 |
gmake: *** [builddefs/common_rules.mk:369: .build/obj_handwired_arcboard_mk19_christrotter/matrix.o] Error 1
```

We changed MATRIX_ROWS calls to be just '16', and it got farther...

## soft-serial missing
Also forgot this... `SERIAL_DRIVER = vendor` ... in rules.mk.

# no key-up
## day1
Ok, so what is the logic here...
- foreach row
  - set row pin high
  - scan all cols for matching high
  - build row in temp_matrix
- now we have a rows/cols temp_matrix
- compare temp_matrix against current_matrix
  - if no changes, done;
  - if changes, overwrite current_matrix with temp_matrix
HERE.  now what?

If I connect (row pin, count3 from left) and (col pin, count3 from left) together...
```
christrotter:handwired/arcboard_mk19:2:
christrotter:handwired/arcboard_mk19:2: r/c 0123456789ABCDEF
christrotter:handwired/arcboard_mk19:2: 00: 0000000000000000
christrotter:handwired/arcboard_mk19:2: 01: 0000000000000000
christrotter:handwired/arcboard_mk19:2: 02: 0001000000000000
christrotter:handwired/arcboard_mk19:2: 03: 0000000000000000
christrotter:handwired/arcboard_mk19:2: 04: 0000000000000000
christrotter:handwired/arcboard_mk19:2: 05: 0000000000000000
christrotter:handwired/arcboard_mk19:2: 06: 0000000000000000
christrotter:handwired/arcboard_mk19:2: 07: 0000000000000000
christrotter:handwired/arcboard_mk19:2: 08: 0000000000000000
christrotter:handwired/arcboard_mk19:2: 09: 0000000000000000
christrotter:handwired/arcboard_mk19:2: 0A: 0000000000000000
christrotter:handwired/arcboard_mk19:2: 0B: 0000000000000000
christrotter:handwired/arcboard_mk19:2: 0C: 0000000000000000
christrotter:handwired/arcboard_mk19:2: 0D: 0000000000000000
christrotter:handwired/arcboard_mk19:2: 0E: 0000000000000000
christrotter:handwired/arcboard_mk19:2: 0F: 0000000000000000
christrotter:handwired/arcboard_mk19:2: keyboard_report: 00 | 06 00 00 00 00 00
```
And then:
`➜  arcboard_mk19 git:(arcboard-series) ✗ cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc`

So it's outputting a keystroke...just not recognizing that it's been released...

If i had to guess, one set of registers is not being cleared...?

Tried another board, same result.  So either there is something dramatically wrong with the hardware, or something being missed in firmware.

## day2
is it possible the rows aren't being un-set from 'high'?

Outputting our 'message'...
```
christrotter:handwired/arcboard_mk19:1: our spi message: 128 0
christrotter:handwired/arcboard_mk19:1: our spi message: 64 0
christrotter:handwired/arcboard_mk19:1: our spi message: 32 0
christrotter:handwired/arcboard_mk19:1: our spi message: 16 0
christrotter:handwired/arcboard_mk19:1: our spi message: 8 0
christrotter:handwired/arcboard_mk19:1: our spi message: 4 0
christrotter:handwired/arcboard_mk19:1: our spi message: 2 0
christrotter:handwired/arcboard_mk19:1: our spi message: 1 0
christrotter:handwired/arcboard_mk19:1: our spi message: 0 128
christrotter:handwired/arcboard_mk19:1: our spi message: 0 64
christrotter:handwired/arcboard_mk19:1: our spi message: 0 32
christrotter:handwired/arcboard_mk19:1: our spi message: 0 16
christrotter:handwired/arcboard_mk19:1: our spi message: 0 8
christrotter:handwired/arcboard_mk19:1: our spi message: 0 4
christrotter:handwired/arcboard_mk19:1: our spi message: 0 2
christrotter:handwired/arcboard_mk19:1: our spi message: 0 1
```
So the row is just constantly cycling, good.

        for(int i = 0; i < MATRIX_ROWS; i++) {
            printf("temp_matrix: %d : %d \n", i, temp_matrix[i]); // this outputs zeros
        }
        if (col_pin_state != 0) {
            printf("col_pin_state: %u \n", col_pin_state);
        }

conclusion: Yes, they were not being 'un-set from high' cuz we were missing pull-down resistors on the col pins.  Adding those cleared up all weirdness. 

# testing the 595s
This code was sufficient for me to see 3.3v on row pins 0-7 and 0v on row pins 8-15.
Flipping the ff and 00 in message reversed the voltage readings, as expected.
```c
bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool matrix_has_changed = false;
    uint8_t message[2] = {0xff, 0x00};
    spi_start(SPI_MATRIX_CHIP_SELECT_PIN_ROWS, false, SPI_MODE, SPI_MATRIX_DIVISOR);
    spi_transmit(message, 2);
    spi_stop();
    return matrix_has_changed;
}
```

# testing the 589s


    // bool matrix_has_changed = false;
    // uint8_t message[2] = {0xff, 0x00};
    // spi_start(SPI_MATRIX_CHIP_SELECT_PIN_ROWS, false, SPI_MODE, SPI_MATRIX_DIVISOR);
    // spi_transmit(message, 2);
    // spi_stop();
// 
    // static matrix_row_t temp_matrix[MATRIX_ROWS] = {0};
    // spi_start(SPI_MATRIX_CHIP_SELECT_PIN_COLS, false, SPI_MODE, SPI_MATRIX_DIVISOR);
    // spi_receive((uint8_t*)temp_matrix, MATRIX_COLS_SHIFT_REGISTER_COUNT * sizeof(matrix_row_t));
    // spi_stop();
// 
    // bool matrix_has_changed = memcmp(current_matrix, temp_matrix, sizeof(temp_matrix)) != 0;
    // if (matrix_has_changed) {
    //     memcpy(current_matrix, temp_matrix, sizeof(temp_matrix));
    //     printf("Matrix has changed");
    // }


# More digging
- row pin connected to each col pin outputs 1,2,4,8,etc,32768

```c
spi_status_t spi_transmit(const uint8_t *data, uint16_t length);
spi_status_t spi_transmit(const uint8_t *data, uint16_t length) {
    spiSend(&SPI_DRIVER, length, data);
    return SPI_STATUS_SUCCESS;
}
```

```c
spi_status_t spi_receive(uint8_t *data, uint16_t length);
spi_status_t spi_receive(uint8_t *data, uint16_t length) {
    spiReceive(&SPI_DRIVER, length, data);
    return SPI_STATUS_SUCCESS;
}
```

# trying to understand what's in the matrix
```c
bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    memset(current_matrix, 0, msize);
    for (uint16_t row = 0; row < MATRIX_ROWS; row++) {
        set_row_high(row);
        uint16_t temp_col_state = read_all_cols();
        if (temp_col_state != 0) {
            // printf("col register data: %u \n", temp_col_state);
        }
        for (uint16_t current_col = 0; current_col < MATRIX_COLS; current_col++) {
            prev_matrix[current_col] |= (((temp_col_state & (1 << current_col)) ? 1 : 0) << row);
        }
    }

    bool matrix_has_changed = memcmp(current_matrix, prev_matrix, msize) != 0;
    if (matrix_has_changed) {
        for(int i = 0; i < MATRIX_ROWS; i++) {
            printf(" %d ", current_matrix[i]); // this outputs zeros
        }
        memcpy(prev_matrix, current_matrix, msize);
        printf("Matrix has changed. \n");
    }
    return matrix_has_changed;
}
```

```
christrotter:handwired/arcpedals_mk2:2: matrix scan frequency: 3123
christrotter:handwired/arcboard_mk19:1:  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0 Matrix has changed.
christrotter:handwired/arcboard_mk19:1:  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0 Matrix has changed.
christrotter:handwired/arcboard_mk19:1:  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0 Matrix has changed.
christrotter:handwired/arcboard_mk19:1:  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0 Matrix has changed.
```

So the col register data has values...but the matrix is not changing...

Output of msize is 32.

```c
printf("row (%d), col register data: %u \n", row, temp_col_state);
```
This correctly changes as i move through rows.
```
christrotter:handwired/arcboard_mk19:2: row (3), col register data: 2
christrotter:handwired/arcboard_mk19:2: row (2), col register data: 2
```

I found current/prev was being mixed up.  Removed 'prev' and replaced w. 'temp', cuz i get that naming logic now.
Current = what is in memory
Temp = the fresh reading of pins that we may or may not write to memory

```
christrotter:handwired/arcboard_mk19:1:  16  0  0  0  65535  0  0  0  0  0  0  0  0  0  0  0 Matrix of size 32 has changed.
christrotter:handwired/arcboard_mk19:1:  16  0  0  0  65535  0  0  0  0  0  0  0  0  0  0  0 Matrix of size 32 has changed.
christrotter:handwired/arcboard_mk19:1:  0  0  0  0  10239  0  0  0  0  0  0  0  0  0  0  0 Matrix of size 32 has changed.
christrotter:handwired/arcboard_mk19:1:  0  0  0  0  64  0  0  0  0  0  0  0  0  0  0  0 Matrix of size 32 has changed.
christrotter:handwired/arcboard_mk19:1:  0  0  0  0  64  0  0  0  0  0  0  0  0  0  0  0 Matrix of size 32 has changed.
christrotter:handwired/arcboard_mk19:1:  16  0  0  0  65534  0  0  0  0  0  0  0  0  0  0  0 Matrix of size 32 has changed.
christrotter:handwired/arcboard_mk19:1:  16  0  0  0  65535  0  0  0  0  0  0  0  0  0  0  0 Matrix of size 32 has changed.
christrotter:handwired/arcboard_mk19:1:  16  0  0  0  65535  0  0  0  0  0  0  0  0  0  0  0 Matrix of size 32 has changed.
christrotter:handwired/arcboard_mk19:1:  0  0  0  0  8445  0  0  0  0  0  0  0  0  0  0  0 Matrix of size 32 has changed.
christrotter:handwired/arcboard_mk19:1:  0  0  0  0  64  0  0  0  0  0  0  0  0  0  0  0 Matrix of size 32 has changed.
christrotter:handwired/arcboard_mk19:1:  0  0  0  0  64  0  0  0  0  0  0  0  0  0  0  0 Matrix of size 32 has changed.
christrotter:handwired/arcboard_mk19:1:  0  0  0  0  8256  0  0  0  0  0  0  0  0  0  0  0 Matrix of size 32 has changed.
```

Some of these values are wack tho.

Apparently: `sizeof(matrix_row_t) = 2`

I re-looked at tzarc's implementation and fixed some stuff.
Now i get...
```
➜  arcboard_mk19 git:(arcboard-series) ✗ vbvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
vvvvvvvvZXCVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
```

The key-up is not working or something.
Verified this with the qmk tester.

debounce: true does not help





// static inline uint16_t read_all_cols(void) {
//     uint16_t col_pin_state = 0;
// 
//     spi_start(SPI_MATRIX_CHIP_SELECT_PIN_COLS, false, SPI_MODE, SPI_MATRIX_DIVISOR); // cs pin, lsbFirst?, spi mode, spi divisor
//     spi_receive((uint8_t*)temp_matrix, MATRIX_COLS_SHIFT_REGISTER_COUNT * sizeof(matrix_row_t));
//     spi_stop(); 
//     
//     // feel like i don't know what is going on here...some bitshifting
//     // presumes that temp_matrix[] is only 0 or 1; and for [1], shift bits 8 cuz two pin sets, 0-7, and 8-15  ?
//     col_pin_state = temp_matrix[0] | (temp_matrix[1] >> 8);
// 
//     return col_pin_state;
// }

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    // what if we try putting everything that needs the temp_matrix inside this function...
    static matrix_row_t temp_matrix[MATRIX_ROWS] = {0};

    for (uint16_t row = 0; row < MATRIX_ROWS; row++) {
        set_row_high(row);

        // uint16_t temp_col_state = read_all_cols();
        // if (temp_col_state != 0) {
            // printf("row (%d), col register data: %u \n", row, temp_col_state);
        // }

        uint16_t col_pin_state = 0;

        spi_start(SPI_MATRIX_CHIP_SELECT_PIN_COLS, false, SPI_MODE, SPI_MATRIX_DIVISOR); // cs pin, lsbFirst?, spi mode, spi divisor
        spi_receive((uint8_t*)temp_matrix, MATRIX_COLS_SHIFT_REGISTER_COUNT * sizeof(matrix_row_t)); // receive(data, length) um like, data = the object to store the received data in?
        spi_stop(); 

        // feel like i don't know what is going on here...some bitshifting
        // presumes that the array temp_matrix[] is only 2 items; and for [1], shift bits 8 cuz two pin sets, 0-7, and 8-15  ?
        col_pin_state = temp_matrix[0] | (temp_matrix[1] >> 8);
        
        for (uint16_t current_col = 0; current_col < MATRIX_COLS; current_col++) {
            // printf("row: %d \n", row);
            // 
            temp_matrix[current_col] |= (((col_pin_state & (1 << current_col)) ? 1 : 0) << row);
        }
    }

    bool matrix_has_changed = memcmp(current_matrix, temp_matrix, sizeof(temp_matrix)) != 0;
    if (matrix_has_changed) {
        // for(int i = 0; i < MATRIX_COLS; i++) {
        //     printf(" %d ", temp_matrix[i]); // this outputs zeros
        // }
        // printf("sizeof matrix_row_t: %d \n", sizeof(matrix_row_t));
        memcpy(current_matrix, temp_matrix, sizeof(temp_matrix));
        // printf("Matrix of size %d has changed. \n", msize);
    }
    return matrix_has_changed;
}