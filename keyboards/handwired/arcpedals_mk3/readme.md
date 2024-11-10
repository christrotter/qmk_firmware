# handwired/arcpedals_mk3
*You should not build this.  Probably mk4 will be much better.*

<a href="https://i.imgur.com/7tJTCDT.jpg"><img src="https://i.imgur.com/7tJTCDT.jpg" width="800"></a>

<a href="https://i.imgur.com/XXe5Rpa.jpg"><img src="https://i.imgur.com/XXe5Rpa.jpg" width="400"></a>
<a href="https://i.imgur.com/kXsa6WP.jpg"><img src="https://i.imgur.com/kXsa6WP.jpg" width="400"></a>

After eight interrupted-but-busy months, here we are, with functional mk3 pedals.  Why do this to myself?
- Holding down keys makes my fingers go numb and catch on fire - what other choice do I have?
- Repetitive motions like scrolling make my hands/wrists/arms catch on fire.
- My feet are lazy good-for-nothings who should contribute to the efforts.
- Yet another opportunity to learn and develop.
- The [mk2 pedals](https://kbd.news/ArcBoard-ArcPedals-2162.html) were - though tremendously broken and semi-reliable - a huge help for my work.

# relevant links
- [Full Imgur album](https://imgur.com/gallery/arcpedals-mk3-build-1mGxVUc)
- [Breakout PCB](https://github.com/christrotter/pedal-breakout-pcb)
- [Button PCB](https://github.com/christrotter/microswitch-pcb)
- [Keyboard journey main doc - links to all my build journals and more](https://docs.google.com/document/d/1714zAB5GvLr3M8TnRpMvAdutThKMioJDGraUgG2VCB4/edit?usp=sharing)
- [build journal (~175 pages)](https://docs.google.com/document/d/1cXvQ-VoUu07zbBuVIKwUyOspt1wIibRq1dktp56DD8o/edit?usp=sharing)
- [STL files](https://github.com/christrotter/3d-models/blob/main/keyboards/arcpedals-mk3/README.md)
- [parts printing list](https://docs.google.com/document/d/19vgn_IOVY2ncgV_MKY-XW2Omr_Vd-NVtJHTEubr_N-U/edit?usp=sharing)
- [mk19 keyboard details](https://github.com/christrotter/qmk_firmware/tree/arcboard-series/keyboards/handwired/arcboard_mk19)

# the real challenge
Honestly, you have two problems to solve:
1. Making a button that your foot can comfortably and reliably actuate.
2. Locating buttons in comfortable places.

And then piecing it all together in a coherent way.

# features
- hundreds of parts to print! (_in search of zero support material you get more parts_)
- hundreds of third party parts to source! (_dowels, magnets, inserts, screws, microswitches, pcbs, JST-XH hardware & tool, 6mm dowel rod_)
- hundreds of JST crimps! (_dozens of feet of wiring, wire wrap, heatshrink tubing_)
- `140` leds (_24 for buttons, 46 for indicators - per side_)
- not-quite-there design aspects (_wiring & wiring covers, floor plates, button fitment, pseudo-adjustability_)
- a remote layer indicator/controller/reset device that only exists in my head!
- eight buttons per foot! wowie zowie!
- mega comfy foot perch!
- solid! weighs in at a hearty, beefy, yummy `1.86kg / 4.1lbs`
- \o/

# how I'm using QMK
As is my tradition, I barely use the full power of the firmware package.

It's early days, but this is where I'm at from a keymap perspective (_just showing one half_):
```c
[_SCROLL] = LAYOUT(
        KC_LCTL, KC_LGUI, KC_LSFT, KC_LALT,
    KC_MS_WH_RIGHT, KC_MS_WH_DOWN, KC_CYCLE_LAYERS, KC_CYCLE_LAYERS,
),
    [_ARROWS] = LAYOUT(
        KC_LEFT, KC_UP, KC_LSFT, KC_LALT,
    KC_MS_WH_RIGHT, KC_MS_WH_DOWN, KC_CYCLE_LAYERS, KC_CYCLE_LAYERS,
),
    [_FUSION] = LAYOUT(
        _______, KC_LGUI, _______, _______,
    KC_MS_WH_LEFT, KC_MS_WH_DOWN, KC_CYCLE_LAYERS, KC_CYCLE_LAYERS,
),
    [_MGMT] = LAYOUT(
        _______, _______, QK_BOOT, EE_CLR,
    _______, _______, KC_CYCLE_LAYERS, KC_CYCLE_LAYERS,
)
```

Simply put...
- Navigational / modifier keys
- Dedicated arrow keys (not sure how this will play out)
- Fusion-specific stuff, e.g. pan/orbit
- Management - both halves have the ability to either enter bootloader or clear eeprom

# lessons
Some big ones out of this...
- Building large (_wide pressable surface area_) buttons that reliably actuate over sub-mm distances is kinda hard.
- Pressing down on an angled plane is far more comfortable than trying to swivel your foot horizontally to push something.  I had originally been trying to mimic the 'must be good' MSI Liberator pedal.
- Hinged things require room for the hinged part to swing, dawg.  More effort in Fusion 360 joints would have paid off here.
- To make pedals that weigh in at 3.6kg total requires at least `2x that much filament` in development.
- FDM 3D printing not capable of 'smooth' surface finishes, and your designs should understand this.  e.g. polished metal surfaces have very low friction/stiction - a printed surface can be very ridged!
- Splitting complex parts in half, using dowels to locate the parts, and gluing really helps cut down on PETG support surface woes.
- TPU springs, harder than you'd think.
- The speed of the Prusa MK4S really is impressive, halved all printing time compared to the Prusa MK3S.
- Rendering is able to give you pretty accurate representations of the final product.
- Fusion 360 forms work pretty well when you keep one major form body per project file, and import other form projects into it.
  - skeleton/frame project -> heel form body & bits; -> front-end form body & bits ---> both form projects into 'final assembly' project
- Fusion 360 parameters do not work outside of the origin model - you must upgrade to paid for this functionality.

# highlights in photos

<a href="https://i.imgur.com/HWcTwsK.png"><img src="https://i.imgur.com/HWcTwsK.png" width="800"></a>

<a href="https://i.imgur.com/3J8CH2m.jpg"><img src="https://i.imgur.com/3J8CH2m.jpg" width="800"></a>

<a href="https://i.imgur.com/4nSBUME.jpg"><img src="https://i.imgur.com/4nSBUME.jpg" width="800"></a>

<a href="https://i.imgur.com/CsmT0eQ.jpg"><img src="https://i.imgur.com/CsmT0eQ.jpg" width="800"></a>

<a href="https://i.imgur.com/kzg8itY.jpg"><img src="https://i.imgur.com/kzg8itY.jpg" width="800"></a>
