# Intro
_Note: This is mk15-era documentation, but still helpful._

'ledmaps' allow you to map your per-key RGB LED colours in the same fashion as how you map your keymaps.

This makes for a much nicer user experience (although still requires the ability to write some basic code) when maintaining your per-key mappings, and makes iteratively improving much more do-able - meaning you are much more inclined to actually try learning new keymaps, and fix your ergonomic burdens.

For example...this keymap...
```c
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT( \
      KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5,                        KC_6,    KC_7,    KC_8,   KC_9,    KC_0,    KC_EQUAL,
      KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T,                        KC_Y,    KC_U,    KC_I,   KC_O,    KC_P,    KC_MINUS,
      KC_LSFT, KC_A, KC_S, KC_D, KC_F, KC_G,                       KC_H,    KC_J,    KC_K,   KC_L,    KC_QUOT, KC_SCLN,
      KC_S, KC_Z, KC_X, KC_C, KC_V, KC_B,                          KC_N,    KC_M,    KC_COMM, KC_DOT, KC_SLASH, KC_Z,
            KC_1, KC_2, KC_3, KC_4, KC_5, KC_6,                    KC_1,    KC_2,    KC_3, KC_4, KC_5, KC_6,
            KC_LEFT, KC_RIGHT, KC_UP, KC_DOWN, KC_B, KC_F,         KC_LEFT, KC_RIGHT, KC_UP, KC_DOWN, KC_B, KC_F
)};
```
...has this ledmap...
```c
const ledmap ledmaps[] = {
    [_QWERTY] = LEDMAP( \
      CYAN, ___n___, ___n___, ___n___, ___n___, ___n___,           CYAN,    ___n___, ___n___, ___n___, ___n___,    CYAN,
      GOLD, ___n___, ___n___, HRM_CTL, ___n___, ___n___,           ___n___, ___n___, ___n___, ___n___, ___n___,    CYAN,
     GREEN, ___n___, HRM_ALT, HRM_GUI, HRM_SFT, ___n___,           ___n___, HRM_SFT, HRM_GUI, HRM_ALT, ___n___, ___n___,
      DRAG, ___n___, ___n___, ___n___, ___n___, ___n___,           ___n___, HRM_CTL, ___n___, ___n___, ___n___,     RED,
     SHIFT, ___n___,     ESC,     DEL, TOG_NAV,  BCKSPC,           ENTER,   SPACE,   SHIFT,   TOG_SYM, GREEN,   ___n___
)};
```


# History
I went through a path of doing things very wrongly that barely worked.
A while back, Dasky suggested Flags...and I was hesitant, because the docs say 'really should only use one flag type'.

Welp, flags.  That is the way.

# Flags
You can tag specific LEDs in your index and then loop over the array, doing stuff with X flag.

Limitation: there are only a few flags available for use...not sure if you can just put in whatever flag numbers you want...

# keyboard/keyboard.h
You need to match your key matrix layout with your ledmap layout, even if you have LED items that have no keys (e.g. indicator lights).

