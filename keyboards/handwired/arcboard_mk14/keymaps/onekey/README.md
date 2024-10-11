# misc



# Onekey experiment

The goal of this onekey board was to learn from Dasky and experiment more cheaply.

I needed to address specific sections of a WS2018 LED string, but rgbmatrix on its own only has utility for led_min/led_max.
Further, I wanted to keep the "ledmap" functionality because it makes customizing things so much easier down the line.

preface: I have no comprehension of how file includes (SRC) are different from keyboard.h/keymap.c

The ledmaps allow you to have an ascii-diagram/table of your physical keymap for led colours, the same way you do for key matrix assignment.


This for loop bug, jeepers.
```c
const ledmap *l = &(ledmapname[layer]);
uint8_t val = rgb_matrix_get_val();
for (int i = led_start; i <= led_last; i++) {
    HSV hsv = {
        .h = (*l)[i][0],
        .s = (*l)[i][1],
        .v = val,

    if (hsv.h || hsv.s) {
        RGB rgb = hsv_to_rgb(hsv);
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }
}
// compared to...
uint8_t val = rgb_matrix_get_val();
int i = 0;
HSV hsv = {
    .h = (ind2ledmaps[layer])[i][0],
    .s = (ind2ledmaps[layer])[i][1],
    .v = val,
};
RGB rgb = hsv_to_rgb(hsv); // something in here was blowing up the i count
for (int i = led_start; i <= led_last; i++) {
    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
}
// the latter loop works fine; something in the HSV conversion was causing 'i' to get set in wacky ways, e.g.
//Chris Trotter:handwired/arcboard_mk13:1: For 0:0:2, setting: 0 to: 23,0,0
//Chris Trotter:handwired/arcboard_mk13:1: For 0:0:2, setting: 1 to: 22,23,0
//Chris Trotter:handwired/arcboard_mk13:1: For 0:0:2, setting: 2 to: 0,0,23
//Chris Trotter:handwired/arcboard_mk13:1: For 4:3:4, setting: 3 to: 22,23,0
//Chris Trotter:handwired/arcboard_mk13:1: For 4:3:4, setting: 4 to: 22,23,0 // and then it just skips led5
//Chris Trotter:handwired/arcboard_mk13:1: For 5:5:6, setting: 6 to: 23,11,0
//
//Chris Trotter:handwired/arcboard_mk13:1: setting keys rgb range
//Chris Trotter:handwired/arcboard_mk13:1: For: 0 Loop start: 0 Loop end: 2
//Chris Trotter:handwired/arcboard_mk13:1: For 0:0:2, setting: 0 to: 23,0,0
//Chris Trotter:handwired/arcboard_mk13:1: For 0:0:2, setting: 1 to: 22,23,0
//Chris Trotter:handwired/arcboard_mk13:1: For 0:0:2, setting: 2 to: 0,0,23
//Chris Trotter:handwired/arcboard_mk13:1: setting ind1 rgb range
//Chris Trotter:handwired/arcboard_mk13:1: For: 5 Loop start: 3 Loop end: 4
//Chris Trotter:handwired/arcboard_mk13:1: For 5:3:4, setting: 3 to: 0,23,0
//Chris Trotter:handwired/arcboard_mk13:1: For 5:3:4, setting: 4 to: 0,23,0
//Chris Trotter:handwired/arcboard_mk13:1: setting ind2 rgb range to: 4 / 6 / 5
//Chris Trotter:handwired/arcboard_mk13:1: For: 6 Loop start: 4 Loop end: 6
//Chris Trotter:handwired/arcboard_mk13:1: For 6:4:6, setting: 4 to: 23,11,0 // entirely refusing to set 5???
//Chris Trotter:handwired/arcboard_mk13:1: For 6:4:6, setting: 6 to: 11,0,23
// other times it would blow up and pull from the previous layer definitions.
```



// line 44:23 is the 'ledmapname': const ledmap *l = &(ledmapname[layer]);
./keyboards/handwired/arcboard_mk14/keymaps/onekey/keymap.c:44:23: 
error: initialization of 
'const uint8_t (*)[3][3]' {aka 'const unsigned char (*)[3][3]'} 
from incompatible pointer type 
'uint8_t (*)[3]' {aka 'unsigned char (*)[3]'} [-Werror=incompatible-pointer-types]
     const ledmap *l = &(ledmapname[layer]);

