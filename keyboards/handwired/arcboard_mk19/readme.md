# handwired/arcboard_mk19
<a href="https://i.imgur.com/nll7tnS.jpg"><img src="https://i.imgur.com/nll7tnS.jpg" width="800"></a>
<a href="https://i.imgur.com/3L5ygCA.jpg"><img src="https://i.imgur.com/3L5ygCA.jpg" width="800"></a>

*KeyDesk? DeskBoard? UltraDorito?*

Introducing ArcBoard mk19, the latest in a line of medical needs-focused input devices that allow you to operate a computer while...
- keeping flat, at-rest hands
- avoiding long keypressses & awkward combinations
- avoiding any kind of 'dedicated mouse/trackball' devices
- minimizing repetitive motions
- accelerating keymap learning through the use of LED colours
- not looking like a medical device

Despite all of that, as a good anecdote, **these boards have enabled me to continue working for over two years now**.  The magic really is in the thumb trackball and relaxed posture.

Full Imgur album: https://imgur.com/a/z9URBAb

# The keyboard WE built
So many folks contributed to this build - some with silliness and encouragement (_the cactus, the coffee cup warmer_), others with significant design or tech contributions (_burkfers, GeorgeN, ErikN, bomtarnes, Wimads, Yingeling, Dasky, casuanoob, so many more_), and especially Quentin from BKB for allowing me to pollute his discord server.  Many thanks, and I look forward to future learnings.

<a href="https://i.imgur.com/vcvHMnO.jpg"><img src="https://i.imgur.com/vcvHMnO.jpg" width="300"></a>
<a href="https://i.imgur.com/Vhyt6kz.jpg"><img src="https://i.imgur.com/Vhyt6kz.jpg" width="300"></a>
<a href="https://i.imgur.com/Mdz08AQ.jpg"><img src="https://i.imgur.com/Mdz08AQ.jpg" width="300"></a>
<a href="https://i.imgur.com/luSWp12.jpg"><img src="https://i.imgur.com/luSWp12.jpg" width="300"></a>

# Features
There's both a lot going on and not that much going on...at the same time.

## But what about the pedals????
Yup, info here: 
- https://github.com/christrotter/qmk_firmware/tree/arcboard-series/keyboards/handwired/arcpedals_mk2
- https://kbd.news/ArcBoard-ArcPedals-2162.html

Also have some new buttons ready to test: https://github.com/christrotter/microswitch-pcb/

## Ergonomics
I would note that I'm not a medical professional, but I did sleep at a Best Western last night.  

The layout itself has not changed for a while - both mk13 and mk17 used the same basic curvatures, trackball location, etc - and indeed mk17 as a whole was the tracing aid for mk18 and mk19.

<a href="https://i.imgur.com/HJl8do1.jpg"><img src="https://i.imgur.com/HJl8do1.jpg" width="300"></a>
<a href="https://i.imgur.com/D39sQPG.jpg"><img src="https://i.imgur.com/D39sQPG.jpg" width="300"></a>

### In practice
The benefits I get from this board are:
- Never move your fingers from homerow yet still mouse using the thumb trackball and auto-mouse layer.
- Moving functionality from pinkies to thumbs reduces strain and pinky pain.

Other ergonomic improvements...
- Indicator brightness is normally dim, and then when you trigger an indicator (_e.g. oneshot shift_) it raises indicator brightness by 2-3x, helping with off-center visual comprehension
- Four encoders - two on each half - with generous 70mm knobs allow you to offload repetitive actions.
  - _e.g. alt-tab, scrolling, cycling through browser tabs, volume, zoom, etc_
  - The screens are also buttons!
- Grifiti FatMat palm rests (18mm thick neoprene) reach all the way out to the macropad, making every action comfy.
- Large 1.5u thumb keycaps make for comfortable thumb actioning, with six thumb keys available.
  - _sourced from the Moonlander, which is obviously not going to be cheap to replicate_
- Tailored switches:
  - Box silent pink for regularly used keys
  - Box white clicky for f-keys and macro keys
  - Gateron clear for keys that need zero friction
  - Ultrafalcon TFT buttons use Box navy

## Functionality
Right-half has a PMW33xx sensor with a 34mm trackball on NSK roller-bearings.  Each side have dedicated arrow keys (or any keys) via directional pads at your thumb-tips.

