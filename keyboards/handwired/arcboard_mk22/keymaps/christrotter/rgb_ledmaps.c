// Copyright 2021 Mikael Manukyan <arm.localhost@gmail.com>
// Copyright 2023 Chris Trotter (@christrotter)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "rgb_ledmaps.h"
#include "arcboard_mk22.h"
#include "keymap.h"

bool process_record_user_rgb_matrix(uint16_t keycode, keyrecord_t *record) { return true; }

bool is_transparent_color(uint8_t h, uint8_t s) {
    return (h == 255 && s == 255); // Our ___t___ value
}

// Get color from the layer stack
HSV get_color_from_layer_stack(uint16_t led_index) {
    uint8_t highest_layer = get_highest_layer(layer_state | default_layer_state);
    
    // Start from highest active layer and work down
    for (int8_t layer = highest_layer; layer >= 0; layer--) {
        // Skip inactive layers
        if (!layer_state_is(layer) && layer != 0) {
            continue;
        }
        
        // Adjust index for split keyboard if needed
        int adjusted_index = led_index;
        if (!is_keyboard_left()) {
            // Apply any necessary index adjustment for right side
            if (led_index >= RGB_TOT_IND_L) {
                adjusted_index = led_index - RGB_TOT_IND_L;
            }
        }
        
        const uint8_t h = ledmaps[layer][adjusted_index][0];
        const uint8_t s = ledmaps[layer][adjusted_index][1];
        
        // If this key has a defined color on this layer (not transparent)
        if (!is_transparent_color(h, s)) {
            return (HSV){h, s, 0}; // Brightness will be set later
        }
    }
    
    // If we got here, all layers had transparent values for this LED
    // Return a default (black/off)
    return (HSV){0, 0, 0};
}

// Replace the existing set_rgb_ledmap function
void set_rgb_ledmap(uint16_t first_led, uint16_t last_led, int val, int layer) {
    for (int i = first_led; i <= last_led; i++) {
        // Get the color from the layer stack
        hsv_t hsv = get_color_from_layer_stack(i);
        hsv.v = val; // Set brightness
        
        if (hsv.h || hsv.s) { // Only set if the color isn't black/off
            RGB rgb = hsv_to_rgb(hsv);
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        }
    }
}

void set_rgb_range(uint16_t first_led, uint16_t last_led, int hue, int sat, int val, int val_override) {
    if (val_override) {
        val = val_override;
    } else {
        val = INDICATOR_BRIGHTNESS;
    }
    for (int i = first_led; i <= last_led; i++) {
        hsv_t hsv = {
            .h = hue,
            .s = sat,
            .v = val, // 120 is ok for outer uf, but inner needs brighter, and the led strip at 120 is wayyyy too bright
        };
        if (hsv.h || hsv.s) {
            RGB rgb = hsv_to_rgb(hsv);
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        }
    }
}

bool rgb_matrix_indicators_user() {

    if (is_keyboard_left()) {
        // set LEFT per-key leds by ledmap
        set_rgb_ledmap(RGB_KEYS_L_START, RGB_KEYS_L_END, KEYS_BRIGHTNESS, get_highest_layer(layer_state | default_layer_state));

    } else {
        // set RIGHT per-key leds by ledmap
        set_rgb_ledmap(RGB_KEYS_R_START, RGB_KEYS_R_END, KEYS_BRIGHTNESS, get_highest_layer(layer_state | default_layer_state));


    }
    return true;
}