// line 43:75 is the 'ledmapname' in the function input list: void set_rgb_range(uint8_t led_start, uint8_t led_last, int layer, ledmap ledmapname) {
./keyboards/handwired/arcboard_mk14/keymaps/onekey/keymap.c:43:75: 
note: expected 
'uint8_t (*)[3]' {aka 'unsigned char (*)[3]'} 
but argument is of type 
'const uint8_t (*)[3][3]' {aka 'const unsigned char (*)[3][3]'}



```c
#define LED_COUNT 1 // placed here for context; lives in config.h
#define LEDMAP_KEYS( LM_11 ) { LM_11 } // placed here for context; lives in h file
typedef uint8_t ledmap[LED_COUNT][3]; // placed here for context; lives in h file ([3] is cuz HSV values)
void set_rgb_range(uint8_t led_min, uint8_t led_max, int layer, ledmap ledmapname); // placed here for context; lives in h file

const ledmap PROGMEM keyledmaps[] = {
    [_QWERTY] = LEDMAP_KEYS(
    RED // this is a macro for HSV colours
    ),
    [_UPPER] = LEDMAP_KEYS(
    PINK
    ),
};

void set_rgb_range(uint8_t led_start, uint8_t led_last, int layer, ledmap ledmapname) {
    const ledmap *l = &(ledmapname[layer]);
    // more stuff
}
set_rgb_range(LED_MIN, LED_MAX, /*layercodehere*/, keyledmaps);
```

Throws: (I formatted the error for reading)
```c
// line 44:23 is the 'ledmapname' here: const ledmap *l = &(ledmapname[layer]);
./keyboards/handwired/arcboard_mk14/keymaps/onekey/keymap.c:44:23: 
error: initialization of 
'const uint8_t (*)[3][3]' {aka 'const unsigned char (*)[3][3]'} 
from incompatible pointer type 
'uint8_t (*)[3]' {aka 'unsigned char (*)[3]'} [-Werror=incompatible-pointer-types]
     const ledmap *l = &(ledmapname[layer]);

// line 43:75 is the 'ledmapname' in the function argument list
./keyboards/handwired/arcboard_mk14/keymaps/onekey/keymap.c:43:75: 
note: expected 
'uint8_t (*)[3]' {aka 'unsigned char (*)[3]'} 
but argument is of type 
'const uint8_t (*)[3][3]' {aka 'const unsigned char (*)[3][3]'}
```



```c
// header file
#define RGB_MATRIX_LAYOUT_LEDMAP_KEYS( LM_11, LM_12, LM_13 ) { LM_11, LM_12, LM_13 } // this is called in the ledmap PROGMEM
typedef uint8_t ledmap[RGB_MATRIX_KEY_LED_COUNT][3]; // defines our ledmap type (originally RGB_MATRIX_LED_COUNT, i.e. max total LEDs; 3 is for hsv values)
// //extern const ledmap keyledmaps[RGB_MATRIX_KEY_LED_COUNT][3]; (only need this if using another file)
void set_rgb_range(uint8_t led_min, uint8_t led_max, int layer); // header def of the function
// color shorthand defines

// keymap.c
// our keymap PROGMEM
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QWERTY] = LAYOUT( \
    OSM(MOD_LSFT), KC_1, MO(_UPPER), KC_NO, KC_NO, KC_NO, KC_NO
),
[_UPPER] = LAYOUT( \
    OSM(MOD_LSFT), KC_1, MO(_UPPER), KC_NO, KC_NO, KC_NO, KC_NO
),
};
// our ledmap PROGMEM, with matching layers
const ledmap PROGMEM keyledmaps[] = {
    [_QWERTY] = RGB_MATRIX_LAYOUT_LEDMAP_KEYS(
    RED, YELLOW, BLUE
    ),
    [_UPPER] = RGB_MATRIX_LAYOUT_LEDMAP_KEYS(
    PINK, PINK, PINK
    ),
};
// the function

// so our problem statement is, we need to be able to...
// pass in the 'const ledmap PROGMEM keyledmaps[]' variable to the function
// const shouldn't matter? ... nor should PROGMEM...except that it's a mem thing, so maybe that's why they used an &
// uint8_t ledmapname[]

void set_rgb_range(uint8_t led_start, uint8_t led_last, int layer) {
    // keyledmaps here == the PROGMEM ledmap
    // so we are trying to pass in the 'ledmap PROGMEM keyledmaps'
    // without a function input, it's pulling an already-declared variable called 'keyledmaps'
    const ledmap *l = &(keyledmaps[layer]);
    uint8_t val = rgb_matrix_get_val();
    for (int i = led_start; i <= led_last; i++) {
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
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    set_rgb_range(KEY_LED_MIN, KEY_LED_MAX, get_highest_layer(layer_state | default_layer_state));
}


```



