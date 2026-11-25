// Copyright 2021 Mikael Manukyan <arm.localhost@gmail.com>
// Copyright 2023 Chris Trotter (@christrotter)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "rgb_ledmaps.h"
#include "arcboard_mk22.h"
#include "keymap.h"
#include <lib/lib8tion/lib8tion.h>

_Static_assert(RGB_LEDS_PER_HALF * 2 == RGB_MATRIX_LED_COUNT, "RGB_LEDS_PER_HALF does not match the rgb_matrix layout in keyboard.json");
_Static_assert(FIN_PULSE_PERIOD > 0, "FIN_PULSE_PERIOD must be positive");
_Static_assert(FIN_PULSE_FLOOR < INDICATOR_BRIGHTNESS_FINS, "FIN_PULSE_FLOOR must be below INDICATOR_BRIGHTNESS_FINS");

bool is_transparent_color(uint8_t h, uint8_t s) {
    return (h == 255 && s == 255); // Our ___t___ value
}

// global index of this half's first led
static uint16_t half_base(void) {
    return is_keyboard_left() ? 0 : RGB_LEDS_PER_HALF;
}

// Get color from the layer stack
hsv_t get_color_from_layer_stack(uint16_t led_index) {
    // ledmaps[] holds the left half's entries, then the right half's
    const uint16_t ledmap_index  = (is_keyboard_left() ? 0 : RGB_LEDMAP_PER_HALF) + (led_index - half_base());
    const uint8_t  highest_layer = get_highest_layer(layer_state | default_layer_state);

    // Start from highest active layer and work down
    for (int8_t layer = highest_layer; layer >= 0; layer--) {
        // Skip inactive layers
        if (!layer_state_is(layer) && layer != 0) {
            continue;
        }

        const uint8_t h = ledmaps[layer][ledmap_index][0];
        const uint8_t s = ledmaps[layer][ledmap_index][1];

        // If this key has a defined color on this layer (not transparent)
        if (!is_transparent_color(h, s)) {
            return (hsv_t){h, s, 0}; // Brightness will be set later
        }
    }

    // If we got here, all layers had transparent values for this LED
    // Return a default (black/off)
    return (hsv_t){0, 0, 0};
}

void set_rgb_ledmap(uint16_t start, uint16_t count, uint8_t val) {
    for (uint16_t i = start; i < start + count; i++) {
        hsv_t hsv = get_color_from_layer_stack(i);
        hsv.v     = val;

        if (hsv.h || hsv.s) { // Only set if the color isn't black/off
            rgb_t rgb = hsv_to_rgb(hsv);
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        }
    }
}

void set_rgb_range(uint16_t start, uint16_t count, hsv_t hsv, uint8_t val) {
    hsv.v = val;
    if (!(hsv.h || hsv.s)) {
        return;
    }
    rgb_t rgb = hsv_to_rgb(hsv);
    for (uint16_t i = start; i < start + count; i++) {
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }
}

// which fin (0-3, front to back) an indicator led belongs to
static uint8_t indicator_fin(uint8_t i) {
    if (is_keyboard_left()) {
        // the left indicator pcb is mounted rotated 90deg and its chain snakes: each group of four is a column, and odd columns run the other way
        const uint8_t row = ((i / 4) % 2) ? 3 - (i % 4) : i % 4;
        return row;
    }
    return 3 - i / 4;
}

// brightness of a pulsing fin; phase 128 is the wave's peak, so a fin lights at full brightness and then dims
static uint8_t fin_pulse_val(uint32_t lit_since) {
    const uint32_t elapsed = (g_rgb_timer - lit_since) % FIN_PULSE_PERIOD;
    const uint8_t  phase   = 128 + elapsed * 256 / FIN_PULSE_PERIOD;
    return FIN_PULSE_FLOOR + scale8(FIN_PULSE_WAVE(phase), INDICATOR_BRIGHTNESS_FINS - FIN_PULSE_FLOOR);
}

