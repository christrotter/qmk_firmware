

# ledmap/layer indexing way off just for post-keys led's
The symptoms are...
- keys ledmap works fine
- falcon ledmap does not map correctly, very bizarrely
  - first 6 leds are: layer1, last half
  - last 6 leds are:  layer3, first half
  - layer switching starts taking leds from the indicator ledmap


- indicator ledmap is always off by 3 layers, but maps right
  - related to '42'? (key count + falcon count) - could this be g_led_config related?

what are the math relationships here...



# ledmaps reading left row, right row, left row, right row...



how exactly does split work for the ledmaps??
```c
#define LEDMAP_KEYS(
    phys-left11, phys-left12, phys-left13,        phys-rght11, phys-rght12, phys-rght13, \
    phys-left21, phys-left22, phys-left23,        phys-rght21, phys-rght22, phys-rght23, \
    phys-left31, phys-left32, phys-left33,        phys-rght31, phys-rght32, phys-rght33
) {
    // the full led index sequence, split in the middle
    logi-left11, logi-left11, logi-left11,        logi-rght11, logi-rght11, logi-rght11, \
    logi-left21, logi-left22, logi-left23,        logi-rght21, logi-rght22, logi-rght23, \
    logi-left31, logi-left32, logi-left33,        logi-rght31, logi-rght32, logi-rght33 
}
// cuz the ledmap is...ordered...
const keysledmap keysledmaps[] = {
    [_QWERTY]   = LEDMAP_KEYS(
     CHART, RED, RED,           RED, RED, PINK,
     CHART, CYAN, CYAN,         CYAN, CYAN, PINK,
     CHART, ORANGE, ORANGE,     ORANGE, ORANGE, PINK,

   ), // aka
    [_QWERTY]   = LEDMAP_KEYS(
     logi-left11, logi-left12, logi-left13,        logi-rght11, logi-rght12, logi-rght13, 
     logi-left21, logi-left22, logi-left23,        logi-rght21, logi-rght22, logi-rght23,
     logi-left31, logi-left32, logi-left33,        logi-rght31, logi-rght32, logi-rght33 
   ),
};
```