<a href="https://i.imgur.com/ZEtqWpZ.jpg"><img src="https://i.imgur.com/ZEtqWpZ.jpg" width="300"></a>
<a href="https://i.imgur.com/DB81dCi.jpg"><img src="https://i.imgur.com/DB81dCi.jpg" width="300"></a>

There are 51 keys/side [keywell(5x6) + thumbs(6) + 5-way(5) + falcons (2 push-buttons) + macropad (8)]
<a href="https://i.imgur.com/tnc6MSk.jpg"><img src="https://i.imgur.com/tnc6MSk.jpg" width="600"></a>

The encoders are a whole thing, see the link: https://github.com/christrotter/ultrafalcon

<a href="https://i.imgur.com/S5YIfKW.jpg"><img src="https://i.imgur.com/S5YIfKW.jpg" width="300"></a>

## Learning
<a href="https://i.imgur.com/oLM7SkP.jpg"><img src="https://i.imgur.com/oLM7SkP.jpg" width="600"></a>

- Addressable LEDs on each button for rapid learning of your custom keymaps.
  - In fact, so many LEDS that I ran into overflow problems in code, and had to add a 2nd QMK controller.
  - Across both halves, ~330 LEDs?  ~100 LEDs just for keys, ~120 LEDs on the encoders, ~10-? for the indicators, and ~100 for the VaniLED (_i.e. underglow_)
- Self-awareness: make a list of your common shortcuts, program features you use, specific pain points.  Take this list and look into automation via macros or keyboard shortcuts.  QMK-ify what you can!  Re-route/find alternatives for what you can't.

## Customizability
The flat encoder segment can be swapped out for another type of device, like a USB SpaceMouse Compact or touchpad - or anything you can think of.

<a href="https://i.imgur.com/xklBrFP.jpg"><img src="https://i.imgur.com/xklBrFP.jpg" width="600"></a>

The two integrated 8-key macropads allow one-key functions for whatever shortcuts you need. 

<a href="https://i.imgur.com/3M44gZW.jpg"><img src="https://i.imgur.com/3M44gZW.jpg" width="600"></a>

Each keyboard half has two individually addressable 1.25" GC9A01 circular LCDs that are attached to MX switches.

<a href="https://i.imgur.com/u552Hhd.jpg"><img src="https://i.imgur.com/u552Hhd.jpg" width="600"></a>

A bank of dedicated indicator LEDs allow whatever state you want to be made visible.  They can be further extended via the LED signal/power/ground output (_third USB-C port_) for screen-mounted indicators.

<a href="https://i.imgur.com/Q4pYmZR.jpg"><img src="https://i.imgur.com/Q4pYmZR.jpg" width="600"></a>

The "slats" lighting is fully customizable via the secret 7-key keyboard hidden under the palm rests.  It uses QMK's `rgblight` feature with most animations enabled.

<a href="https://i.imgur.com/yRw2KzA.jpg"><img src="https://i.imgur.com/yRw2KzA.jpg" width="300"></a>
<a href="https://i.imgur.com/WbLgkzP.jpg"><img src="https://i.imgur.com/WbLgkzP.jpg" width="300"></a>

<a href="https://i.imgur.com/lBhUcKl.jpg"><img src="https://i.imgur.com/lBhUcKl.jpg" width="300"></a>
<a href="https://i.imgur.com/EfHsPB7.jpg"><img src="https://i.imgur.com/EfHsPB7.jpg" width="300"></a>

# Assembly
Due to a number of constraints (_printer plate size chief among them_), the shell of the keyboard is comprised of a number of segments connected via dovetails and screws that is quite rigid when everything is screwed together.

- Custom RP2040 microcontroller pcb and flex-pcb interconnect designed to integrate with the Cyboard flex-pcb system
- USB-C connectivity for all external wiring - main usb in, split connection, screen-mounted indicators
- No glue in the assembly, so future customization just a print away.
- Minimal amount of soldering required.
- Open-source models, schematics, and code.

<a href="https://i.imgur.com/jrJZMWU.jpg"><img src="https://i.imgur.com/jrJZMWU.jpg" width="800"></a>

## STL files
Most of them are available here: https://github.com/christrotter/3d-models/tree/main/keyboards/arcboard-mk19
<a href="https://i.imgur.com/cK5dK9k.jpg"><img src="https://i.imgur.com/cK5dK9k.jpg" width="800"></a>

Github won't let me upload the F3Z fusion backup, but there's a dropbox link in the readme there.