// four fins of four leds: layer colour, shift, cmd, mouse layer held; an unlit fin is explicitly black
static void set_indicator_fins(uint16_t base) {
    static const hsv_t layer_colors[] = {
        {LAYER_0_COLOUR}, {LAYER_1_COLOUR}, {LAYER_2_COLOUR}, {LAYER_3_COLOUR}, {LAYER_4_COLOUR},
        {LAYER_5_COLOUR}, {LAYER_6_COLOUR}, {LAYER_7_COLOUR}, {LAYER_8_COLOUR}, {LAYER_9_COLOUR},
    };
    static const bool fin_pulses[4] = {false, true, true, true};
    static bool       fin_was_lit[4];
    static uint32_t   fin_lit_since[4];

    const uint8_t layer = get_highest_layer(layer_state | default_layer_state);
    const uint8_t mods  = get_mods() | get_weak_mods() | get_oneshot_mods();

    const bool  fin_lit[4]    = {true, mods & MOD_MASK_SHIFT, mods & MOD_MASK_GUI, layer_state_is(_MOUSE)};
    const hsv_t fin_color[4]  = {
        layer < ARRAY_SIZE(layer_colors) ? layer_colors[layer] : (hsv_t){HSV_WHITE},
        {HSV_GREEN},
        {HSV_PURPLE},
        {HSV_BLUE},
    };

    rgb_t fin_rgb[4];
    for (uint8_t fin = 0; fin < 4; fin++) {
        if (fin_lit[fin] && !fin_was_lit[fin]) {
            fin_lit_since[fin] = g_rgb_timer;
        }
        fin_was_lit[fin] = fin_lit[fin];

        hsv_t hsv = fin_color[fin];
        if (!fin_lit[fin]) {
            hsv.v = 0;
        } else if (fin_pulses[fin]) {
            hsv.v = fin_pulse_val(fin_lit_since[fin]);
        } else {
            hsv.v = INDICATOR_BRIGHTNESS_FINS;
        }
        fin_rgb[fin] = hsv_to_rgb(hsv);
    }

    for (uint8_t i = 0; i < RGB_INDICATOR_COUNT; i++) {
        const rgb_t rgb = fin_rgb[indicator_fin(i)];
        rgb_matrix_set_color(base + RGB_INDICATOR_START + i, rgb.r, rgb.g, rgb.b);
    }
}

bool rgb_matrix_indicators_user(void) {
    static const hsv_t panel_color             = {HSV_WHITE};
    static const hsv_t panel_logo_color        = {HSV_CYAN};

    const uint16_t b = half_base();

    // per-key leds (keys + thumbs) by ledmap
    set_rgb_ledmap(b + RGB_KEYS_START, RGB_LEDMAP_PER_HALF, KEYS_BRIGHTNESS);
    set_rgb_range(b + RGB_RING_START, RGB_RING_COUNT, (hsv_t){HSV_GREEN}, INDICATOR_BRIGHTNESS_RING);
    set_rgb_range(b + RGB_ENC1_START, RGB_ENC1_COUNT, is_keyboard_left() ? (hsv_t){LEFT_ENC1_COLOUR} : (hsv_t){RIGHT_ENC1_COLOUR}, ENCODER_BRIGHTNESS);
    set_rgb_range(b + RGB_DPAD_START, RGB_DPAD_COUNT, (hsv_t){HSV_BLUE}, DPAD_BRIGHTNESS);
    set_rgb_range(b + RGB_ENC2_START, RGB_ENC2_COUNT, is_keyboard_left() ? (hsv_t){LEFT_ENC2_COLOUR} : (hsv_t){RIGHT_ENC2_COLOUR}, ENCODER_BRIGHTNESS);

    set_indicator_fins(b);

    // wing insert panel, with the logo inside it
    for (uint8_t i = 0; i < RGB_PANEL_COUNT; i++) {
        const bool is_logo = (i >= RGB_PANEL_LOGO_A_START && i < RGB_PANEL_LOGO_A_START + RGB_PANEL_LOGO_RUN_COUNT) ||
                             (i >= RGB_PANEL_LOGO_B_START && i < RGB_PANEL_LOGO_B_START + RGB_PANEL_LOGO_RUN_COUNT);
        set_rgb_range(b + RGB_PANEL_START + i, 1, is_logo ? panel_logo_color : panel_color, is_logo ? LOGO_BRIGHTNESS : PANEL_BRIGHTNESS);
    }
    return true;
}