```c
#if defined(RGB_MATRIX_LEDMAPS_ENABLED)
    #include "rgb_ledmaps.h"
#endif

#define LAYOUT( \
    LM_11, LM_12, LM_13, LM_14, LM_15, LM_16,     RM_11, RM_12, RM_13, RM_14, RM_15, RM_16, \
    LM_21, LM_22, LM_23, LM_24, LM_25, LM_26,     RM_21, RM_22, RM_23, RM_24, RM_25, RM_26, \
    LM_31, LM_32, LM_33, LM_34, LM_35, LM_36,     RM_31, RM_32, RM_33, RM_34, RM_35, RM_36, \
    LM_41, LM_42, LM_43, LM_44, LM_45, LM_46,     RM_41, RM_42, RM_43, RM_44, RM_45, RM_46, \
    LT_51, LT_52, LT_53, LT_54, LT_55, LT_56,     RT_51, RT_52, RT_53, RT_54, RT_55, RT_56, \
    LT_61, LT_62, LT_63, LT_64, LT_65, LT_66,     RT_61, RT_62, RT_63, RT_64, RT_65, RT_66, \
    FL_01, FL_02, FL_03, FL_04, FL_05, FL_06,     FR_01, FR_02, FR_03, FR_04, FR_05, FR_06, \
    FL_07, FL_08, FL_09, FL_10, FL_11, FL_12,     FR_07, FR_08, FR_09, FR_10, FR_11, FR_12, \
    IL_01, IL_02, IL_03, IL_04, IL_05, IL_06,     IR_01, IR_02, IR_03, IR_04, IR_05, IR_06, \
    IL_07, IL_08, IL_09, IL_10, IL_11, IL_12,     IR_07, IR_08, IR_09, IR_10, IR_11, IR_12, \
    IL_13, IL_14,                                 IR_13, IR_14 \
) \
{ \
    { LM_11, LM_12, LM_13, LM_14, LM_15, LM_16 }, \
    { LM_21, LM_22, LM_23, LM_24, LM_25, LM_26 }, \
    { LM_31, LM_32, LM_33, LM_34, LM_35, LM_36 }, \
    { LM_41, LM_42, LM_43, LM_44, LM_45, LM_46 }, \
    { LT_51, LT_52, LT_53, LT_54, LT_55, LT_56 }, \
    { LT_61, LT_62, LT_63, LT_64, LT_65, LT_66 }, \
    { FL_01, FL_02, FL_03, FL_04, FL_05, FL_06 }, \
    { FL_07, FL_08, FL_09, FL_10, FL_11, FL_12 }, \
    { IL_01, IL_02, IL_03, IL_04, IL_05, IL_06 }, \
    { IL_07, IL_08, IL_09, IL_10, IL_11, IL_12 }, \
    { IL_13, IL_14 }, \
    { RM_11, RM_12, RM_13, RM_14, RM_15, RM_16 }, \
    { RM_21, RM_22, RM_23, RM_24, RM_25, RM_26 }, \
    { RM_31, RM_32, RM_33, RM_34, RM_35, RM_36 }, \
    { RM_41, RM_42, RM_43, RM_44, RM_45, RM_46 }, \
    { RT_51, RT_52, RT_53, RT_54, RT_55, RT_56 }, \
    { RT_61, RT_62, RT_63, RT_64, RT_65, RT_66 }, \
    { FR_01, FR_02, FR_03, FR_04, FR_05, FR_06 }, \
    { FR_07, FR_08, FR_09, FR_10, FR_11, FR_12 }, \
    { IR_01, IR_02, IR_03, IR_04, IR_05, IR_06 }, \
    { IR_07, IR_08, IR_09, IR_10, IR_11, IR_12 }, \
    { IR_13, IR_14 }, \
}
```

# keyboard/keyboard.c
The `g_led_config` helps you map the electrical layout, the led-to-physical layout, and the led index flags.
## electrical layout
This is where you can ensure that led/no-led is correctly laid out.  The index is based on this electrical layout, sans gaps.
```c
{
    { 0,  1,  2,  3,  4,  5  }, // per-key LEDs
    { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED }, // e.g. a 5-way switch (up, down, left right, button, nothing hooked up)
    { 6,  7,  8,  9,  10, 11 } // more per-key LEDs
}
```

## led-to-physical layout
This is used for animations.  I don't use them, so no more said here.
Basically you can ensure that keys that are oddly arranged still map nicely to animation patterns (i.e. avoiding animation distortion).

It needs to be there and be populated (matching the index count) to compile.

## led index flags
The WS2818 wiring is: GPIO pin -> key1-DI -> key1-DO -> key2-DI -> etc
What flags allow you to do is specify: -> key-led -> key-led -> indicator-led -> indicator-led

