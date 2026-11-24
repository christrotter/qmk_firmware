// Copyright 2021 Mikael Manukyan <arm.localhost@gmail.com>
// Copyright 2023 Chris Trotter (@christrotter)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "rgb_ledmaps.h"
#include "arcboard_mk22.h"
#include "keymap.h"

_Static_assert(RGB_LEDS_PER_HALF * 2 == RGB_MATRIX_LED_COUNT, "RGB_LEDS_PER_HALF does not match the rgb_matrix layout in keyboard.json");

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

bool rgb_matrix_indicators_user(void) {
    static const hsv_t indicator_bar_colors[4] = {{HSV_RED}, {HSV_PINK}, {HSV_CYAN}, {HSV_BLUE}};
    static const hsv_t panel_color             = {HSV_WHITE};
    static const hsv_t panel_logo_color        = {HSV_CYAN};

    const uint16_t b = half_base();

    // per-key leds (keys + thumbs) by ledmap
    set_rgb_ledmap(b + RGB_KEYS_START, RGB_LEDMAP_PER_HALF, KEYS_BRIGHTNESS);
    set_rgb_range(b + RGB_RING_START, RGB_RING_COUNT, (hsv_t){HSV_ORANGE}, INDICATOR_BRIGHTNESS_RING);
    set_rgb_range(b + RGB_ENC1_START, RGB_ENC1_COUNT, (hsv_t){HSV_CYAN}, INDICATOR_BRIGHTNESS_RING);
    set_rgb_range(b + RGB_DPAD_START, RGB_DPAD_COUNT, (hsv_t){HSV_BLUE}, INDICATOR_BRIGHTNESS_RING);
    set_rgb_range(b + RGB_ENC2_START, RGB_ENC2_COUNT, (hsv_t){HSV_YELLOW}, INDICATOR_BRIGHTNESS_RING);

    // indicator bars
    if (is_keyboard_left()) {
        // the left indicator pcb is mounted rotated 90deg and its chain snakes: each group of four is a column, and odd columns run the other way
        for (uint8_t i = 0; i < RGB_INDICATOR_COUNT; i++) {
            const uint8_t row = ((i / 4) % 2) ? 3 - (i % 4) : i % 4;
            set_rgb_range(b + RGB_INDICATOR_START + i, 1, indicator_bar_colors[3 - row], INDICATOR_BRIGHTNESS_RING);
        }
    } else {
        for (uint8_t i = 0; i < RGB_INDICATOR_COUNT; i++) {
            set_rgb_range(b + RGB_INDICATOR_START + i, 1, indicator_bar_colors[i / 4], INDICATOR_BRIGHTNESS_RING);
        }
    }

    // wing insert panel, with the logo inside it
    for (uint8_t i = 0; i < RGB_PANEL_COUNT; i++) {
        const bool is_logo = (i >= RGB_PANEL_LOGO_A_START && i < RGB_PANEL_LOGO_A_START + RGB_PANEL_LOGO_RUN_COUNT) ||
                             (i >= RGB_PANEL_LOGO_B_START && i < RGB_PANEL_LOGO_B_START + RGB_PANEL_LOGO_RUN_COUNT);
        set_rgb_range(b + RGB_PANEL_START + i, 1, is_logo ? panel_logo_color : panel_color, is_logo ? LOGO_BRIGHTNESS : PANEL_BRIGHTNESS);
    }
    return true;
}