```c
#define LEDMAP_KEYS( \
    LM_11, LM_12, LM_13, LM_14, LM_15, LM_16, RM_11, RM_12, RM_13, RM_14, RM_15, RM_16, \
    LM_21, LM_22, LM_23, LM_24, LM_25, LM_26, RM_21, RM_22, RM_23, RM_24, RM_25, RM_26, \
    LM_31, LM_32, LM_33, LM_34, LM_35, LM_36, RM_31, RM_32, RM_33, RM_34, RM_35, RM_36, \
    LM_41, LM_42, LM_43, LM_44, LM_45, LM_46, RM_41, RM_42, RM_43, RM_44, RM_45, RM_46, \
    LT_51, LT_52, LT_53, LT_54, LT_55, LT_56, RT_51, RT_52, RT_53, RT_54, RT_55, RT_56 \
) { \
    LM_11, LM_12, LM_13, LM_14, LM_15, LM_16, RM_11, RM_12, RM_13, RM_14, RM_15, RM_16, \
    LM_21, LM_22, LM_23, LM_24, LM_25, LM_26, RM_21, RM_22, RM_23, RM_24, RM_25, RM_26, \
    LM_31, LM_32, LM_33, LM_34, LM_35, LM_36, RM_31, RM_32, RM_33, RM_34, RM_35, RM_36, \
    LM_41, LM_42, LM_43, LM_44, LM_45, LM_46, RM_41, RM_42, RM_43, RM_44, RM_45, RM_46, \
    LT_51, LT_52, LT_53, LT_54, LT_55, LT_56, RT_51, RT_52, RT_53, RT_54, RT_55, RT_56 \
}

// also tried
#define LEDMAP_KEYS( \
    LM_11, LM_12, LM_13, LM_14, LM_15, LM_16, LM_21, LM_22, LM_23, LM_24, LM_25, LM_26, \
    LM_31, LM_32, LM_33, LM_34, LM_35, LM_36, LM_41, LM_42, LM_43, LM_44, LM_45, LM_46, \
    LT_51, LT_52, LT_53, LT_54, LT_55, LT_56, RM_11, RM_12, RM_13, RM_14, RM_15, RM_16, \
    RM_21, RM_22, RM_23, RM_24, RM_25, RM_26, RM_31, RM_32, RM_33, RM_34, RM_35, RM_36, \
    RM_41, RM_42, RM_43, RM_44, RM_45, RM_46, RT_51, RT_52, RT_53, RT_54, RT_55, RT_56 \
) { \
    LM_11, LM_12, LM_13, LM_14, LM_15, LM_16, LM_21, LM_22, LM_23, LM_24, LM_25, LM_26, \
    LM_31, LM_32, LM_33, LM_34, LM_35, LM_36, LM_41, LM_42, LM_43, LM_44, LM_45, LM_46, \
    LT_51, LT_52, LT_53, LT_54, LT_55, LT_56, RM_11, RM_12, RM_13, RM_14, RM_15, RM_16, \
    RM_21, RM_22, RM_23, RM_24, RM_25, RM_26, RM_31, RM_32, RM_33, RM_34, RM_35, RM_36, \
    RM_41, RM_42, RM_43, RM_44, RM_45, RM_46, RT_51, RT_52, RT_53, RT_54, RT_55, RT_56 \
}

#define LEDMAP_KEYS( \
    LM_11, LM_12, LM_13, LM_14, LM_15, LM_16, \
    LM_21, LM_22, LM_23, LM_24, LM_25, LM_26, \
    LM_31, LM_32, LM_33, LM_34, LM_35, LM_36, \
    LM_41, LM_42, LM_43, LM_44, LM_45, LM_46, \
    LT_51, LT_52, LT_53, LT_54, LT_55, LT_56, \
    RM_11, RM_12, RM_13, RM_14, RM_15, RM_16, \
    RM_21, RM_22, RM_23, RM_24, RM_25, RM_26, \
    RM_31, RM_32, RM_33, RM_34, RM_35, RM_36, \
    RM_41, RM_42, RM_43, RM_44, RM_45, RM_46, \
    RT_51, RT_52, RT_53, RT_54, RT_55, RT_56 \
) { \
    LM_11, LM_12, LM_13, LM_14, LM_15, LM_16, \
    LM_21, LM_22, LM_23, LM_24, LM_25, LM_26, \
    LM_31, LM_32, LM_33, LM_34, LM_35, LM_36, \
    LM_41, LM_42, LM_43, LM_44, LM_45, LM_46, \
    LT_51, LT_52, LT_53, LT_54, LT_55, LT_56, \
    RM_11, RM_12, RM_13, RM_14, RM_15, RM_16, \
    RM_21, RM_22, RM_23, RM_24, RM_25, RM_26, \
    RM_31, RM_32, RM_33, RM_34, RM_35, RM_36, \
    RM_41, RM_42, RM_43, RM_44, RM_45, RM_46, \
    RT_51, RT_52, RT_53, RT_54, RT_55, RT_56 \
}
```


// #define LEDMAP_KEYS( \
//     LM_11, LM_12, LM_13, LM_14, LM_15, LM_16,       RM_11, RM_12, RM_13, RM_14, RM_15, RM_16, \
//     LM_21, LM_22, LM_23, LM_24, LM_25, LM_26,       RM_21, RM_22, RM_23, RM_24, RM_25, RM_26, \
//     LM_31, LM_32, LM_33, LM_34, LM_35, LM_36,       RM_31, RM_32, RM_33, RM_34, RM_35, RM_36, \
//     LM_41, LM_42, LM_43, LM_44, LM_45, LM_46,       RM_41, RM_42, RM_43, RM_44, RM_45, RM_46, \
//     LT_51, LT_52, LT_53, LT_54, LT_55, LT_56,       RT_51, RT_52, RT_53, RT_54, RT_55, RT_56 \
// ) { \
//     LM_11, LM_12, LM_13, LM_14, LM_15, LM_16, \
//     LM_21, LM_22, LM_23, LM_24, LM_25, LM_26, \
//     LM_31, LM_32, LM_33, LM_34, LM_35, LM_36, \
//     LM_41, LM_42, LM_43, LM_44, LM_45, LM_46, \
//     LT_51, LT_52, LT_53, LT_54, LT_55, LT_56, \
//     RM_11, RM_12, RM_13, RM_14, RM_15, RM_16, \
//     RM_21, RM_22, RM_23, RM_24, RM_25, RM_26, \
//     RM_31, RM_32, RM_33, RM_34, RM_35, RM_36, \
//     RM_41, RM_42, RM_43, RM_44, RM_45, RM_46, \
//     RT_51, RT_52, RT_53, RT_54, RT_55, RT_56 \
// }
// typedef uint8_t keysledmap[KEYS_LED_COUNT][3]; // remembering the ledmap is for both sides...
// extern const keysledmap keysledmaps[];
// void set_rgb_range_keys(uint8_t led_start, uint8_t led_last, int val, int layer);




