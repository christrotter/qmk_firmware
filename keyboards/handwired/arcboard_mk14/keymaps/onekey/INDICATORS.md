# Flawed but working method for getting indicators working with LEDmaps
This assumes all of your leds are on a single WS2018 chain.

The example assumes three backlit keys and two indicators with two leds each.

This is an awful way of doing this, but I'm not a C developer, so if you find a way to improve it, please let me know.

## A note on rgb matrix
You cannot do things like set 'HSV_BLACK' because the rgb matrix has an 'always on' colour that sits below your ledmap code.
Also, the rgb subsystem has no 'brightness' functionality when it comes to this.  HS'V' handles this for us, but it 
means that you cannot have a non-HSV LED also respecting your global brightness max.

I think ideally there needs to be an 'hsv matrix' or something like that to allow for the fundamental differences
of hsv and rgb colour definitions.

## Keyboard config file
```c
    #define RGBLED_NUM 7 // Total number of LEDs
    #define RGB_MATRIX_LED_COUNT RGBLED_NUM
    #define KEYS_LED_COUNT 3 // Total number of LEDs used by your backlit key ledmaps
    #define KEYS_LED_MIN 0 // key ledmap led address start
    #define KEYS_LED_MAX 2 // key ledmap led address end
    #define IND1_LED_COUNT 2 // Total number of LEDs used by indicator 1
    #define IND1_LED_MIN 3
    #define IND1_LED_MAX 4
    #define IND2_LED_COUNT 2 // Total number of LEDs used by indicator 2
    #define IND2_LED_MIN 5
    #define IND2_LED_MAX 6
```
## Keyboard header file
```c
#define LEDMAP_KEYS( LM_11, LM_12, LM_13 ) { LM_11, LM_12, LM_13 }
#define LEDMAP_IND1( LI_11, LI_12 ) { LI_11, LI_12 }
#define LEDMAP_IND2( LI_21, LI_22 ) { LI_21, LI_22 }

// [3], because HSV is three values, and your ledmaps are really arrays of HSV values
typedef uint8_t keysledmap[KEYS_LED_COUNT][3];
typedef uint8_t ind1ledmap[IND1_LED_COUNT][3];
typedef uint8_t ind2ledmap[IND2_LED_COUNT][3];

void set_rgb_range_keys(uint8_t led_start, uint8_t led_last, int layer);
void set_rgb_range_ind1(uint8_t led_start, uint8_t led_last, int layer);
void set_rgb_range_ind2(uint8_t led_start, uint8_t led_last, int layer);

// ALSO, include whatever colours you want in shortform
// e.g.....
#    define RED \
        { HSV_RED }
#    define CORAL \
        { HSV_CORAL }
```

## Keymap file
```c
// ledmaps for keys
const keysledmap keysledmaps[] = {
    [_QWERTY] = LEDMAP_KEYS(
    YELLOW, YELLOW, YELLOW
    ),
    [_UPPER] = LEDMAP_KEYS(
    PINK, PINK, PINK
    ),
};
// ledmaps for indicators
const ind1ledmap ind1ledmaps[] = {
    [0] = LEDMAP_IND1(
    YELLOW, YELLOW
    ),
    [1]  = LEDMAP_IND1(
    GREEN, GREEN
    ),
};
const ind2ledmap ind2ledmaps[] = {
    [0] = LEDMAP_IND2(
    ORANGE, ORANGE
    ),
    [1]  = LEDMAP_IND2(
    PURPLE, PURPLE
    ),
};

// a function per ledmap
// I did not know how to pass in the ledmap as an argument; spent too much time trying
// note that I ran into a weird off-by-one bug somewhere in the hsv conversion macros? maybe
// ...given what I'm trying to do, 'get colour, then iterate over led index' seemed ok, and works.
// NOTE: you can also use this to set a different brightness max, if your led-to-diffuser distance is too great/close
void set_rgb_range_keys(uint8_t led_start, uint8_t led_last, int layer) {
    uint8_t val = rgb_matrix_get_val();
    int i = 0;
    HSV hsv = {
        .h = (keysledmaps[layer])[i][0],
        .s = (keysledmaps[layer])[i][1],
        .v = val,
    };
    RGB rgb = hsv_to_rgb(hsv);
    for (int i = led_start; i <= led_last; i++) {
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }
}
void set_rgb_range_ind1(uint8_t led_start, uint8_t led_last, int layer) {
    uint8_t val = rgb_matrix_get_val();
    int i = 0;
    HSV hsv = {
        .h = (ind1ledmaps[layer])[i][0],
        .s = (ind1ledmaps[layer])[i][1],
        .v = val,
    };
    RGB rgb = hsv_to_rgb(hsv); // something in here was blowing up the i count
    for (int i = led_start; i <= led_last; i++) {
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }
}
void set_rgb_range_ind2(uint8_t led_start, uint8_t led_last, int layer) {
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
}

// finally, call them like this (probably doesn't need to be in this function?)
// this is logic to change the keys ledmap on layer change, and oneshot shift/shift-holding as indicators
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    set_rgb_range_keys(KEYS_LED_MIN, KEYS_LED_MAX, get_highest_layer(layer_state | default_layer_state));

    bool is_shifted = (get_mods() | get_weak_mods()) & MOD_MASK_SHIFT;
    if (is_shifted) {
        set_rgb_range_ind1(IND1_LED_MIN, IND1_LED_MAX, 1);
    } else {
        set_rgb_range_ind1(IND1_LED_MIN, IND1_LED_MAX, 0);
    }
    bool is_oneshot = (get_oneshot_mods() | get_mods()) & MOD_MASK_SHIFT;
    if (is_oneshot) {
        set_rgb_range_ind2(IND2_LED_MIN, IND2_LED_MAX, 1);
    } else {
        set_rgb_range_ind2(IND2_LED_MIN, IND2_LED_MAX, 0);
    }
    return false;
}
```
