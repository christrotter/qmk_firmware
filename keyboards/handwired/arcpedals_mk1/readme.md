# handwired/arcpedals_mk1
*QMK-powered foot pedals - offload strain from your hands to your feet!*

![handwired/arcpedals_mk1](https://i.imgur.com/uLY4qxZl.jpg)

* Keyboard Maintainer: [christrotter](https://github.com/christrotter)

## Features
* Foot rest w. layer changing using the ball of your foot; toes get the main functionality
* Split keyboard w. TRRS
* RGB all day long
* JST connector for remote indicator bar
* Modular assembly w. dovetail/M3 connectors
* Prototype jank

## Parts and files
* STLs and Fusion 360 files here: https://github.com/christrotter/3d-models/tree/main/keyboards/arcpedals-mk1
* Hardware Supported: RP2040 w. mxledbit 'container' PCBs, ST7789 TFTs, 3D-printed chassis
* Hardware Availability: 
  * Waveshare RP2040-Plus: https://www.aliexpress.com/item/1005003504708746.html
  * per-key PCB: https://github.com/swanmatch/MxLEDBitPCB/tree/master/container (via JLCPCB)
  * wiring PCB: https://www.amazon.ca/Solderable-Breadboard-Electronics-Gold-Plated-Multicolor/dp/B081MSKJJX
  * TRRS PCB: https://www.aliexpress.com/item/32968034072.html
  * Hotswap sockets: https://www.aliexpress.com/item/4001051840976.html
  * Capacitors: https://www.aliexpress.com/item/32877282377.html
  * LEDs: https://www.aliexpress.com/item/4000475685852.html
  * JST connectors: https://www.aliexpress.com/item/32954418743.html (but I highly recommend buying a JST crimper, connectors, and using 26awg silicone wiring)

## History
I have issues holding keys down and was looking for a way to remove strain from my hands.  Eye/face tracking and voice commands are things I'm also looking into, but pedals seemed more accessible to me at the time.

Anyways I had all the parts sitting around, and after two weeks of work the pedals are operational!

**Things I tried that didn't work:**
* Ball-of-foot pedals only; maybe my implementation was bad, but I couldn't do any kind of rapid keypress actions.
* Adjustable springiness of ball pedals; the design provides for 6 or 7 positions of the fulcrum, and I found 'almost full spring force' best - keeping the base pedals more as foot rests than actionable things
* High-angle toe pedals; you end up having to float your foot and that's bad
* Toe and ball pedals; you end up having to float your foot AND contort it, which is even worse

**Things I considered:**
* 'gas pedal'-like functionality; I had some rheostats and was going to try this, but you'd then lose the ability to do any other kind of functionality.  Maybe one day I'll revisit this.
* 'distortion pedal'-like functionality; foot stop actions are even slower than ball-of-foot
* 'side' buttons, a la MSI Liberator; a lot of ankle penalties with this one, but thought about it

**Things I'll be trying next:**
* v2 will feature 'heel stays put' functionality and focus on making the layer switching easy
* v2 will also have formed pedals, I think
* v1 is going to get a remote indicator/maybe-keys functionality for rapid layer switching/understanding

## Details
* JST connectors make wiring and troubleshooting much easier.  Much, much, much easier.  USE A FLUX PEN WHEN SOLDERING WOW.
* I used some old Grifiti wrist pad (palm rest) (about 3/4"/~20mm neoprene pad) for the heel pads.
* The wiring covers are separate parts for reasons I can't now remember.
* I used prototypes of the MCU holder as wire retainers; the latest design includes the capacity for making a wire retainer part.
* Can't recommend JST XH 2.54 connectors enough, have really made a difference in packaging/assembly/troubleshooting my prototypes!

![handwired/arcpedals_mk1](https://i.imgur.com/uLY4qxZ.jpg)
![handwired/arcpedals_mk1](https://i.imgur.com/QyyWODa.jpg)
![handwired/arcpedals_mk1](https://i.imgur.com/PbXtXyX.jpg)
![handwired/arcpedals_mk1](https://i.imgur.com/9EiABB0.jpg)

More pictures here: https://crazymittens.imgur.com/all


## Bootloader and flashing
First, update the variables in build.sh to suit user/build cores/etc.
```shell
#!/bin/bash
KB_PATH=handwired/arcpedals_mk1 #<--- this
HOME_DIR=/Users/christrotter/git/printing/qmk_firmware #<--- this
KB_DIR=$HOME_DIR/keyboards/$KB_PATH
USER_DIR=$HOME_DIR/users/christrotter #<--- this

BUILD_CORES=12 #<--- this (figure out how many logical CPU cores you have, adjust number accordingly)
KEYMAP='christrotter' #<--- this
KEYBOARD='handwired/arcpedals_mk1' #<--- this
```
Make example for this keyboard (after setting up your build environment):

    ./build.sh build

Flashing example for this keyboard:

    ./build.sh left
    ./build.sh right

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the left-most ball-of-foot pedal and plug in the keyboard
* **Physical reset button**: Quickly (within 250ms) double-press the 'boot' button on the PCB
* **Keycode in layout**: There is a 'MGMT' layer that has `QK_BOOT` and `EE_CLR` buttons available.
