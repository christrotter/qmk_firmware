# this is how to use led config

Cyboard's layout makes this hard, and g_led_config makes it harder.  This doc will try to explain how it all works.

## expected results
we're trying to have this work
1. led signal out of mcu via flex pcb
2. led into cyboard column structure
3. led out of cyboard columns into thumb keys
4. led out of flex cable back to pcb; to macro keys
5. led out of macro keys back to pcb; to UF1
6. led out of UF1 to UF2
7. led out of UF2 to keybar strip

however, only steps 1 to 4 need to be in 'per key ledmaps'.

so we really need to map our cyboard system (keywell, thumbs) and macro keys set up.

## config.h
this sets our led index ranges
```c
    // these are used for properly handling the gaps in the led index for "non-ledmap" leds
    // e.g. "count: ledmap leds - left" + RGB_TOT_IND_L + "count: ledmap leds - right" + RGB_TOT_IND_R = total led index size
    #define RGB_TOT_IND_L 72
    #define RGB_TOT_IND_R 72
    // 'KEYS' is our cyboard 36 keys + 8 macro keys = 44, thus 0-43
    #define RGB_KEYS_L_START 0
    #define RGB_KEYS_L_END 43
    // UF1/UF2 are the two ultrafalcons, inner ring and outer ring
    #define RGB_UF1_INNER_L_START 44
    #define RGB_UF1_INNER_L_END 49
    #define RGB_UF1_OUTER_L_START 50
    #define RGB_UF1_OUTER_L_END 73
    #define RGB_UF2_INNER_L_START 74
    #define RGB_UF2_INNER_L_END 79
    #define RGB_UF2_OUTER_L_START 80
    #define RGB_UF2_OUTER_L_END 103
    // INDICATOR = keybar...i should rename this... the 5 leds in the led strip above keywell
    #define RGB_INDICATOR_L_START 104
    #define RGB_INDICATOR_L_END 108
    // right side, same thing
    #define RGB_KEYS_R_START 109
    #define RGB_KEYS_R_END 152
    #define RGB_UF1_INNER_R_START 153
    #define RGB_UF1_INNER_R_END 158
    #define RGB_UF1_OUTER_R_START 159
    #define RGB_UF1_OUTER_R_END 182
    #define RGB_UF2_INNER_R_START 183
    #define RGB_UF2_INNER_R_END 188
    #define RGB_UF2_OUTER_R_START 189
    #define RGB_UF2_OUTER_R_END 212
    #define RGB_INDICATOR_R_START 213
    #define RGB_INDICATOR_R_END 217
```

For the per-key ledmap stuff, we only ever deal with `KEYS`.

## how the ranges are called
```c
bool rgb_matrix_indicators_user() {
    if (is_keyboard_left()) {
        set_rgb_ledmap(RGB_KEYS_L_START, RGB_KEYS_L_END, rgb_matrix_get_val(), get_highest_layer(layer_state | default_layer_state));
    } else {
        set_rgb_ledmap(RGB_KEYS_R_START, RGB_KEYS_R_END, rgb_matrix_get_val(), get_highest_layer(layer_state | default_layer_state));
    }
    return true;
}
```

This is that function.  Important here is that we are passing in the layer ledmap index.
```c
void set_rgb_ledmap(uint16_t first_led, uint16_t last_led, int val, int layer) {
    const ledmap *l = &(ledmaps[layer]);
    for (int i = first_led; i <= last_led; i++) {
        // RGB_TOT_IND_L is 'how many right indicator leds between left and right key ranges, in the context of the led-flag section of g_led_config'
        // cuz, ledmaps doesn't think there are any indicator leds, it believes you only have l.key-range + r.key-range = total addressable leds
        if (!(is_keyboard_left())) {
            i = i - RGB_TOT_IND_L;
        }
        HSV hsv = {
            .h = (*l)[i][0],
            .s = (*l)[i][1],
            .v = val,
        };
        if (!(is_keyboard_left())) {
            i = i + RGB_TOT_IND_L;
        } // revert i to fit the 'in reality' led sequence
        if (hsv.h || hsv.s) {
            RGB rgb = hsv_to_rgb(hsv);
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        }
    }
}
```