```c
// config.h has your ranges defined...
#define KEYS_LED_MIN 0
#define KEYS_LED_MAX 2
#define KEYS_LED_COUNT 3

// keyboard.h has a macro to define your ledmap size
#define KEYS_LEDMAP( LM_11, LM_12, LM_13 ) { LM_11, LM_12, LM_13 }
// a typedef for the ledmap array type: [#of leds] by [HSV has three values]
typedef uint8_t keyledmap[KEYS_LED_COUNT][3];
// an extern for the declared instance
extern const keyledmap keyledmaps[KEYS_LED_COUNT][3];
// and the header? for the function
void set_rgb_range(uint8_t led_start, uint8_t led_last, int layer, int ledmap);

// keymap.c has the ledmap PROGMEMs; the names should match your layer defs and macro above
const ledmap PROGMEM keyledmaps[] = {
    [_QWERTY] = LEDMAP_KEYS(
    RED, YELLOW, BLUE
    ),
    [_UPPER] = LEDMAP_KEYS(
    PINK, PINK, PINK
    ),
};

// the setting function
void set_rgb_range(uint8_t led_start, uint8_t led_last, int layer, uint8_t ledmap) {
    const ledmap *l = &(ledmap[layer]); // what ledmap to pull our HSV values from
    uint8_t val = rgb_matrix_get_val(); // this gets us our globally-configured max brightness
    for (int i = led_start; i <= led_last; i++) {
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

// and then us actually doing the dance; note this bool auto-uses led_min and led_max, which are qmk-generated thingies based on your rgbmatrix counts....???
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    // set_rgb_range(RANGE_LED_MIN, RANGE_LED_MAX, ~layer int~, ~extern keyledmap~);
    set_rgb_range(KEYS_LED_MIN, KEYS_LED_MAX, get_highest_layer(layer_state | default_layer_state), keyledmap);
    return false;
}
```













keyboard.h has:
```c
// uh should this be here...? this shouldn't be here...
enum userspace_layers {
    _QWERTY             = 0,
    FIRST_DEFAULT_LAYER = 0,
    _UPPER              = 1,
    _IND1_OFF = 5, // <--- These extra layers for indicator ledmap usage
    _IND1_ON = 6,
    _IND2_OFF = 7,
    _IND2_ON = 8
};
// The key matrix layout?...?
#define LAYOUT( \
    LM_11, LM_12, LM_13, LI_11, LI_12, LI_13, LI_21 \
) \
{ \
    { LM_11, LM_12, LM_13, LI_11, LI_12, LI_13, LI_21 }, \
}
// (these LM_/LI_ things appear to make not much difference... how do they relate?)
// The array?s
#define RGB_MATRIX_LAYOUT_LEDMAP_KEYS( LM_11, LM_12, LM_13 ) { LM_11, LM_12, LM_13 }

// define a type; it's a uint8_t (); name is keyledmap; it's a multidimensional array; why is is prepopulated...
// [LED_COUNT = how many leds in this ledmap system][3 = ...items per OHHH HSV]
typedef uint8_t keyledmap[LED_COUNT_KEYS][3];
extern const keyledmap keyledmaps[];

#define RGB_MATRIX_LAYOUT_LEDMAP_IND1( LI_11, LI_12, LI_13 ) { LI_11, LI_12, LI_13 }
typedef uint8_t ind1ledmap[LED_COUNT_IND1][3];
extern const ind1ledmap ind1ledmaps[];

#define RGB_MATRIX_LAYOUT_LEDMAP_IND2( LI_21 ) { LI_21 }
typedef uint8_t ind2ledmap[LED_COUNT_IND2][3];
extern const ind2ledmap ind2ledmaps[];

void set_rgb_range(uint8_t led_min, uint8_t led_max, int layer, int ledmap);
```
