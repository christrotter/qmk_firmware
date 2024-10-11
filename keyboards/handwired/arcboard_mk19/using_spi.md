# Using the SPI matrix-inator
At the end of the day, think of the shift register's I/O pins as row/col pins...just row/col pins that have been abstracted away from being directly wired to the MCU.

So the 'shift registers for dummies' version is:
- hook up your rows/cols as per ROW2COL
- less row usage = better performance
- your `matrix_pins` configuration must match your keymap (like anywhere in QMK)
- use `NO_PIN` instead of a specific GPIO
- you need SPI enabled and configured
- 5-6 GPIO buys you up to 32 row/col pins

## Basic configuration
```json
    "matrix_pins": {
        "custom_lite": true,
        "rows": ["NO_PIN", "NO_PIN", "NO_PIN", "NO_PIN", "NO_PIN", "NO_PIN", "NO_PIN", "NO_PIN", "NO_PIN", "NO_PIN"],
        "cols": ["NO_PIN", "NO_PIN", "NO_PIN", "NO_PIN", "NO_PIN", "NO_PIN", "NO_PIN", "NO_PIN", "NO_PIN", "NO_PIN", "NO_PIN", "NO_PIN", "NO_PIN", "NO_PIN", "NO_PIN", "NO_PIN"]
      },
```
```c
// SPI configuration
#define SPI_MATRIX_DIVISOR 16 // default
#define SPI_MODE 0 // default
#define SPI_DRIVER SPID1
#define SPI_SCK_PIN  GP10
#define SPI_MOSI_PIN GP11
#define SPI_MISO_PIN GP12

// todo: this will change
#define SPI_MATRIX_CHIP_SELECT_PIN_ROWS GP9
#define SPI_MATRIX_CHIP_SELECT_PIN_COLS GP5
#define MATRIX_COLS_SHIFT_REGISTER_COUNT 2   // 74HC589
#define MATRIX_ROWS_SHIFT_REGISTER_COUNT 2   // 74HC595
```

# But I don't understand how this works, tell me more...
First, it's very important to understand how the matrix scanning works.  Without a good grasp of this, shift registers are black magic.

## matrix scanning basics
Simply put, every loop of the QMK code runs a matrix scan, which... (in ROW2COL parlance)
- set up a temporary matrix array
- for each row
  - set the row HIGH (74HC595)
  - read all col pin states (74HC589)
  - write the col pin states into that row in the temporary matrix array
- compare the temporary matrix against the current matrix
  - if different, replace the current matrix array with the temporary one
    - this triggers things like keystrokes and whatnot to activate
  - if same, do nothing.

So you are one by one setting row pins HIGH and seeing if there is a connection between row and col.  Because only one row pin is HIGH, if any other col pins are also HIGH, there must be a completed circuit between the row and col - i.e. a key is pressed.

### ROW2COL or COL2ROW??
This is the `diode_direction` configuration.  Diodes are used to prevent noise in the matrix which causes sadness so you want them.  But diodes only let electricity flow one direction!  So their orientation matters.

Picking one or the other is somewhat arbitrary (_there are deep QMK reasons why one is better, but I don't understand any of that yet so we'll ignore this..._), but once you've set it, a number of QMK things rely on this being consistent.

I chose ROW2COL because I was using Cyboard's flex pcb system, and Cyboard chose ROW2COL.  I asked them why - no particular reason!  So here we are.

Just know that for all intents and purposes, they work the same way - as long as you keep the `diode_direction` mental model front and center!

## shift registers - how do they work??
Again, the simple version...
- each register has 8 inputs (74HC589) or 8 outputs (744HC595)
  - 8 pins = 8 bits = 1 byte
  - except, input and output is not quite right
  - 589 reads the state of its pins (pin, are you HIGH? if not, LOW)
  - 595 sets the state of its pins (PIN, go HIGH, if not, LOW)
- each register has the ability to 'batch' the requested pin states as 1 byte
- you send 1 byte per register via SPI - if 2 registers, 2 bytes
  - e.g. 00010001 to a 595 register is saying, please set pin 0 and 4 HIGH (recall 8 bits, in order, looks like: 128 64 32 16 8 4 2 1)
- registers can be daisy chained

Visualizing the underlying logic...
```
 decimal       hex        bits
    1       = 0x0001 = 0b0000000000000001    = register1 => pcb-row0
    2       = 0x0002 = 0b0000000000000010    = register1 => pcb-row1
    4       = 0x0004 = 0b0000000000000100    = register1 => pcb-row2
    8       = 0x0008 = 0b0000000000001000    = register1 => pcb-row3
    16      = 0x0010 = 0b0000000000010000    = register1 => pcb-row4
    32      = 0x0020 = 0b0000000000100000    = register1 => pcb-row5
    64      = 0x0040 = 0b0000000001000000    = register1 => pcb-row6
    128     = 0x0080 = 0b0000000010000000    = register1 => pcb-row7
    256     = 0x0100 = 0b0000000100000000    = register2 => pcb-row8
    512     = 0x0200 = 0b0000001000000000    = register2 => pcb-row9
    1024    = 0x0400 = 0b0000010000000000    = register2 => pcb-row10 
    2k      = 0x0800 = 0b0000100000000000    = register2 => pcb-row11 
    4k      = 0x1000 = 0b0001000000000000    = register2 => pcb-row12
    8k      = 0x2000 = 0b0010000000000000    = register2 => pcb-row13
    16k     = 0x4000 = 0b0100000000000000    = register2 => pcb-row14
    32k     = 0x8000 = 0b1000000000000000    = register2 => pcb-row15
```