A ledmap is defined like this:
```c
#define LEDMAP( \
    L_50, L_51, L_52, L_53, L_54, L_55,                             R_50, R_51, R_52, R_53, R_54, R_55, \
    L_40, L_41, L_42, L_43, L_44, L_45,                             R_40, R_41, R_42, R_43, R_44, R_45, \
    L_30, L_31, L_32, L_33, L_34, L_35,                             R_30, R_31, R_32, R_33, R_34, R_35, \
    L_20, L_21, L_22, L_23, L_24, L_25,                             R_20, R_21, R_22, R_23, R_24, R_25, \
    L_10, L_11, L_12, L_13, L_14, L_15,                             R_10, R_11, R_12, R_13, R_14, R_15, \
    L_00, L_01, L_02, L_03, L_04, L_05,                             R_00, R_01, R_02, R_03, R_04, R_05, \
    L_36, L_37, L_38, L_39, L_26, L_27, L_28, L_29,                 R_36, R_37, R_38, R_39, R_26, R_27, R_28, R_29 \
) { \
    L_30, L_20, L_10, L_50, L_40, \
    L_31, L_21, L_11, L_51, L_41, \
    L_32, L_22, L_12, L_52, L_42, \
    L_33, L_23, L_13, L_53, L_43, \
    L_34, L_24, L_14, L_54, L_44, \
    L_35, L_25, L_15, L_55, L_45, \
    L_00, L_01, L_02, L_03, L_04, L_05, \
    L_36, L_37, L_38, L_39, L_26, L_27, L_28, L_29, \
    R_30, R_20, R_10, R_50, R_40, \
    R_31, R_21, R_11, R_51, R_41, \
    R_32, R_22, R_12, R_52, R_42, \
    R_33, R_23, R_13, R_53, R_43, \
    R_34, R_24, R_14, R_54, R_44, \
    R_35, R_25, R_15, R_55, R_45, \
    R_00, R_01, R_02, R_03, R_04, R_05, \
    R_36, R_37, R_38, R_39, R_26, R_27, R_28, R_29, \
}
typedef uint8_t ledmap[RGB_MATRIX_LED_COUNT][3];
extern const ledmap ledmaps[];
```

