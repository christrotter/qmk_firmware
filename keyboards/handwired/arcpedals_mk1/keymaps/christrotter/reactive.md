# per-key ledmaps and reactive lighting effects

Because foot pedals are hidden away under the desk, out of eyesight, it can be confusing to know which pedal you are pressing.
There are two ways I will solve for that - homing bumps, and the indicator bar.

Already the bar gives me static indication, per layer, of which pedal does what.  But it can't tell me that i've just pressed a pedal.
If I'm pressing the wrong one, or double-pressing, I want to know.

```c

```

# config needed
in keyboard/config.h...
```c
#define RGB_MATRIX_KEYPRESSES
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE
```

# reactive effects
```c
#ifdef RGB_MATRIX_KEYREACTIVE_ENABLED
#    ifdef ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
RGB_MATRIX_EFFECT(SOLID_REACTIVE_SIMPLE)
#        ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static HSV SOLID_REACTIVE_SIMPLE_math(HSV hsv, uint16_t offset) {
#            ifdef RGB_MATRIX_SOLID_REACTIVE_GRADIENT_MODE
    hsv.h = scale16by8(g_rgb_timer, qadd8(rgb_matrix_config.speed, 8) >> 4);
#            endif
    hsv.v = scale8(255 - offset, hsv.v);
    return hsv;
}

bool SOLID_REACTIVE_SIMPLE(effect_params_t* params) {
    return effect_runner_reactive(params, &SOLID_REACTIVE_SIMPLE_math);
}

#        endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#    endif     // ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#endif         // RGB_MATRIX_KEYREACTIVE_ENABLED
```

```c
#pragma once

#ifdef RGB_MATRIX_KEYREACTIVE_ENABLED

typedef HSV (*reactive_f)(HSV hsv, uint16_t offset);

bool effect_runner_reactive(effect_params_t* params, reactive_f effect_func) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    uint16_t max_tick = 65535 / qadd8(rgb_matrix_config.speed, 1);
    for (uint8_t i = led_min; i < led_max; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();
        uint16_t tick = max_tick;
        // Reverse search to find most recent key hit
        for (int8_t j = g_last_hit_tracker.count - 1; j >= 0; j--) {
            if (g_last_hit_tracker.index[j] == i && g_last_hit_tracker.tick[j] < tick) {
                tick = g_last_hit_tracker.tick[j];
                break;
            }
        }

        uint16_t offset = scale16by8(tick, qadd8(rgb_matrix_config.speed, 1));
        RGB      rgb    = rgb_matrix_hsv_to_rgb(effect_func(rgb_matrix_config.hsv, offset));
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }
    return rgb_matrix_check_finished_leds(led_max);
}

#endif // RGB_MATRIX_KEYREACTIVE_ENABLED
```

## basic operation of 'last_hit'
1. magic in the background captures in a buffer the last `LED_HITS_TO_REMEMBER` keys to be pressed.
2. the effect function does a search against this buffer; on first match, break out of the loop...
3. ...and modify the hsv-to-be-applied using...
4. effect_func(hsv, offset)

So the magic of the reactive effect is in these two pieces...
- effect_func
- offset

