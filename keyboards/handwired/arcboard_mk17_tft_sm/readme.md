# handwired/arcboard_mk17_tft

A test keyboard for validating my quantum painter woes.

- 7789 TFT
- RP2040
- QP enabled

# Problem description
The code is attempting to draw a blue box on the screen.

Scan rate is atrociously bad (25) when executing `qp_rect` inside `housekeeping_task_kb`.
Uncommenting `qp_rect` immediately resolves the scan rate issues.

The issue presents when the SPI bus is shared with a PMW33xx device as well as when it is not.

# Hardware setup
Only the pins necessary for making the TFT work are used. 5v is supplied from VSYS to a power rail.  Ground rail from GND.
RST on GP0. 




                {"matrix": [12, 0], "x": 0, "y": 12},
                {"matrix": [12, 1], "x": 1, "y": 12},
                {"matrix": [12, 2], "x": 2, "y": 12},
                {"matrix": [12, 3], "x": 3, "y": 12},
                {"matrix": [12, 4], "x": 4, "y": 12},
                {"matrix": [12, 5], "x": 5, "y": 12},

                {"matrix": [13, 0], "x": 0, "y": 13},
                {"matrix": [13, 1], "x": 1, "y": 13},
                {"matrix": [13, 2], "x": 2, "y": 13},
                {"matrix": [13, 3], "x": 3, "y": 13},
                {"matrix": [13, 4], "x": 4, "y": 13},
                {"matrix": [13, 5], "x": 5, "y": 13},

                {"matrix": [14, 0], "x": 0, "y": 14},
                {"matrix": [14, 1], "x": 1, "y": 14},
                {"matrix": [14, 2], "x": 2, "y": 14},
                {"matrix": [14, 3], "x": 3, "y": 14},
                {"matrix": [14, 4], "x": 4, "y": 14},
                {"matrix": [14, 5], "x": 5, "y": 14},

                {"matrix": [15, 0], "x": 0, "y": 15},
                {"matrix": [15, 1], "x": 1, "y": 15},
                {"matrix": [15, 2], "x": 2, "y": 15},
                {"matrix": [15, 3], "x": 3, "y": 15},
                {"matrix": [15, 4], "x": 4, "y": 15},
                {"matrix": [15, 5], "x": 5, "y": 15},

                {"matrix": [16, 0], "x": 0, "y": 16},
                {"matrix": [16, 1], "x": 1, "y": 16},
                {"matrix": [16, 2], "x": 2, "y": 16},
                {"matrix": [16, 3], "x": 3, "y": 16},
                {"matrix": [16, 4], "x": 4, "y": 16},
                {"matrix": [16, 5], "x": 5, "y": 16},

                {"matrix": [17, 0], "x": 0, "y": 17},
                {"matrix": [17, 1], "x": 1, "y": 17},
                {"matrix": [17, 2], "x": 2, "y": 17},
                {"matrix": [17, 3], "x": 3, "y": 17},
                {"matrix": [17, 4], "x": 4, "y": 17},
                {"matrix": [17, 5], "x": 5, "y": 17},

                {"matrix": [18, 0], "x": 0, "y": 18},
                {"matrix": [18, 1], "x": 1, "y": 18},
                {"matrix": [18, 2], "x": 2, "y": 18},
                {"matrix": [18, 3], "x": 3, "y": 18},
                {"matrix": [18, 4], "x": 4, "y": 18},
                {"matrix": [18, 5], "x": 5, "y": 18},

                {"matrix": [19, 0], "x": 0, "y": 19},
                {"matrix": [19, 1], "x": 1, "y": 19},
                {"matrix": [19, 2], "x": 2, "y": 19},
                {"matrix": [19, 3], "x": 3, "y": 19},
                {"matrix": [19, 4], "x": 4, "y": 19},
                {"matrix": [19, 5], "x": 5, "y": 19},

                {"matrix": [20, 0], "x": 0, "y": 20},
                {"matrix": [20, 1], "x": 1, "y": 20},
                {"matrix": [20, 2], "x": 2, "y": 20},
                {"matrix": [20, 3], "x": 3, "y": 20},
                {"matrix": [20, 4], "x": 4, "y": 20},
                {"matrix": [20, 5], "x": 5, "y": 20},

                {"matrix": [21, 0], "x": 0, "y": 21},
                {"matrix": [21, 1], "x": 1, "y": 21},
                {"matrix": [21, 2], "x": 2, "y": 21},
                {"matrix": [21, 3], "x": 3, "y": 21},
                {"matrix": [21, 4], "x": 4, "y": 21},
                {"matrix": [21, 5], "x": 5, "y": 21},

                {"matrix": [22, 0], "x": 0, "y": 22},
                {"matrix": [22, 1], "x": 1, "y": 22},
                {"matrix": [22, 2], "x": 2, "y": 22},
                {"matrix": [22, 3], "x": 3, "y": 22},
                {"matrix": [22, 4], "x": 4, "y": 22},
                {"matrix": [22, 5], "x": 5, "y": 22},

                {"matrix": [23, 0], "x": 0, "y": 23},
                {"matrix": [23, 1], "x": 1, "y": 23},
                {"matrix": [23, 2], "x": 2, "y": 23},
                {"matrix": [23, 3], "x": 3, "y": 23},
                {"matrix": [23, 4], "x": 4, "y": 23},
                {"matrix": [23, 5], "x": 5, "y": 23}