but, very importantly...the cyboard system doesn't work in rows/cols.  this is their `info.json/rgb-matrix` section.
```json
{"flags": 4, "matrix": [2, 1], "x": 86, "y": 43}, // not quite sure what this is
{"flags": 4, "matrix": [3, 1], "x": 86, "y": 32},
{"flags": 4, "matrix": [4, 1], "x": 86, "y": 21},
{"flags": 4, "matrix": [5, 1], "x": 86, "y": 11},
{"flags": 4, "matrix": [6, 1], "x": 86, "y": 0},
{"flags": 4, "matrix": [1, 1], "x": 86, "y": 53},
{"flags": 4, "matrix": [1, 0], "x": 103, "y": 53},
{"flags": 4, "matrix": [0, 0], "x": 103, "y": 64}, // thumb keys here
{"flags": 4, "matrix": [0, 1], "x": 86, "y": 64},
{"flags": 4, "matrix": [0, 2], "x": 69, "y": 64},
{"flags": 4, "matrix": [1, 2], "x": 69, "y": 53},  // cols start here
{"flags": 4, "matrix": [2, 2], "x": 69, "y": 43},
{"flags": 4, "matrix": [3, 2], "x": 69, "y": 32},
{"flags": 4, "matrix": [4, 2], "x": 69, "y": 21},
{"flags": 4, "matrix": [5, 2], "x": 69, "y": 11},
{"flags": 4, "matrix": [6, 2], "x": 69, "y": 0},
{"flags": 4, "matrix": [1, 3], "x": 52, "y": 53},
{"flags": 4, "matrix": [2, 3], "x": 52, "y": 43},
{"flags": 4, "matrix": [3, 3], "x": 52, "y": 32},
{"flags": 4, "matrix": [4, 3], "x": 52, "y": 21},
{"flags": 4, "matrix": [5, 3], "x": 52, "y": 11},
{"flags": 4, "matrix": [6, 3], "x": 52, "y": 0},
{"flags": 4, "matrix": [1, 4], "x": 34, "y": 53},
{"flags": 4, "matrix": [2, 4], "x": 34, "y": 43},
{"flags": 4, "matrix": [3, 4], "x": 34, "y": 32},
{"flags": 4, "matrix": [4, 4], "x": 34, "y": 21},
{"flags": 4, "matrix": [5, 4], "x": 34, "y": 11},
{"flags": 4, "matrix": [6, 4], "x": 34, "y": 0},
{"flags": 4, "matrix": [1, 5], "x": 17, "y": 53},
{"flags": 4, "matrix": [2, 5], "x": 17, "y": 43},
{"flags": 4, "matrix": [3, 5], "x": 17, "y": 32},
{"flags": 4, "matrix": [4, 5], "x": 17, "y": 21},
{"flags": 4, "matrix": [5, 5], "x": 17, "y": 11},
{"flags": 4, "matrix": [6, 5], "x": 17, "y": 0},
{"flags": 4, "matrix": [1, 6], "x": 0, "y": 53},
{"flags": 4, "matrix": [2, 6], "x": 0, "y": 43},
{"flags": 4, "matrix": [3, 6], "x": 0, "y": 32},
{"flags": 4, "matrix": [4, 6], "x": 0, "y": 21},
{"flags": 4, "matrix": [5, 6], "x": 0, "y": 11},
{"flags": 4, "matrix": [6, 6], "x": 0, "y": 0},  // this half done, more for next half
```

For our purposes, that ordering is actually incorrect.  You'd think it is this...
```
{"flags": 4, "matrix": [1, 2], "x": 69, "y": 53},  // row1, col2
{"flags": 4, "matrix": [2, 2], "x": 69, "y": 43},  // row2, col2
{"flags": 4, "matrix": [3, 2], "x": 69, "y": 32},  // row3, col2
{"flags": 4, "matrix": [4, 2], "x": 69, "y": 21},  // row4, col2
{"flags": 4, "matrix": [5, 2], "x": 69, "y": 11},  // row5, col2
```
but the actual pcb layout is this:
```
{"flags": 4, "matrix": [3, 2], "x": 69, "y": 32},  // row3, col2
{"flags": 4, "matrix": [2, 2], "x": 69, "y": 43},  // row2, col2
{"flags": 4, "matrix": [1, 2], "x": 69, "y": 53},  // row1, col2
{"flags": 4, "matrix": [4, 2], "x": 69, "y": 21},  // row4, col2
{"flags": 4, "matrix": [5, 2], "x": 69, "y": 11},  // row5, col2
```

Thus we have:
```json
{"flags": 4, "matrix": [3, 0], "x": 0, "y": 0},
{"flags": 4, "matrix": [2, 0], "x": 0, "y": 0},
{"flags": 4, "matrix": [1, 0], "x": 0, "y": 0}, 
{"flags": 4, "matrix": [5, 0], "x": 0, "y": 0},
{"flags": 4, "matrix": [4, 0], "x": 0, "y": 0},
{"flags": 4, "matrix": [3, 1], "x": 1, "y": 0},
{"flags": 4, "matrix": [2, 1], "x": 1, "y": 0},
{"flags": 4, "matrix": [1, 1], "x": 1, "y": 0},
{"flags": 4, "matrix": [5, 1], "x": 1, "y": 0},
{"flags": 4, "matrix": [4, 1], "x": 1, "y": 0},
```
Now if you mess with the ordering at all, you get sadness.  And the counts of the gap makes things sad.
Using the handedness reversal config, testing shows the first portion of the config is 100% accurate aside from thumbs ordering.

So our issue is not:
- the info/led config
- the ledmap layout config
- the basic col ranges

This means the gap is causing grief.