**In the ledmap context, you don't map any non-per-key-led flagged LEDs in the index.**
They get skipped w. `___n___` and then your logic in 

Which means you can do neato stuff like...
```c
bool is_shifted = (get_mods() | get_weak_mods()) & MOD_MASK_SHIFT;
if (is_shifted) {
    for (uint8_t i = led_min; i < led_max; i++) {
        if (HAS_FLAGS(g_led_config.flags[i], 0x08)) {
            set_rgb_led(i, HSV_GREEN);
        }
    }
} else {
    for (uint8_t i = led_min; i < led_max; i++) {
        if (HAS_FLAGS(g_led_config.flags[i], 0x08)) {
            set_rgb_led(i, HSV_CYAN);
        }
    }
}
```

# keyboard/config.h
Breaking the config down...
- RGB_DI_PIN: The GPIO pin your WS2818 index starts from.
- RGBLED_NUM: Total count of LEDs in your index
- RGB_MATRIX_SPLIT: Sometimes you don't have an even split, this is how you manage that.
- RGB_MATRIX_MAXIMUM_BRIGHTNESS: Set the maximum brightness the HSV stuff will use, aka your HS_V_
- RGB_MATRIX_DEFAULT_HUE/SAT: Pick your 'default' LED colour.  I use white.

```c
// WS2812 RGB LED strip input and number of LEDs
#if defined(RGB_MATRIX_ENABLE) || defined(RGB_MATRIX_LEDMAPS_ENABLED)
    #define RGB_DI_PIN GP28
    #define RGBLED_NUM 112                       // Total number of LEDs, total of both halves
    #define RGB_MATRIX_SPLIT { 56, 56 }
    #define RGB_MATRIX_LED_COUNT RGBLED_NUM

    // this brightness is only for 'default' rgb settings; userspace rgb is set in the keymap config.h
    #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 50 // this has no effect unless you eeprom reset  // setting this too high will cause the trackball to reset every min or so, and at highest just brownout entirely
    #define RGB_MATRIX_DEFAULT_HUE 5
    #define RGB_MATRIX_DEFAULT_SAT 5
    #define RGB_MATRIX_DEFAULT_VAL RGB_MATRIX_MAXIMUM_BRIGHTNESS
    #define NOP_FUDGE 0.4                       // not sure what this does - some math about rgb brightness or something? - but it won't compile without this set
#endif
```
# keyboard/rules.mk
The ifeq part maybe is not required...

```c
# Split settings
SPLIT_KEYBOARD 				= yes

# LED settings
RGB_MATRIX_ENABLE 		= yes 		# matrix enable turns on the "background" lighting
RGB_MATRIX_LEDMAPS_ENABLED = yes 	# turn on per-key colours
RGB_MATRIX_DRIVER 		= WS2812
WS2812_DRIVER 			= vendor  	# RP2040 lyfe

ifeq ($(strip $(RGB_MATRIX_ENABLE)), yes)
	OPT_DEFS += -DRGB_MATRIX_ENABLE
endif
```

# keyboard/keymaps/my_keymap/rules.mk
Need to ensure you include the ledmaps extra files!

```c
ifeq ($(strip $(RGB_MATRIX_LEDMAPS_ENABLED)), yes)
	SRC += keymaps/my_keymap/rgb_ledmaps.c
	OPT_DEFS += -DRGB_MATRIX_LEDMAPS_ENABLED
endif
```