# ledmaps not compiling

This is our macro for all the key-leds.

## rgb_ledmaps.h
```c
#define LEDMAP_KEYS( \
    LM_11, LM_12, LM_13, LM_14, LM_15, LM_16, RM_11, RM_12, RM_13, RM_14, RM_15, RM_16, \
    LM_21, LM_22, LM_23, LM_24, LM_25, LM_26, RM_21, RM_22, RM_23, RM_24, RM_25, RM_26, \
    LM_31, LM_32, LM_33, LM_34, LM_35, LM_36, RM_31, RM_32, RM_33, RM_34, RM_35, RM_36, \
    LM_41, LM_42, LM_43, LM_44, LM_45, LM_46, RM_41, RM_42, RM_43, RM_44, RM_45, RM_46, \
    LT_51, LT_52, LT_53, LT_54, LT_55, LT_56, RT_51, RT_52, RT_53, RT_54, RT_55, RT_56 \
) { \
    LM_11, LM_12, LM_13, LM_14, LM_15, LM_16, RM_11, RM_12, RM_13, RM_14, RM_15, RM_16, \
    LM_21, LM_22, LM_23, LM_24, LM_25, LM_26, RM_21, RM_22, RM_23, RM_24, RM_25, RM_26, \
    LM_31, LM_32, LM_33, LM_34, LM_35, LM_36, RM_31, RM_32, RM_33, RM_34, RM_35, RM_36, \
    LM_41, LM_42, LM_43, LM_44, LM_45, LM_46, RM_41, RM_42, RM_43, RM_44, RM_45, RM_46, \
    LT_51, LT_52, LT_53, LT_54, LT_55, LT_56, RT_51, RT_52, RT_53, RT_54, RT_55, RT_56 \
}
typedef uint8_t keysledmap[KEYS_LED_COUNT][3]; // remembering the ledmap is for both sides...
extern const keysledmap keysledmaps[];
void set_rgb_range_keys(uint8_t led_start, uint8_t led_last, int layer);
```
## rgb_ledmaps.c
This is our function to set the leds based on maps...
```c
void set_rgb_range_keys(uint8_t led_min, uint8_t led_max, int layer) {
    uint8_t val = rgb_matrix_get_val();
    int i = 0;
    HSV hsv = {
        .h = (keysledmaps[layer])[i][0],
        .s = (keysledmaps[layer])[i][1],
        .v = val,
    };
    RGB rgb = hsv_to_rgb(hsv);
    for (int i = led_min; i <= led_max; i++) {
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }
}
```
# another ledmap function
```c
void set_layer_rgb(uint8_t led_min, uint8_t led_max, int layer) {
    const ledmap *l = &(ledmaps[layer]);

    uint8_t val = rgb_matrix_get_val();

    for (int i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
        HSV hsv = {
            .h = (*l)[i][0],
            .s = (*l)[i][1],
            .v = val,
        };

        if (hsv.h || hsv.s) {
            RGB rgb = hsv_to_rgb(hsv);
            RGB_MATRIX_INDICATOR_SET_COLOR(i, rgb.r, rgb.g, rgb.b);
        }
    }
}
```