Suffice to say there are like 50 STL files per half, soooo have fun with that.  Everything prints on a Prusa MK3S plate (_210 x 210 mm_).

**Key point:  I calculated it at some point - expect something like 250+ hours of total printing.**

Note that some of the parts need 'clear' filament, and some parts, like the diffuser sheets, are designed to be used with white filament.

I'd also be aware that I spent quite a lot of time with a chisel and pick, and one or two interior pieces needed quite a lot of hacking to fit - never got around to fixing that in Fusion, sorry!

# Development
New learnings on this build were...
- custom pcb design in Kicad
- SPI shift-registers and custom QMK matrix code
- flex-pcb design
- integrated-microcontroller pcb design
- learning how to deal with pcb assembly
- working with manufacturer sponsorships and pcb industry standards
- how to sheathe cable using flex-weave

<a href="https://i.imgur.com/LSF9lwF.jpg"><img src="https://i.imgur.com/LSF9lwF.jpg" width="300"></a>
<a href="https://i.imgur.com/E5y8A3d.jpg"><img src="https://i.imgur.com/E5y8A3d.jpg" width="300"></a>
<a href="https://i.imgur.com/9KDiLHO.jpg"><img src="https://i.imgur.com/9KDiLHO.jpg" width="300"></a>
<a href="https://i.imgur.com/wljKoSO.jpg"><img src="https://i.imgur.com/wljKoSO.jpg" width="300"></a>
<a href="https://i.imgur.com/nxRyYub.jpg"><img src="https://i.imgur.com/nxRyYub.jpg" width="300"></a>
<a href="https://i.imgur.com/KmsC67y.png"><img src="https://i.imgur.com/KmsC67y.png" width="300"></a>

This article came out of the mk18/mk19 Fusion work: https://kbd.news/From-switchbody-to-3D-keywell-2225.html

