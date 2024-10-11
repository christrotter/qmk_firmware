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

ok so this code sort of works.
but the non-key leds consume ledmap items...breaking split.

So, this is how you get it working.

except split doesn't work.

Setting manually the leds to call from the led index...
// right side
christrotter:handwired/arcboard_mk17_tft:1: led: 4 hsv: 0,0,50
christrotter:handwired/arcboard_mk17_tft:1: led: 5 hsv: 0,0,50
christrotter:handwired/arcboard_mk17_tft:1: led: 6 hsv: 43,255,30
christrotter:handwired/arcboard_mk17_tft:1: set led: 6
christrotter:handwired/arcboard_mk17_tft:1: led: 7 hsv: 43,255,30
christrotter:handwired/arcboard_mk17_tft:1: set led: 7
// left side
christrotter:handwired/arcboard_mk17_tft:1: led: 0 hsv: 128,255,50
christrotter:handwired/arcboard_mk17_tft:1: set led: 0
christrotter:handwired/arcboard_mk17_tft:1: led: 1 hsv: 170,255,50
christrotter:handwired/arcboard_mk17_tft:1: set led: 1
christrotter:handwired/arcboard_mk17_tft:1: led: 2 hsv: 128,255,30
christrotter:handwired/arcboard_mk17_tft:1: set led: 2
christrotter:handwired/arcboard_mk17_tft:1: led: 3 hsv: 128,255,30
christrotter:handwired/arcboard_mk17_tft:1: set led: 3

So the ledmap index call is blowing up...
if we exclude flags for 2,3...
christrotter:handwired/arcboard_mk17_tft:1: led: 2 hsv: 234,128,50
christrotter:handwired/arcboard_mk17_tft:1: set led: 2
christrotter:handwired/arcboard_mk17_tft:1: led: 3 hsv: 191,255,50
christrotter:handwired/arcboard_mk17_tft:1: set led: 3
christrotter:handwired/arcboard_mk17_tft:1: led: 6 hsv: 43,255,30
christrotter:handwired/arcboard_mk17_tft:1: set led: 6
christrotter:handwired/arcboard_mk17_tft:1: led: 7 hsv: 43,255,30
christrotter:handwired/arcboard_mk17_tft:1: set led: 7

Now it's getting the correct values, but failing to actually turn on the leds...

theory: 
- on left side, ledmap and led-flag index agree
- left side: ledmap says, led0 gets hsv_this; led-flag says, apply to led0
- right side: ledmap says, led2 gets hsv_this; led-flag says, we don't have a led2, do nothing
cuz split works like...
- take led-flag range, split by config param
- therefore left sees 0-3 of led chain; right sees 4-7 of led chain



ok, multi-line ledmap testing

left side is working correctly
right side, zero working

it's like rgb matrix is not even starting...
ok, the background lighting is working, but not rgb matrix
something wonky with flags!!  turning off the 'if flag' addresses the issue. (this was due to not making the led matrix chagnes everywher)

christrotter:handwired/arcboard_mk17_tft:1: starting rgb range...range: 6 to 9
christrotter:handwired/arcboard_mk17_tft:1: og led: 6
christrotter:handwired/arcboard_mk17_tft:1: indexed led: 2
christrotter:handwired/arcboard_mk17_tft:1: reverted led/hsv: 6 85.255.50
christrotter:handwired/arcboard_mk17_tft:1: og led: 7
christrotter:handwired/arcboard_mk17_tft:1: indexed led: 3
christrotter:handwired/arcboard_mk17_tft:1: reverted led/hsv: 7 0.255.50
christrotter:handwired/arcboard_mk17_tft:1: og led: 8
christrotter:handwired/arcboard_mk17_tft:1: indexed led: 4
christrotter:handwired/arcboard_mk17_tft:1: reverted led/hsv: 8 234.128.50
christrotter:handwired/arcboard_mk17_tft:1: og led: 9
christrotter:handwired/arcboard_mk17_tft:1: indexed led: 5
christrotter:handwired/arcboard_mk17_tft:1: reverted led/hsv: 9 191.255.50

ok, seems to be working now...but need more leds to test properly.
i think it'll work fine tho.

the key thing seems to be 'minus the gap out'.
-2 worked on the single-row config cuz there were 2 indicator leds on the left side.
-2 works on the multi-row config cuz there are 2 indicator leds on the left side.
-4 and -6 do not work cuz there are only 2 indicator leds on the left side.

ok, so next step is ensuring that there is logic that doesn't blow up for falcons/indicator handling.
also, can we just make up our own flags?
yes, yes you can.



