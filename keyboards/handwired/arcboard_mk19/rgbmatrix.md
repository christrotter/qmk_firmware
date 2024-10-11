# day1 - understanding cyboard's rgb logic
So i'm used to DI -> DO -> DI etc, and working across in rows.

But Cyboard is physically arranged in columns, so of course it'd be different.
```c
{"flags": 4, "matrix": [3, 0], "x": 86, "y": 32},
{"flags": 4, "matrix": [2, 0], "x": 86, "y": 43},
{"flags": 4, "matrix": [6, 0], "x": 86, "y": 0},
{"flags": 4, "matrix": [5, 0], "x": 86, "y": 11},
{"flags": 4, "matrix": [4, 0], "x": 86, "y": 21
{"flags": 4, "matrix": [3, 1], "x": 69, "y": 32},
{"flags": 4, "matrix": [2, 1], "x": 69, "y": 43},
{"flags": 4, "matrix": [6, 1], "x": 69, "y": 0},
{"flags": 4, "matrix": [5, 1], "x": 69, "y": 11},
{"flags": 4, "matrix": [4, 1], "x": 69, "y": 21
{"flags": 4, "matrix": [3, 2], "x": 52, "y": 32},
{"flags": 4, "matrix": [2, 2], "x": 52, "y": 43},
{"flags": 4, "matrix": [1, 2], "x": 52, "y": 53},
{"flags": 4, "matrix": [6, 2], "x": 52, "y": 0},
{"flags": 4, "matrix": [5, 2], "x": 52, "y": 11},
{"flags": 4, "matrix": [4, 2], "x": 52, "y": 21},
```

info.json has a rgbmatrix/layout section - this is the replacement for g_led_config.

but, ledmaps are different somehow...
how do ledmaps interact with the led config?

```c
#define LEDMAP( \
    LM_11, LM_12, LM_13, LM_14, LM_15, LM_16,     RM_11, RM_12, RM_13, RM_14, RM_15, RM_16, \
    LM_21, LM_22, LM_23, LM_24, LM_25, LM_26,     RM_21, RM_22, RM_23, RM_24, RM_25, RM_26, \
    LM_31, LM_32, LM_33, LM_34, LM_35, LM_36,     RM_31, RM_32, RM_33, RM_34, RM_35, RM_36, \
    LM_41, LM_42, LM_43, LM_44, LM_45, LM_46,     RM_41, RM_42, RM_43, RM_44, RM_45, RM_46, \
    LT_51, LT_52, LT_53, LT_54, LT_55, FL_B0,     RT_51, RT_52, RT_53, RT_54, RT_55, FL_B2, \
    DP_01, DP_02, DP_03, DP_04, DP_05, FL_B1,     DP_11, DP_12, DP_13, DP_14, DP_15, FL_B3 \
) { \
    LM_11, LM_12, LM_13, LM_14, LM_15, LM_16, \
    LM_21, LM_22, LM_23, LM_24, LM_25, LM_26, \
    LM_31, LM_32, LM_33, LM_34, LM_35, LM_36, \
    LM_41, LM_42, LM_43, LM_44, LM_45, LM_46, \
    LT_51, LT_52, LT_53, LT_54, LT_55, FL_B0, \
    DP_01, DP_02, DP_03, DP_04, DP_05, FL_B1, \
    RM_11, RM_12, RM_13, RM_14, RM_15, RM_16, \
    RM_21, RM_22, RM_23, RM_24, RM_25, RM_26, \
    RM_31, RM_32, RM_33, RM_34, RM_35, RM_36, \
    RM_41, RM_42, RM_43, RM_44, RM_45, RM_46, \
    RT_51, RT_52, RT_53, RT_54, RT_55, FL_B2, \
    DP_11, DP_12, DP_13, DP_14, DP_15, FL_B3 \
}
```

the ledmap function:
```c
const ledmap *l = &(ledmaps[layer]);
        HSV hsv = {
            .h = (*l)[i][0],
            .s = (*l)[i][1],
            .v = val,
        };
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);

// and it gets called:
bool rgb_matrix_indicators_user() {
    if (is_keyboard_left()) {
        // set LEFT per-key leds by ledmap
        set_rgb_ledmap(RGB_KEYS_L_MIN, RGB_KEYS_L_MAX, rgb_matrix_get_val(), get_highest_layer(layer_state | default_layer_state));
    } else {
        // set RIGHT per-key leds by ledmap
        set_rgb_ledmap(RGB_KEYS_R_MIN, RGB_KEYS_R_MAX, rgb_matrix_get_val(), get_highest_layer(layer_state | default_layer_state));
    }
    return true;
}
```
all the ledmap function is doing is taking the first_led and last_led values and looping over that span, one by one, and setting hsv->rgb.

and b/c we're calling that inside a normally-looped function, that's how our state is set.

keymap.c calls it:
`const ledmap ledmaps[] = {`
so the keymap is basically saying, hey, when you are doing your colour lookups, here's your colour lookup table.

which means, the ledmap is an analogue to the keymap.  IF.   the keymap is also an ordered thing, i.e. if the keymap ordering and led index ordering is the same.

but ours is not.  so this code will not work, and this explains why things are all wonky.


So what needs to change?

Maybe this is where the rgb matrix index fits in...  it'll be fine if we specify where in the matrix the led is, in our sequential order?

# day2 - figuring out how info.json/rgb_matrix/layout is supposed to work
so, if the ledmap is just 0,1,2,3 execution, i.e. a sequential led execution...
info.json should also be laid out in the sequence of the ws2818 chain.

GOT IT.

## summary
- there is led_start and led_end in config.h; for the custom functions
- info.json is now effectively doing g_led_config stuff
- the LEDMAP object needed to be re-oriented as well

the rows are all reversed.

i tried reversing one col in info.json - no change.

reversed the row order in the first part of the ledmap...reversed!
that did it!!

ok, last two led items.
- layers
- thumbcluster kc_no

Both working.

need to really dig into how this is all set up, but, it's working!  \o/

