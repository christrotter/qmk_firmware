# re-doing the ledmaps

So something in the ledmap code is causing the tft to stop working.

first things first, the key matrix needs to exactly map the ledmaps.
all other leds need to be dealt with in some other manner.

issue still persists after getting g_led_config to match the key matrix.

Oooookay had the wiring wrong in info.json.

Turned things all back on including QP...seems to be working fine.

will let it sit for a bit...

kinda feels like maybe the excess matrix thingies were causing an overload or something?

let's try now adding more leds to the led matrix...

I added four leds with a different flag to the g_led_config.
e.g.
led_config_t g_led_config = {
    {
        { 0,  1,  2,  3  },  
    },
    {
        { 1,   0 }, { 2,   0 }, {  3,   0 }, {  4,   0 }, {  5,   0 }, {   6,   0 },
    },
    {
            4, 4, 4, 4, 8, 8
    }
};

note the key matrix is 4, but the led index is 6.  this compiles and seems to work fine.