## keymap.c
Using the above macro, we have our per-key led assignments.
```c
const keysledmap keysledmaps[] = {
    [_QWERTY] = LEDMAP_KEYS(
       CYAN, ___n___, ___n___, ___n___, ___n___, ___n___,           ___n___, ___n___, ___n___, ___n___, ___n___,    CYAN,
       GOLD, ___n___, ___n___, HRM_CTL, ___n___, ___n___,           ___n___, ___n___, ___n___, ___n___, ___n___,    CYAN,
      GREEN, ___n___, HRM_ALT, HRM_GUI, HRM_SFT, ___n___,           ___n___, HRM_SFT, HRM_GUI, HRM_ALT, ___n___, ___n___,
       DRAG, ___n___, ___n___, ___n___, ___n___, ___n___,           ___n___, HRM_CTL, ___n___, ___n___, ___n___,     RED,
      SHIFT, ___n___,     ESC,     DEL, TOG_NAV,  BCKSPC,           SHIFT, ___n___, TOG_SYM, ___n___, ENTER, SPACE
    ),
    [_MOUSE] = LEDMAP_KEYS(
       CYAN, ___n___, ___n___, ___n___, ___n___, ___n___,           ___n___, ___n___, ___n___, ___n___, ___n___, ___n___,
       GOLD, ___n___, ___n___, ___n___, ___n___, ___n___,               RED,   GREEN, ___n___, ___n___, ___n___, ___n___,
      GREEN, ___n___, ___n___, ___n___, ___n___, ___n___,              DRAG,    CYAN,    PINK,    CYAN, ___n___, ___n___,
       DRAG, ___n___, ___n___, ___n___, ___n___, ___n___,           ___n___, ___n___, ___n___, ___n___, ___n___,     RED,
      SHIFT, ___n___,     ESC,     DEL, TOG_NAV,  BCKSPC,           SHIFT, ___n___, TOG_SYM, ___n___, ENTER, SPACE
    ),
    [_SYMBOLS] = LEDMAP_KEYS(
       CYAN, ___n___, ___n___, ___n___, ___n___, ___n___,          ORANGE, MAGIPLY, ___n___, ___n___, ___n___, ___n___,
       GOLD,    GOLD,   GREEN,  PURPLE,  PURPLE,   GREEN,           GREEN,    CYAN,    CYAN,    CYAN, ___n___, ___n___,
      GREEN,    CYAN,  YELLOW,  MAGENT,  MAGENT,    BLUE,           GREEN,    CYAN,    CYAN,    CYAN,    CYAN, ___n___,
       DRAG,    GOLD,   GREEN,   PINK,     PINK,    CYAN,             RED,    CYAN,    CYAN,    CYAN,    GOLD,     RED,
      SHIFT, ___n___,     ESC,     DEL, TOG_NAV,  BCKSPC,           SHIFT, ___n___, TOG_SYM, ___n___, ENTER, SPACE
    ),
    [_NAV] = LEDMAP_KEYS(
       CYAN, ___n___, ___n___, ___n___, ___n___, ___n___,           ___n___, ___n___,  ORANGE, ___n___, ___n___, ___n___,
       GOLD, ___n___, ___n___,    CYAN, ___n___,  PURPLE,             GREEN,    CYAN,   GREEN,    CYAN,     RED, ___n___,
      GREEN,    BLUE,  SPRING,    PINK,    CYAN,   GREEN,            YELLOW,   GREEN,   GREEN,   GREEN,  YELLOW, ___n___,
       DRAG, ___n___, ___n___, ___n___, ___n___,     RED,            PURPLE,  ORANGE,  ORANGE,  ORANGE,  PURPLE,     RED,
      SHIFT, ___n___,  YELLOW,     DEL, TOG_NAV,  BCKSPC,           SHIFT, ___n___, TOG_SYM, ___n___, ENTER, SPACE
    ),
};
```
It's angry about trying to turn 'RED' into 'HSV_RED' which becomes '0,255,255', which it thinks has too many elements.
i.e. it's expecting a single value and we are passing it an array.
```c
// create an int called 'keysledmap' that is a multidimensional array of [VAR] and [3];
// an array of x arrays each with 3 items
typedef uint8_t keysledmap[KEYS_LED_COUNT][3];
// and then create a global constant of type 'keysledmap' called keysledmaps[]
// global constant (static) of this type with this identifier/name;
// extern = other files can use this
// const = static thing
// keysledmap = int with two-dim array
// keysledmaps = an additional array of arrays?
extern const keysledmap keysledmaps[];
```
Some of the error messages portray it as:
`keysledmaps[0][0][0]` or `keysledmaps[0][59][0]`
So:
```c
// keysledmaps[0] (layer?) [0] (key location) [0] (hsv array)
```