## shift registers - how do we talk to them??
This is where things get weird in code.  I'm not even sure who first wrote this, but this is what it is doing...
```c
uint8_t message[2] = {(uint8_t)(value & 0xFF), (value >> 8) & 0xFF};
```
- the goal is to set a row pin HIGH - just one!
- you pass in your row value in 16-bit decimal
- you split the 16-bit value into the message object's 8-bit format
- message is an array of 2 b/c 2 shift registers
- 2 shift registers looking for 8 bits of data each...

So take the example from the above table - "pcb-row15, set this HIGH".
- the `uint16_t value` is `32768`
- `uint8_t message[2] = {(value >> 8) & 0xFF, (uint8_t)(value & 0xFF)};`
- when you bitshift `10000000 00000000` over to the right 8 bits (`00000000`)...
- ...you get `00000000 10000000`...
- which in bits = `128` (128 64 32 16 8 4 2 1)
- and b/c we need to send two messages, one for each shift register...

...first shift register...
- the first gets `(value & 0xFF)` ----> `10000000 00000000`, but only give me the bits under `11111111`
- so the first byte of the message is therefore `00000000`, or, set NO pins HIGH.

...second shift register...
- the second shift register gets `(value >> 8) & 0xFF` ----> `10000000` (value needs to be bit-shifted cuz the register only understands 8 bits)
- so you take `10000000 00000000` and bitshift >> to get `00000000 100000000`
- the `& 0xFF` is "bitwise AND".  "return only the bits matching hex `FF` aka `11111111`; everything else zero out"
- so, the bitshifted `00000000 100000000` suddenly becomes `100000000`; 
- our second byte of the message is therefore `100000000`, or, set the last pin in the register HIGH.

So easy, right?

# performance considerations
Do you really need a 16x16 matrix...per side?...

Picture your typical 4x6 split keyboard...move both halves right next to each other.  Now double that.  Then double _that_ to get your new split keyboard.
That's how many keys you will have available in the matrix.

```
note: split was configured but not connected, boosting these numbers by 600-800
note: 1344 was our scan rate with 16 rows and 16 columns
removing 1 row: 1344 -> 1407 = +63 improvement
removing 2 rows:1344 -> 1532 = +188 improvement
removing 3 rows:1344 -> 1642 = +298 improvement
removing 4 rows:1344 -> 1759 = +415 improvement
removing 5 rows:1344 -> 1920 = +576 improvement
removing 6 rows:1344 -> 2100 = +756 improvement
removing 7 rows:1344 -> 2315 = +971 improvement
removing 8 rows:1344 -> 2580 = +1236 improvement -> 1675 (split costs 800)
```

However, rev1 was missing some fundamental wiring - ability to trigger register latch pins separately - and so we had to add in some code that slowed things down.
This is what kind of improvement we were looking at:
```
note: removing the rev1's preliminary SPI call: 2580 -> 3235 = +655 improvement
```

As a further note, the number of cols you have is much less relevant to performance.  All we are doing is a single `spi_receive` call which apparently is much less spendy than `spi_transmit`.

SO.  With 8 rows x 16 cols, you are 

Don't get carried away.

# configuring the shift registers

## info.json
All shift register pins are set as `NO_PIN`.  Ensure the row and col `NO_PIN` counts are correct for your usage.

e.g. 10x16 matrix.
```json
    "matrix_pins": {
        "custom_lite": true,
        "rows": ["NO_PIN", "NO_PIN", "NO_PIN", "NO_PIN", "NO_PIN", "NO_PIN", "NO_PIN", "NO_PIN", "NO_PIN", "NO_PIN"],
        "cols": ["NO_PIN", "NO_PIN", "NO_PIN", "NO_PIN", "NO_PIN", "NO_PIN", "NO_PIN", "NO_PIN", "NO_PIN", "NO_PIN", "NO_PIN", "NO_PIN", "NO_PIN", "NO_PIN", "NO_PIN", "NO_PIN"]
      },
```

## config.h - spi setup
todo: this will change once we get the latch pin involved.
```c
// SPI configuration
#define SPI_MATRIX_DIVISOR 16
#define SPI_MODE 0
#define SPI_DRIVER SPID1

#define SPI_SCK_PIN GP10
#define SPI_MOSI_PIN GP11
#define SPI_MISO_PIN GP12

#define SPI_MATRIX_CHIP_SELECT_PIN_ROWS GP9
#define SPI_MATRIX_CHIP_SELECT_PIN_COLS GP5

// two shift registers for rows(74HC595 write pin high), two for cols(74HC589 receive pin state)
#define MATRIX_COLS_SHIFT_REGISTER_COUNT 2
#define MATRIX_ROWS_SHIFT_REGISTER_COUNT 2
```


## config.h - matrix setup
This is pretty straightforward!  ... haha.
todo: try the old numbers method...


todo: replace rows_count
```c
#define ROWS_COUNT 10 // this can be replaced w. array_size or something?
#define ROWS { \
    0b0000000000000001, \
    0b0000000000000010, \
    0b0000000000000100, \
    0b0000000000001000, \
    0b0000000000010000, \
    0b0000000000100000, \
    0b0000000001000000, \
    0b0000000010000000, \
    0b0000000100000000, \
    0b0000001000000000, \
}
```

## keymap.c
This is where things get fishy.  Balancing the usage of all available cols to save row performance with the need for actual human beings to understand this.

