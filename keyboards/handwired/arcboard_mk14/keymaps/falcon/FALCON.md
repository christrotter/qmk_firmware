# How to get the Falcon working
So you want to get the Charbydis EC11 pcb (aka Falcon PCB) working on your non-Charybdis handwired build?

Follow the assembly instructions in the readme: https://github.com/Bastardkb/Charybdis-EC11

# Wiring
The encoder (R1, R2) needs two GPIO ports, and needs to be connected to the bottom of a column and end of a row.

The D-IN needs to go on the end of your WS2818 LED chain (or, somewhere in the middle where you can easily isolate its LEDs).  We'll control this with the Ledmaps.

# Code
You need to code up...
- your encoder actions (rotary actions and keypress action)
- your led config
- your ledmap config and functions

# keyboard-level code
## rules.mk
```c
# Encoder
ENCODER_ENABLE = yes
ENCODER_MAP_ENABLE = no
// and of course your rgb matrix switches
```
## config.h
```c
// encoder
#define ENCODERS_PAD_A { GP12 }
#define ENCODERS_PAD_B { GP13 }
#define ENCODER_RESOLUTION 4
```
## keyboard.h
```c
// make sure the layers are defined (i'm still not sure how to get this out of keyboard.h)
```
## keyboard.c
```c
// the led_config needs to accommodate your entire LED string, so represent the Falcon LEDs here
led_config_t g_led_config = {
// Key Matrix to LED Index
{
    { 0 }
},
// LED Index to Physical Position // afaik this is only for stuff like matrix animations
{
    { 102,   0 }, { 102,   0 }, { 102,   0 }, { 102,   0 }, { 102,   0 }, { 102,   0 }, { 102,   0 }, { 102,   0 }, { 102,   0 }, { 102,   0 }, { 102,   0 }, { 102,   0 }
},
// LED type bit mask - 4 is per-key, 8 is indicator
{
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4
}
};
```
# keymap-level code
## keymap.c
The actual ledmap for your 12 LEDs.
```c
// ledmaps for keys
const keysledmap keysledmaps[] = {
    [_QWERTY] = LEDMAP_KEYS(
    BLUE, BLUE, BLUE,       PINK, PINK, PINK,         CHART, CHART, CHART,      ORANGE, ORANGE, ORANGE
    ),
    [_UPPER] = LEDMAP_KEYS(
    CYAN, CYAN, CYAN,       PURPLE, PURPLE, PURPLE,   CHART, CHART, CHART,      ORANGE, ORANGE, ORANGE
    ),
    [_UPPER2] = LEDMAP_KEYS(
    CYAN, CYAN, CYAN,       PINK, PINK, PINK,         GREEN, GREEN, GREEN,      ORANGE, ORANGE, ORANGE
    ),
    [_UPPER3] = LEDMAP_KEYS(
    CYAN, CYAN, CYAN,       PINK, PINK, PINK,         CHART, CHART, CHART,      RED, RED, RED
    ),
};
```
Your function `set_rgb_range_thing`
```c
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
```
Your encoder callback coding.
```c
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (clockwise) {
        layer_on(get_highest_layer(layer_state) + 1);
    } else {
        layer_clear();
    }
    return false;
}

```
## keymap/rgb_ledmaps.h
```c
#    define HSV_MOONLANDER         5,   5, 255

// you need a section like this
// a define for the positional array
// a new type thingledmap[THING_LED_COUNT][3]
// a function for set_rgb_range_thing

#define LEDMAP_KEYS( LM_0, LM_1, LM_2, LM_3, LM_4, LM_5, LM_6, LM_7, LM_8, LM_9, LM_10, LM_11 ) { LM_0, LM_1, LM_2, LM_3, LM_4, LM_5, LM_6, LM_7, LM_8, LM_9, LM_10, LM_11 }
typedef uint8_t keysledmap[KEYS_LED_COUNT][3];
extern const keysledmap keysledmaps[];
void set_rgb_range_keys(uint8_t led_start, uint8_t led_last, int layer);
```
