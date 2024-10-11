# question i never posted
Question about `auto_mouse_toggle`...
I have an encoder i want to use to flip through layers, but automouse blows up the 'holding mouse layer on'.  So I used auto_mouse_toggle when the encoder moves to mouse layer, and turning auto mouse back on once you go to other layers.  But it gets stuck, and you have to repeat the encoder motions twice to get it back to normal state.

I looked at the docs (https://github.com/qmk/qmk_firmware/blob/develop/docs/feature_pointing_device.md#use-custom-keys-to-control-auto-mouse) and this seemed close, but maybe I just don't understand how that works...or my context is different.

Encoder functionality desired:
- clockwise: scroll up through layers to hold on
- counterclockwise: reset to default layer

Feels like an obvious problem, but I'm just not seeing it.  Any ideas?

```c
    int encoder_counter = 0;    
    bool encoder_update_user(uint8_t index, bool clockwise) {
        if (clockwise) {
            printf("Encoder start. Toggle state: %d \n", get_auto_mouse_toggle());
            if ((encoder_counter + 1) == 1) {
              if (get_auto_mouse_enable()) {
                  auto_mouse_toggle();
              }
            }
            else {
              if (!get_auto_mouse_enable()) {
                  auto_mouse_toggle();
              }
            }
            printf("Layering on (%d). Toggle state: %d \n", encoder_counter, get_auto_mouse_toggle());
            layer_move(encoder_counter + 1);
            encoder_counter++;
        } else {
            layer_clear();
            if (!get_auto_mouse_enable()) {
                auto_mouse_toggle();
            }
            printf("Clearing layer.  Toggle state: %d \n", get_auto_mouse_toggle());
            encoder_counter = 0;
        }
    return false;
    }
```

The problem?  The if statements were not triggering correctly.  I simplified to the following and all is good.

```c
int encoder_counter = 0;
#if defined(ENCODER_ENABLE)
    bool encoder_update_user(uint8_t index, bool clockwise) {
        if (clockwise) {
            printf("Encoder start. Toggle state: %d \n", get_auto_mouse_toggle());
            if ((encoder_counter + 1) == 1) {
                // we are moving to the mouse layer from qwerty, turn off automouse
              if (get_auto_mouse_enable()) {
                  auto_mouse_toggle();
              }
            }
            // printf("Layering on (%d). Toggle state: %d \n", (encoder_counter + 1), get_auto_mouse_toggle());
            layer_move(encoder_counter + 1);
            encoder_counter++;
        } else {
            auto_mouse_toggle();
            layer_clear();
            // printf("Clearing layer.  Toggle state: %d \n", get_auto_mouse_toggle());
            encoder_counter = 0;
        }
    return false;
    }
#endif
```


# logging
```
// clockwise1
Encoder start. Toggle state: 0
Layering on (1). Toggle state: 1
// clockwise2
Encoder start. Toggle state: 1
Layering on (2). Toggle state: 1
// clockwise3
Encoder start. Toggle state: 1
Layering on (3). Toggle state: 1
// ccw1
Clearing layer.  Toggle state: 1

// clockwise1
Encoder start. Toggle state: 1
Layering on (1). Toggle state: 0
// clockwise2
Encoder start. Toggle state: 0
Layering on (2). Toggle state: 0
// clockwise3
Encoder start. Toggle state: 0
Layering on (3). Toggle state: 0
// ccw1
Clearing layer.  Toggle state: 0
```

the toggling is so not working...
```
Chris Trotter:handwired/arcboard_mk15:1: Encoder start. Toggle state: 0
Chris Trotter:handwired/arcboard_mk15:1: Layering on (1). Toggle state: 1
Chris Trotter:handwired/arcboard_mk15:1: Encoder start. Toggle state: 1
Chris Trotter:handwired/arcboard_mk15:1: Layering on (2). Toggle state: 1
Chris Trotter:handwired/arcboard_mk15:1: Encoder start. Toggle state: 1
Chris Trotter:handwired/arcboard_mk15:1: Layering on (3). Toggle state: 1
Chris Trotter:handwired/arcboard_mk15:1: Clearing layer.  Toggle state: 1

Chris Trotter:handwired/arcboard_mk15:1: Encoder start. Toggle state: 1
Chris Trotter:handwired/arcboard_mk15:1: Layering on (1). Toggle state: 0
Chris Trotter:handwired/arcboard_mk15:1: Encoder start. Toggle state: 0
Chris Trotter:handwired/arcboard_mk15:1: Layering on (2). Toggle state: 0
Chris Trotter:handwired/arcboard_mk15:1: Encoder start. Toggle state: 0
Chris Trotter:handwired/arcboard_mk15:1: Layering on (3). Toggle state: 0
Chris Trotter:handwired/arcboard_mk15:1: Clearing layer.  Toggle state: 0
```