# keyboard/keymaps/my_keymap/keymap.c
Here is a working ledmap.
```c
const ledmap ledmaps[] = {
    [_QWERTY]   = LEDMAP(
      CYAN, ___n___, ___n___, ___n___, ___n___, ___n___,           CYAN, ___n___, ___n___, ___n___, ___n___,    CYAN,
      GOLD, ___n___, ___n___, HRM_CTL, ___n___, ___n___,           ___n___, ___n___, ___n___, ___n___, ___n___,    CYAN,
     GREEN, ___n___, HRM_ALT, HRM_GUI, HRM_SFT, ___n___,           ___n___, HRM_SFT, HRM_GUI, HRM_ALT, ___n___, ___n___,
      DRAG, ___n___, ___n___, ___n___, ___n___, ___n___,           ___n___, HRM_CTL, ___n___, ___n___, ___n___,     RED,
     SHIFT, ___n___,     ESC,     DEL, TOG_NAV,  BCKSPC,           ENTER, SPACE, SHIFT, TOG_SYM, GREEN,___n___,
     FL_L0, FL_L0, FL_L0, FL_L0, FL_L0, FL_L0,                           FR_L0, FR_L0, FR_L0, FR_L0, FR_L0, FR_L0,
     FL_L0, FL_L0, FL_L0, FL_L0, FL_L0, FL_L0,                           FR_L0, FR_L0, FR_L0, FR_L0, FR_L0, FR_L0,
     ___n___, ___n___, ___n___, ___n___, ___n___, ___n___,         ___n___, ___n___, ___n___, ___n___, ___n___, ___n___,
     ___n___, ___n___, ___n___, ___n___, ___n___, ___n___,         ___n___, ___n___, ___n___, ___n___, ___n___, ___n___,
     ___n___, ___n___,                                             ___n___, ___n___
   ),
   etc
}
```
Some details...
- note that both sides are captured in one map
- ___n___ is used as a placeholder to basically 'do nothing' (cuz rgb_matrix can't handle 0,0,0 being passed as an HSV value, so it effectively skips that item)
  - is there a better way?  probably.
- the FL_L0/FR_L0 is where the Falcon LEDs (12 per) are mapped out.  you can exclude them from the map by adding flags.
- the use of macros (aliases?) to make the maps more relatable to the keymaps

# keyboard/keymaps/my_keymap/rgb_ledmap.h
In this header file we define the way the ledmap array is configured.
Note...
- You can see here how the sides are mapped... in the first part of the LEDMAP, it's 'what you pass in from the ledmap', i.e. Left,Right,Left,Right,etc
- In the second part, in braces, you see the led index mapping: Left,Left,Left,Right,Right,Right,etc
  - Why?  Because the split code splits the led index in half!

```c
#define LEDMAP( \
    LM_11, LM_12, LM_13, LM_14, LM_15, LM_16,     RM_11, RM_12, RM_13, RM_14, RM_15, RM_16, \
    LM_21, LM_22, LM_23, LM_24, LM_25, LM_26,     RM_21, RM_22, RM_23, RM_24, RM_25, RM_26, \
    LM_31, LM_32, LM_33, LM_34, LM_35, LM_36,     RM_31, RM_32, RM_33, RM_34, RM_35, RM_36, \
    LM_41, LM_42, LM_43, LM_44, LM_45, LM_46,     RM_41, RM_42, RM_43, RM_44, RM_45, RM_46, \
    LT_51, LT_52, LT_53, LT_54, LT_55, LT_56,     RT_51, RT_52, RT_53, RT_54, RT_55, RT_56, \
    FL_01, FL_02, FL_03, FL_04, FL_05, FL_06,     FR_01, FR_02, FR_03, FR_04, FR_05, FR_06, \
    FL_07, FL_08, FL_09, FL_10, FL_11, FL_12,     FR_07, FR_08, FR_09, FR_10, FR_11, FR_12, \
    IL_01, IL_02, IL_03, IL_04, IL_05, IL_06,     IR_01, IR_02, IR_03, IR_04, IR_05, IR_06, \
    IL_07, IL_08, IL_09, IL_10, IL_11, IL_12,     IR_07, IR_08, IR_09, IR_10, IR_11, IR_12, \
    IL_13, IL_14,                                 IR_13, IR_14 \
) { \
    LM_11, LM_12, LM_13, LM_14, LM_15, LM_16, \
    LM_21, LM_22, LM_23, LM_24, LM_25, LM_26, \
    LM_31, LM_32, LM_33, LM_34, LM_35, LM_36, \
    LM_41, LM_42, LM_43, LM_44, LM_45, LM_46, \
    LT_51, LT_52, LT_53, LT_54, LT_55, LT_56, \
    FL_01, FL_02, FL_03, FL_04, FL_05, FL_06, \
    FL_07, FL_08, FL_09, FL_10, FL_11, FL_12, \
    IL_01, IL_02, IL_03, IL_04, IL_05, IL_06, \
    IL_07, IL_08, IL_09, IL_10, IL_11, IL_12, \
    IL_13, IL_14, \
    RM_11, RM_12, RM_13, RM_14, RM_15, RM_16, \
    RM_21, RM_22, RM_23, RM_24, RM_25, RM_26, \
    RM_31, RM_32, RM_33, RM_34, RM_35, RM_36, \
    RM_41, RM_42, RM_43, RM_44, RM_45, RM_46, \
    RT_51, RT_52, RT_53, RT_54, RT_55, RT_56, \
    FR_01, FR_02, FR_03, FR_04, FR_05, FR_06, \
    FR_07, FR_08, FR_09, FR_10, FR_11, FR_12, \
    IR_01, IR_02, IR_03, IR_04, IR_05, IR_06, \
    IR_07, IR_08, IR_09, IR_10, IR_11, IR_12, \
    IR_13, IR_14 \
}

// ledmap is an array of [this many LEDs in the index] by [ H, S, V ]
typedef uint8_t ledmap[RGB_MATRIX_LED_COUNT][3];

// extern cuz other files need to use this
extern const ledmap ledmaps[];

// you can pass in the index start, index end, brightness value, and layer number
void set_rgb_range(uint8_t led_start, uint8_t led_last, int val, int layer);
```

# keyboard/keymaps/my_keymap/rgb_ledmap.c
And this is the function that actually references the above ledmap... (I did not write this! just tweaked a bit.)
```c
void set_rgb_range(uint8_t led_min, uint8_t led_max, int val, int layer) {
    const ledmap *l = &(ledmaps[layer]);
    for (int i = led_min; i <= led_max; i++) {
        HSV hsv = {
            .h = (*l)[i][0],
            .s = (*l)[i][1],
            .v = val,
        };
        if (hsv.h || hsv.s) {
            RGB rgb = hsv_to_rgb(hsv);
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        }
    }
}

// And the 'non-ledmap' LED function (as of this writing there is no 'set_hsv_led' available)
void set_rgb_led(int index, int hue, int sat, int val) {
    HSV hsv = {
        .h = hue,
        .s = sat,
        .v = rgb_matrix_get_val(),
    };
    if (hsv.h || hsv.s) {
        RGB rgb = hsv_to_rgb(hsv);
        rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
    }
}

// Now call our functions to set the LEDs...
bool rgb_matrix_indicators_user(void) { return rgb_matrix_indicators_keymap(); }
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {

    // rgb_matrix_get_val gets our global brightness value
    set_rgb_range(led_min, led_max, rgb_matrix_get_val(), get_highest_layer(layer_state | default_layer_state));
    
    // and here you would set flag stuff
    bool is_shifted = (get_mods() | get_weak_mods()) & MOD_MASK_SHIFT;
    if (is_shifted) {
        for (uint8_t i = led_min; i < led_max; i++) {
            if (HAS_FLAGS(g_led_config.flags[i], 0x08)) {
                set_rgb_led(i, HSV_GREEN);
            }
        }
    } else {
        for (uint8_t i = led_min; i < led_max; i++) {
            if (HAS_FLAGS(g_led_config.flags[i], 0x08)) {
                set_rgb_led(i, HSV_CYAN);
            }
        }
    }

    return rgb_matrix_indicators_advanced_keymap(led_min, led_max);
}
```
