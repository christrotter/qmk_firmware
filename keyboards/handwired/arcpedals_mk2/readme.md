# handwired/arcpedals_mk2
*QMK-powered feet spaceships!*

![handwired/arcpedals_mk2](https://i.imgur.com/2YFsvdz.jpg)
![handwired/arcpedals_mk2](https://i.imgur.com/et9Df2X.jpg)
![handwired/arcpedals_mk2](https://i.imgur.com/S3UdNZw.jpg)

* Demo of trackball: https://youtu.be/Bjl8MWTQXys
  * This is very silly.  You could easily do the same thing with a simple button.
* Demo of foot switch: https://youtu.be/YfFeX6zHOLo
  * Note this is pre-sanding - the noise is all the layers scraping together
* **More pictures here:** https://imgur.com/a/wuah6Nh

* Keyboard Maintainer: [christrotter](https://github.com/christrotter)

## Four weeks in usage notes
* Really need to fix the toe button, but I think the real issue is that at the end of the day, the spring/mx-switch mechanism is too much travel, full stop.
  * so, i will be making some microswitch pcbs for this
* Probably due to the high travel/wide spacing, i really only ever use the toe button.
  * the side buttons are too much foot travel to be comfortable
  * what i am imagining as the logical next step is that there would be two or three toe buttons, much smaller, and much lower travel; the pedal area would be 'effectively exactly the outline of your foot'; the side buttons would stay but also move to microswitches
* even though i only ever use the toe button, it's been massively helpful and i will never go back.
* the trackball for layer changing is very entertaining and a fun desk piece, but ultimately you have to reach pretty far; how to avoid that?
  * also, you barely ever change layers; this seems an antipattern somehow...
  * you barely ever change layers, so this is not really that big of a deal
* someone called me out for white showing dirt, and it sure does, but that's ok
  * they get pretty dirty and i don't really want to vacuum them!
* visiting children find the whole setup fascinating and entertaining; job done
* Discovered that the pedals will probably always be standalone, as there's no QMK concept of 'two sets of layers and layer states'.  (which is totally fine)
* Discovered that you can do gpio triggering from QMK...so what would that mean for our 'sync' conundrum?

## Two weeks in usage notes
* Toe button sticks a lot - ideally we move to something with less travel
  * mk3 do diy pcb, microswitch/led
* Side buttons are handy but not very ergonomic; mk3 should have more toe buttons in a splay?
* The trackball works great but I don't actually switch layers that often
* led ring is super fun but turns the red ball black when looking at it - a transparent ball w. frosted surface would be ideal...
  * bomtarnes resin-printed a trackball with these characteristics...
* My heels go numb after a while - a me-problem? ... probably just me...?

## Features
* Four buttons per foot
* Trackball-powered layer switcher with integrated RGB indicator
* RGB all day long
* Prototype jank in spades

## Details
* Four buttons per foot
  * Pivot your foot on the heel left or right
  * Press hard on ball of foot
  * Press lightly with your big toe
* Adjustable heel cup distance (extend and re-print one small part)
* Split-keyboard allows you to move each foot wherever is most comfortable
* Tool-less wiring cover makes the build/troubleshooting a little less tiresome
* Silly trackball allows for layer switching - swipe ball left/right/up/down to change layers
  * I found on mk1 that I didn't change layers very often
  * You only have so many places to put functional foot buttons
  * Using a desk-mounted switcher is entertaining and maximizes button functionality
  * Design includes upper and lower shims for micro-adjustments w. minimal re-prints (PMW sensor lens-to-ball distance is a very tight tolerance)
* Management layer for eeprom resets and quick bootloader-ing
* "ledmap" code makes for easier per-key LED-ing

![handwired/arcpedals_mk2](https://i.imgur.com/uLvFw8G.png)
![handwired/arcpedals_mk2](https://i.imgur.com/v1zb3KZ.png)
![handwired/arcpedals_mk2](https://i.imgur.com/DY65eGE.png)
![handwired/arcpedals_mk2](https://i.imgur.com/F6Qt3zf.png)
![handwired/arcpedals_mk2](https://i.imgur.com/KEk4hFD.png)

## Links and files
* ArcPedals-mk1: https://github.com/christrotter/qmk_firmware/blob/arcboard-series/keyboards/handwired/arcpedals_mk1/readme.md
* ArcBoard-mk17: https://github.com/christrotter/qmk_firmware/tree/arcboard-series/keyboards/handwired/arcboard_mk17
* STLs and Fusion 360 files here: https://github.com/christrotter/3d-models/tree/main/keyboards/arcpedals-mk2
* Build journal: https://docs.google.com/document/d/1714zAB5GvLr3M8TnRpMvAdutThKMioJDGraUgG2VCB4/edit?pli=1#heading=h.r2089kgowj5j

## History
**Things I tried that didn't work:**
* mk1 pedals :D

**Things I considered:**
* _microswitches for buttons_ - but they require a pcb really, and I haven't dipped my toes into that deep pool
* _using forms to design the shell_ - I chickened out
* _backlighting the mk2 lettering_ - would have required re-printing the shell pieces

**What needs work:**
* The end plate does too much - assembly is awkward - maybe will be ok with the next item fixed...
* The rp2040 holder, trrs pcb holder, and jst holder all need to be merged into one piece.
* The base principles of the button motion mechanics really require a polished finish and tighter tolerances.  Had to do sanding to 220 grit to make it usable.
* The design of the spring/button retention coupled with the loose tolerances causes the button to catch on surfaces if not pressed dead-center.
* Spring tension is critical on the ball-switch, cuz you are resting your foot pressure on it.
* The trackball cable is a mega-jank JST 7-pin w. loose wires.  I got some wire sleeving but couldn't figure out how to route it quickly/easily.  Next time want to do a USB cable.

**Things I'll be trying next:**
* the location of the buttons is not perfect - toe button needs to come back toward the heel a bit
* tight tolerances, polishing, plus grease/lube
* a 'bridge' button (lift the foot to press)
* two toe buttons

## Parts information
* Hardware Supported: RP2040 w. mxledbit 'container' PCBs, ST7789 TFTs, 3D-printed chassis
* Hardware Availability: 
  * Waveshare RP2040-Plus: https://www.aliexpress.com/item/1005003504708746.html
  * per-key PCB: https://github.com/swanmatch/MxLEDBitPCB/tree/master/container (via JLCPCB)
  * wiring PCB: https://www.amazon.ca/Solderable-Breadboard-Electronics-Gold-Plated-Multicolor/dp/B081MSKJJX
  * TRRS PCB: https://www.aliexpress.com/item/32968034072.html
  * PMW3360: https://www.tindie.com/products/jkicklighter/pmw3360-motion-sensor/
  * Hotswap sockets: https://www.aliexpress.com/item/4001051840976.html
  * LEDs: https://www.aliexpress.com/item/4000475685852.html
  * LED ring: https://www.amazon.ca/dp/B07G9YH3HF
  * Spring steel: https://www.amazon.ca/dp/B0B491L6LV
  * M3 hot-melt inserts: https://cnckitchen.store/products/gewindeeinsatz-threaded-insert-m3-standard-100-stk-pcs
  * JST connectors: I highly recommend buying a JST crimper, connectors, and using 26awg silicone wiring - i got all of this off aliexpress
  * Trackball: 55mm, from a Kensington Expert

## Printing notes
* You will need m3 inserts from here: https://cnckitchen.store/products/gewindeeinsatz-threaded-insert-m3-standard-100-stk-pcs
  * The insert holes in the model are designed for this part's dimensions: 3.9mm holes, 8-10mm deep.
  * I found these inserts far superior to the cheapies online, hold better, goes in much nicer.
  * I did not design the Fusion stuff to easily replace this dimension, sorry.  :(
* The end plate needs to be printed vertically, turns out horribly when flat.
* The button 'dowels' need sanding, plus the sockets where they insert need sanding, I went to 220 grit.
* 100hrs of printing per side, roughly.
* I used PETG - this is probably a requirement for parts like the wiring cover and buttons.

## Spring notes
* tl;dr: Under tension, wrap the spring steel around a dowel with desired spacing and length
* https://www.youtube.com/watch?v=Us28iaPOitU
* I used some old laser printer rods that alread had a hole drilled through
* The dowel size you use should be like 25% smaller than your final spring's desired ID (interior diameter), cuz it expands upon releasing tension
* Don't use your expensive flush cutters on thick spring steel; I used a dremel with cut-off wheel
* The toe/side switches have springs really just light enough to provide "button return" power
* Ball switch has springs strong enough to support my foot at rest; 1.5mm maybe?

![handwired/arcpedals_mk2](https://i.imgur.com/CRVOIf6.jpg)

## Bootloader and flashing
First, update the variables in build.sh to suit user/build cores/etc.
```shell
#!/bin/bash
KB_PATH=handwired/arcpedals_mk2 #<--- this
HOME_DIR=/Users/christrotter/git/printing/qmk_firmware #<--- this
KB_DIR=$HOME_DIR/keyboards/$KB_PATH
USER_DIR=$HOME_DIR/users/christrotter #<--- this

BUILD_CORES=12 #<--- this (figure out how many logical CPU cores you have, adjust number accordingly)
KEYMAP='christrotter' #<--- this
KEYBOARD='handwired/arcpedals_mk2' #<--- this
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