And the shift register work that Burkfers and I did was very helpful in understanding how the QMK matrix stuff works, plus provided a [VIK module](https://github.com/sadekbaroudi/vik?tab=readme-ov-file#modules)  for the community: https://github.com/christrotter/shift-register-spi-breakout-pcb

<a href="https://i.imgur.com/zpPm7Fv.jpg"><img src="https://i.imgur.com/zpPm7Fv.jpg" width="300"></a>
<a href="https://i.imgur.com/bXJ338i.jpg"><img src="https://i.imgur.com/bXJ338i.jpg" width="300"></a>

## Family picture for Dasky
<a href="https://i.imgur.com/JmNemlQ.jpg"><img src="https://i.imgur.com/JmNemlQ.jpg" width="800"></a>

# Any existing issues?
Still have a lot of work to do on the UI and screen functionality, including figuring out how to deal with the screen rotation limitations.  QMK/chibios only allows for 4 rotation angles - I need 'input the angle' levels of rotation adjustment.

There's also a mystery issue where the board reboots when I get up out of my chair.  But _only_ if I'm getting up to leave my office.  Very mysterious.

And I still haven't gotten to the screen-mounted indicators...

# What are the gotchas and limitations?

Well, repetitive mousing (_e.g. games_) is still a challenge, which is not a bad constraint, as it requires you to learn a lot of keyboard shortcuts.  And frankly, for me, it's not going to be solved by any keyboard, so I can live with this.

I found that despite my best efforts, repetitive movements like scrolling needed to be moved to the feet.  There's perhaps a good dose of 'my particular situation' here, but even with making it as easy as possible I still found scrolling to be best done by my feet.

Finally, without an understanding of QMK, coding, and microcontroller flashing to customize the board, you're kinda stuck.  So some sort of intrinsic motivation to learn is required!

# What would I do differently next time?
The macropad was a new experiment for me - I would definitely take a different approach for next time.  (_the location is not ideal, and the raised keys didn't play out quite how I'd imagined_)

As much as I really don't like FPC/FFC, I'd probably move to that exclusively, or perhaps move to a smaller JST framework.  The 2.54mm spacing really is huge.

I'd also look at flipping the mainboard upside down, so accessing the plugs/wires/cables doesn't require gingerly unplugging the shorter cables to get full access.  This will require a bit more height, but would be worth it.

The keywell area also didn't get a PCB retention system, like the thumb keys.  This is fine if you never hotswap...but that's a silly limitation.  The retention system really needs to be designed in from day1; retrofitting it did not pan out well, especially with the mainboard directly in that area.

I still haven't looked at Via support, but then again nobody else uses these boards so this is not a priority.

The left thumb keys are also still just a mirror of the right, which is sized for a trackball.  I need to do a better job with the model to allow for left/right adjustments.

# Supporting projects
Turns out you can get quite a bit done in five months.  I had never used Kicad before this project, and now the project would not exist without it!  Many thanks to those folks.

## Cyboard's flex pcb system
This was really the genesis for spurring me on to the other projects.  Or perhaps the boot that kicked me down the rabbit hole of yak shaving.  Either way, very grateful for Erik's work and encouragement!  "An mcu daughterboard is super easy - make your own!"

https://www.cyboard.digital/product-page/dactyl-flex-pcbs

And when I ran into issues with broken PCBs (_due to manhandling_), or needing more PCBs, he was ready to help out.

<a href="https://i.imgur.com/DsyhVKL.jpg"><img src="https://i.imgur.com/DsyhVKL.jpg" width="300"></a>
<a href="https://i.imgur.com/pppaV7b.jpg"><img src="https://i.imgur.com/pppaV7b.jpg" width="300"></a>

## Dpad pcb
This went through three iterations as well - first RKJXT, then a micro-5way, then a normal dpad but with LEDs.
- RKJXT: https://github.com/christrotter/rkjxt-mini-breakout
- micro-5way: https://github.com/christrotter/5way-pcb
- dpad-inator: https://github.com/christrotter/microswitch-dpad

<a href="https://i.imgur.com/UflfgbG.jpg"><img src="https://i.imgur.com/UflfgbG.jpg" width="300"></a>

## Extended Cyboard flex pcb
Unfortunately the factory Cyboard flex pcb was very much too short for my thumbcluster, so with support from Erik from Cyboard, I made my own.
- https://github.com/christrotter/mk19-flex-pcb

<a href="https://i.imgur.com/aXGwML6.jpg"><img src="https://i.imgur.com/aXGwML6.jpg" width="300"></a>
<a href="https://i.imgur.com/Gtk579X.jpg"><img src="https://i.imgur.com/Gtk579X.jpg" width="300"></a>
<a href="https://i.imgur.com/GszzoUk.jpg"><img src="https://i.imgur.com/GszzoUk.jpg" width="300"></a>

## RP2040 mainboard
Three iterations led me to finally do away with soldering and put everything on one board.
- v1: https://github.com/christrotter/mk18-pcb
- v2: https://github.com/christrotter/mk19-pcb
- v3: https://github.com/christrotter/mk19-rp2040

<a href="https://i.imgur.com/k1x1K6Z.jpg"><img src="https://i.imgur.com/k1x1K6Z.jpg" width="300"></a>
<a href="https://i.imgur.com/54Q5Jzf.jpg"><img src="https://i.imgur.com/54Q5Jzf.jpg" width="300"></a>

## Macropad - Cyboard 8-key breakout
If I had to do this over again, I would not use the Cyboard single-key pcbs, but rather make a custom macropad pcb.  The 0.3mm cables are $3 each.  A custom board would also help provide options for other switches or encoders, leds, etc.
- https://github.com/christrotter/macropad-pcb

<a href="https://i.imgur.com/WExQMjI.jpg"><img src="https://i.imgur.com/WExQMjI.jpg" width="300"></a>

## Encoders - Ultrafalcon
Such drama, but ended up working out nicely.  They use the Bourns PER60 encoder.
- https://github.com/christrotter/ultrafalcon

More images here: https://imgur.com/a/Sfy7IT9

# Materials
- 3mm hot-melt inserts
- Prusament PETG (signal white, urban grey, galaxy black, clear)
- Cyboard pcb kit
- Aliexpress-sourced
    - JST-XH plugs/sockets/pins
    - RGB LED strips
    - barrel plugs/connectors, assorted FFC/FPC cables
    - MX and other switches
    - silicone-sheathed 26-awg hookup wire
    - various breakout boards for testing and troubleshooting

# Tools used
- Fusion360 for all design work
- Kicad w. JLC fab plugin
- FireAlpaca for sketching w. tablet
- github, VS Code
- Prusaslicer & Prusa MK3S
- temp-controlled soldering iron & various small tools, flux, 0.8mm & 0.25mm solder
- sharp .25" chisel & various small picks
- 6" scale w. millimeters and cheap digital calipers
- JST crimper
- multimeter
