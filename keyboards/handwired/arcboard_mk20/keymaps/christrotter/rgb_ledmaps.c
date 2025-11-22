// Copyright 2021 Mikael Manukyan <arm.localhost@gmail.com>
// Copyright 2023 Chris Trotter (@christrotter)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "rgb_ledmaps.h"
#include "arcboard_mk20.h"
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
    bool is_shifted = (get_mods() | get_weak_mods()) & MOD_MASK_SHIFT;
    bool is_oneshot_shift = (get_oneshot_mods() | get_mods()) & MOD_MASK_SHIFT;

    bool is_lguied = (get_mods() | get_weak_mods()) & MOD_MASK_GUI;
    bool is_oneshot_gui = (get_oneshot_mods() | get_mods()) & MOD_MASK_GUI;
    if (is_keyboard_left()) {
        // set LEFT per-key leds by ledmap
        set_rgb_ledmap(RGB_KEYS_L_START, RGB_KEYS_L_END, KEYS_BRIGHTNESS, get_highest_layer(layer_state | default_layer_state));
        
        // todo have these change on layers
        set_rgb_range(RGB_RING_L_START, RGB_RING_L_END, HSV_GREEN, INDICATOR_BRIGHTNESS_RING); 
        set_rgb_range(RGB_LOGO_L_START, RGB_LOGO_L_END, HSV_CYAN, INDICATOR_BRIGHTNESS);

        switch(get_highest_layer(layer_state|default_layer_state)) {
            case 0:
                set_rgb_range(RGB_INNER_INTAKE_L_START, RGB_INNER_INTAKE_L_END, LAYER_0_COLOUR, INDICATOR_BRIGHTNESS);
                set_rgb_range(RGB_OUTER_INTAKE_L_START, RGB_OUTER_INTAKE_L_END, LAYER_0_COLOUR, INDICATOR_BRIGHTNESS);
                break;
            case 1:
                set_rgb_range(RGB_INNER_INTAKE_L_START, RGB_INNER_INTAKE_L_END, LAYER_1_COLOUR, INDICATOR_BRIGHTNESS);
                set_rgb_range(RGB_OUTER_INTAKE_L_START, RGB_OUTER_INTAKE_L_END, LAYER_1_COLOUR, INDICATOR_BRIGHTNESS);
                break;
            case 2:
                set_rgb_range(RGB_INNER_INTAKE_L_START, RGB_INNER_INTAKE_L_END, LAYER_2_COLOUR, INDICATOR_BRIGHTNESS);
                set_rgb_range(RGB_OUTER_INTAKE_L_START, RGB_OUTER_INTAKE_L_END, LAYER_2_COLOUR, INDICATOR_BRIGHTNESS);
                break;
            case 3:
                set_rgb_range(RGB_INNER_INTAKE_L_START, RGB_INNER_INTAKE_L_END, LAYER_3_COLOUR, INDICATOR_BRIGHTNESS);
                set_rgb_range(RGB_OUTER_INTAKE_L_START, RGB_OUTER_INTAKE_L_END, LAYER_3_COLOUR, INDICATOR_BRIGHTNESS);
                break;
            case 4:
                set_rgb_range(RGB_INNER_INTAKE_L_START, RGB_INNER_INTAKE_L_END, LAYER_4_COLOUR, INDICATOR_BRIGHTNESS);
                set_rgb_range(RGB_OUTER_INTAKE_L_START, RGB_OUTER_INTAKE_L_END, LAYER_4_COLOUR, INDICATOR_BRIGHTNESS);
                break;
            case 5:
                set_rgb_range(RGB_INNER_INTAKE_L_START, RGB_INNER_INTAKE_L_END, LAYER_5_COLOUR, INDICATOR_BRIGHTNESS);
                set_rgb_range(RGB_OUTER_INTAKE_L_START, RGB_OUTER_INTAKE_L_END, LAYER_5_COLOUR, INDICATOR_BRIGHTNESS);
                break;
            case 6:
                set_rgb_range(RGB_INNER_INTAKE_L_START, RGB_INNER_INTAKE_L_END, LAYER_6_COLOUR, INDICATOR_BRIGHTNESS);
                set_rgb_range(RGB_OUTER_INTAKE_L_START, RGB_OUTER_INTAKE_L_END, LAYER_6_COLOUR, INDICATOR_BRIGHTNESS);
                break;
            case 7:
                set_rgb_range(RGB_INNER_INTAKE_L_START, RGB_INNER_INTAKE_L_END, LAYER_7_COLOUR, INDICATOR_BRIGHTNESS);
                set_rgb_range(RGB_OUTER_INTAKE_L_START, RGB_OUTER_INTAKE_L_END, LAYER_7_COLOUR, INDICATOR_BRIGHTNESS);
                break;
            case 8:
                set_rgb_range(RGB_INNER_INTAKE_L_START, RGB_INNER_INTAKE_L_END, LAYER_8_COLOUR, INDICATOR_BRIGHTNESS);
                set_rgb_range(RGB_OUTER_INTAKE_L_START, RGB_OUTER_INTAKE_L_END, LAYER_8_COLOUR, INDICATOR_BRIGHTNESS);
                break;
            case 9:
                set_rgb_range(RGB_INNER_INTAKE_L_START, RGB_INNER_INTAKE_L_END, LAYER_9_COLOUR, INDICATOR_BRIGHTNESS);
                set_rgb_range(RGB_OUTER_INTAKE_L_START, RGB_OUTER_INTAKE_L_END, LAYER_9_COLOUR, INDICATOR_BRIGHTNESS);
                break;

            default:
                break;
        }

        if (is_shifted || (is_oneshot_shift && !is_oneshot_gui)) {
            set_rgb_range(RGB_INDICATOR_L_START, RGB_INDICATOR_L_END, HSV_GREEN, INDICATOR_BRIGHTNESS);
        } else if (kb_get_pointer_dragscroll_enabled()) {
            set_rgb_range(RGB_INDICATOR_L_START, RGB_INDICATOR_L_END, HSV_ORANGE, INDICATOR_BRIGHTNESS);
        } else if (is_lguied || (is_oneshot_gui && !is_oneshot_shift)) {
            set_rgb_range(RGB_INDICATOR_L_START, RGB_INDICATOR_L_END, HSV_PURPLE, INDICATOR_BRIGHTNESS);
        } else if (is_oneshot_gui && is_oneshot_shift) {
            set_rgb_range(RGB_INDICATOR_L1_START, RGB_INDICATOR_L1_END, HSV_GREEN, INDICATOR_BRIGHTNESS);
            set_rgb_range(RGB_INDICATOR_L2_START, RGB_INDICATOR_L2_END, HSV_PURPLE, INDICATOR_BRIGHTNESS);
        } else {
            set_rgb_range(RGB_INDICATOR_L_START, RGB_INDICATOR_L_END, BACKGROUND_SILVER, INDICATOR_BRIGHTNESS_IDLE);
        }
    } else {
        // set RIGHT per-key leds by ledmap
        set_rgb_ledmap(RGB_KEYS_R_START, RGB_KEYS_R_END, KEYS_BRIGHTNESS, get_highest_layer(layer_state | default_layer_state));

        // todo have these change on layers
        set_rgb_range(RGB_RING_R_START, RGB_RING_R_END, HSV_GOLD, INDICATOR_BRIGHTNESS_RING);
        set_rgb_range(RGB_LOGO_R_START, RGB_LOGO_R_END, HSV_CYAN, INDICATOR_BRIGHTNESS);
        
        switch(get_highest_layer(layer_state|default_layer_state)) {
            case 0:
                set_rgb_range(RGB_INNER_INTAKE_R_START, RGB_INNER_INTAKE_R_END, LAYER_0_COLOUR, INDICATOR_BRIGHTNESS);
                set_rgb_range(RGB_OUTER_INTAKE_R_START, RGB_OUTER_INTAKE_R_END, LAYER_0_COLOUR, INDICATOR_BRIGHTNESS);
                break;
            case 1:
                set_rgb_range(RGB_INNER_INTAKE_R_START, RGB_INNER_INTAKE_R_END, LAYER_1_COLOUR, INDICATOR_BRIGHTNESS);
                set_rgb_range(RGB_OUTER_INTAKE_R_START, RGB_OUTER_INTAKE_R_END, LAYER_1_COLOUR, INDICATOR_BRIGHTNESS);
                break;
            case 2:
                set_rgb_range(RGB_INNER_INTAKE_R_START, RGB_INNER_INTAKE_R_END, LAYER_2_COLOUR, INDICATOR_BRIGHTNESS);
                set_rgb_range(RGB_OUTER_INTAKE_R_START, RGB_OUTER_INTAKE_R_END, LAYER_2_COLOUR, INDICATOR_BRIGHTNESS);
                break;
            case 3:
                set_rgb_range(RGB_INNER_INTAKE_R_START, RGB_INNER_INTAKE_R_END, LAYER_3_COLOUR, INDICATOR_BRIGHTNESS);
                set_rgb_range(RGB_OUTER_INTAKE_R_START, RGB_OUTER_INTAKE_R_END, LAYER_3_COLOUR, INDICATOR_BRIGHTNESS);
                break;
            case 4:
                set_rgb_range(RGB_INNER_INTAKE_R_START, RGB_INNER_INTAKE_R_END, LAYER_4_COLOUR, INDICATOR_BRIGHTNESS);
                set_rgb_range(RGB_OUTER_INTAKE_R_START, RGB_OUTER_INTAKE_R_END, LAYER_4_COLOUR, INDICATOR_BRIGHTNESS);
                break;
            case 5:
                set_rgb_range(RGB_INNER_INTAKE_R_START, RGB_INNER_INTAKE_R_END, LAYER_5_COLOUR, INDICATOR_BRIGHTNESS);
                set_rgb_range(RGB_OUTER_INTAKE_R_START, RGB_OUTER_INTAKE_R_END, LAYER_5_COLOUR, INDICATOR_BRIGHTNESS);
                break;
            case 6:
                set_rgb_range(RGB_INNER_INTAKE_R_START, RGB_INNER_INTAKE_R_END, LAYER_6_COLOUR, INDICATOR_BRIGHTNESS);
                set_rgb_range(RGB_OUTER_INTAKE_R_START, RGB_OUTER_INTAKE_R_END, LAYER_6_COLOUR, INDICATOR_BRIGHTNESS);
                break;
            case 7:
                set_rgb_range(RGB_INNER_INTAKE_R_START, RGB_INNER_INTAKE_R_END, LAYER_7_COLOUR, INDICATOR_BRIGHTNESS);
                set_rgb_range(RGB_OUTER_INTAKE_R_START, RGB_OUTER_INTAKE_R_END, LAYER_7_COLOUR, INDICATOR_BRIGHTNESS);
                break;
            case 8:
                set_rgb_range(RGB_INNER_INTAKE_R_START, RGB_INNER_INTAKE_R_END, LAYER_8_COLOUR, INDICATOR_BRIGHTNESS);
                set_rgb_range(RGB_OUTER_INTAKE_R_START, RGB_OUTER_INTAKE_R_END, LAYER_8_COLOUR, INDICATOR_BRIGHTNESS);
                break;
            case 9:
                set_rgb_range(RGB_INNER_INTAKE_R_START, RGB_INNER_INTAKE_R_END, LAYER_9_COLOUR, INDICATOR_BRIGHTNESS);
                set_rgb_range(RGB_OUTER_INTAKE_R_START, RGB_OUTER_INTAKE_R_END, LAYER_9_COLOUR, INDICATOR_BRIGHTNESS);
                break;

            default:
                break;
        }

        if (is_shifted || (is_oneshot_shift && !is_oneshot_gui)) {
            set_rgb_range(RGB_INDICATOR_R_START, RGB_INDICATOR_R_END, HSV_GREEN, INDICATOR_BRIGHTNESS);
        } else if (kb_get_pointer_dragscroll_enabled()) {
            set_rgb_range(RGB_INDICATOR_R_START, RGB_INDICATOR_R_END, HSV_ORANGE, INDICATOR_BRIGHTNESS);
        } else if (is_lguied || (is_oneshot_gui && !is_oneshot_shift)) {
            set_rgb_range(RGB_INDICATOR_R_START, RGB_INDICATOR_R_END, HSV_PURPLE, INDICATOR_BRIGHTNESS);
        } else if (is_oneshot_gui && is_oneshot_shift) {
            set_rgb_range(RGB_INDICATOR_R1_START, RGB_INDICATOR_R1_END, HSV_GREEN, INDICATOR_BRIGHTNESS);
            set_rgb_range(RGB_INDICATOR_R2_START, RGB_INDICATOR_R2_END, HSV_PURPLE, INDICATOR_BRIGHTNESS);
        } else {
            set_rgb_range(RGB_INDICATOR_R_START, RGB_INDICATOR_R_END, BACKGROUND_SILVER, INDICATOR_BRIGHTNESS_IDLE);
        }
    }
    return true;
}