```c
In file included from keyboards/handwired/arcboard_mk15/arcboard_mk15.h:10,
                 from ./keyboards/handwired/arcboard_mk15/keymaps/christrotter/keymap.c:22,
                 from quantum/keymap_introspection.c:5:
quantum/color.h:66:30: error: excess elements in scalar initializer [-Werror]
 #define HSV_RED           0, 255, 255
                              ^~~
keyboards/handwired/arcboard_mk15/keymaps/christrotter/rgb_ledmaps.h:29:5: note: in definition of macro 'LEDMAP_KEYS'
     LM_11, LM_12, LM_13, LM_14, LM_15, LM_16, RM_11, RM_12, RM_13, RM_14, RM_15, RM_16, \
     ^~~~~
keyboards/handwired/arcboard_mk15/arcboard_mk15.h:78:11: note: in expansion of macro 'HSV_RED'
         { HSV_RED }
           ^~~~~~~
./keyboards/handwired/arcboard_mk15/keymaps/christrotter/keymap.c:420:8: note: in expansion of macro 'RED'
        RED, ___n___, ___n___, ___n___, ___n___, ___n___,           ___n___, ___n___, ___n___, ___n___, ___n___, ___n___,
        ^~~
quantum/color.h:66:30: note: (near initialization for 'keysledmaps[0][0][0]')
 #define HSV_RED           0, 255, 255
                              ^~~
keyboards/handwired/arcboard_mk15/keymaps/christrotter/rgb_ledmaps.h:29:5: note: in definition of macro 'LEDMAP_KEYS'
     LM_11, LM_12, LM_13, LM_14, LM_15, LM_16, RM_11, RM_12, RM_13, RM_14, RM_15, RM_16, \
     ^~~~~
keyboards/handwired/arcboard_mk15/arcboard_mk15.h:78:11: note: in expansion of macro 'HSV_RED'
         { HSV_RED }
           ^~~~~~~
./keyboards/handwired/arcboard_mk15/keymaps/christrotter/keymap.c:420:8: note: in expansion of macro 'RED'
        RED, ___n___, ___n___, ___n___, ___n___, ___n___,           ___n___, ___n___, ___n___, ___n___, ___n___, ___n___,
        ^~~
quantum/color.h:66:35: error: excess elements in scalar initializer [-Werror]
 #define HSV_RED           0, 255, 255
                                   ^~~
keyboards/handwired/arcboard_mk15/keymaps/christrotter/rgb_ledmaps.h:29:5: note: in definition of macro 'LEDMAP_KEYS'
     LM_11, LM_12, LM_13, LM_14, LM_15, LM_16, RM_11, RM_12, RM_13, RM_14, RM_15, RM_16, \
     ^~~~~
keyboards/handwired/arcboard_mk15/arcboard_mk15.h:78:11: note: in expansion of macro 'HSV_RED'
         { HSV_RED }
           ^~~~~~~
./keyboards/handwired/arcboard_mk15/keymaps/christrotter/keymap.c:420:8: note: in expansion of macro 'RED'
        RED, ___n___, ___n___, ___n___, ___n___, ___n___,           ___n___, ___n___, ___n___, ___n___, ___n___, ___n___,
        ^~~
quantum/color.h:66:35: note: (near initialization for 'keysledmaps[0][0][0]')
 #define HSV_RED           0, 255, 255
                                   ^~~
keyboards/handwired/arcboard_mk15/keymaps/christrotter/rgb_ledmaps.h:29:5: note: in definition of macro 'LEDMAP_KEYS'
     LM_11, LM_12, LM_13, LM_14, LM_15, LM_16, RM_11, RM_12, RM_13, RM_14, RM_15, RM_16, \
     ^~~~~
keyboards/handwired/arcboard_mk15/arcboard_mk15.h:78:11: note: in expansion of macro 'HSV_RED'
         { HSV_RED }
           ^~~~~~~
./keyboards/handwired/arcboard_mk15/keymaps/christrotter/keymap.c:420:8: note: in expansion of macro 'RED'
        RED, ___n___, ___n___, ___n___, ___n___, ___n___,           ___n___, ___n___, ___n___, ___n___, ___n___, ___n___,
        ^~~
```

# another way of doing ledmaps

## keymap.h
```c
#define RED {HSV_RED}
#define CORAL {HSV_CORAL}
#define ORANGE {HSV_ORANGE}
#define GOLDEN {HSV_GOLDENROD}
#define GOLD {HSV_GOLD}
#define YELLOW {HSV_YELLOW}
#define CHART {HSV_CHARTREUSE}
#define GREEN {HSV_GREEN}
#define SPRING {HSV_SPRINGGREEN}
#define TURQ {HSV_TURQUOISE}
#define TEAL {HSV_TEAL}
#define CYAN {HSV_CYAN}
#define AZURE {HSV_AZURE}
#define BLUE {HSV_BLUE}
#define PURPLE {HSV_PURPLE}
#define MAGENT {HSV_MAGENTA}
#define PINK {HSV_PINK}
```

## keymap.c
```c
#define _______ {0, 0, 0}

const uint8_t PROGMEM ledmap[][RGB_MATRIX_LED_COUNT][3] = {
    [_FL] = {
        _______, CORAL,   CORAL,   _______, _______, CORAL,   CORAL,   _______, _______, CORAL,   _______, YELLOW,  YELLOW,           TEAL,    GOLD,   GOLD,
        _______, _______, PINK,    PINK,    PINK,    PINK,    _______, _______, _______, GREEN,   GREEN,   GREEN,   GREEN,   _______, TEAL,    TEAL,   TEAL,
        ORANGE,  ORANGE,  ORANGE,  ORANGE,  ORANGE,  ORANGE,  _______, AZURE,   AZURE,   _______, _______, _______, _______, _______, TEAL,    TEAL,   TEAL,
        _______, ORANGE,  ORANGE,  ORANGE,  ORANGE,  ORANGE,  _______, _______, _______, _______, _______, _______, _______,
        _______, ORANGE,  _______, CORAL,   _______, AZURE,   AZURE,   _______, _______, _______, _______, AZURE,                              SPRING,
        _______, _______, _______,                   _______,                            _______, PINK,    _______, AZURE,            _______, SPRING, _______
    }
};

// this is not that useful, as it uses IS-something LEDs.
void set_layer_color(int layer) {
    if (layer == 0) { return; }
    for (int i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
        HSV hsv = {
            .h = pgm_read_byte(&ledmap[layer][i][0]),
            .s = pgm_read_byte(&ledmap[layer][i][1]),
            .v = pgm_read_byte(&ledmap[layer][i][2]),
        };
        if (hsv.h || hsv.s || hsv.v) {
            RGB rgb = hsv_to_rgb(hsv);
            float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
            rgb_matrix_set_color(i, f * rgb.r, f * rgb.g, f * rgb.b);
        } else if (layer != 1) {
            // Only deactivate non-defined key LEDs at layers other than FN. Because at FN we have RGB adjustments and need to see them live.
            // If the values are all false then it's a transparent key and deactivate LED at this layer
            rgb_matrix_set_color(i, 0, 0, 0);
        }
    }
}
bool rgb_matrix_indicators_user(void) {
    if (disable_layer_color ||
        rgb_matrix_get_flags() == LED_FLAG_NONE ||
        rgb_matrix_get_flags() == LED_FLAG_UNDERGLOW) {
            return;
        }
    set_layer_color(get_highest_layer(layer_state));
    return false;
}
```
