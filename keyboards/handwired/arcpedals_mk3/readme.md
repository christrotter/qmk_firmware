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

## button design
- Building large (_wide pressable surface area_) buttons that reliably actuate over sub-mm distances is kinda hard.
- Pressing down on an angled plane is far more comfortable than trying to swivel your foot horizontally to push something.  I had originally been trying to mimic the 'must be good' MSI Liberator pedal.
- The feel/tactility of a button is extra important when you cannot see what your feet are doing - it's important to feel like you're doing something.
- Hinged things require room for the hinged part to swing, dawg.  More effort in Fusion 360 joints would have paid off here.
- The shorter your switch travel, the finer your tolerances need to be - i.e. add shims to your design for fine-tuning.
- Super-wide buttons require X and Y stabilizers.
- Dowel/sleeve configurations require effectively zero runout to work smoothly.
- Magnets are strong, but feet are stronger.
- TPU springs, harder than you'd think.

## general design
- Integrate floor plates into the main frame - it's fiddly trying to make them snap into place otherwise.
- Cheap stuff, cheap tolerances.
- In your design of a thing that will be mirrored, `THINGS THAT DO NOT NEED TO BE ASYMMETRICAL SHOULD BE SYMMETRICAL`.  Wasted hours and a lot of filament because parts that truly should have been usable on either side were not.
- Corollary: `If a part must be asymmetrical, indicate its directionality.`
- If you think very early on, man, that's silly how the things is not symmetrical - `SEE ABOVE WOW`.
- Wires/sleeving is very hard to represent in 3D, and therefore your design will inevitably not allow for enough space for them and you will be sad.
- Hex holes work much better for pressing magnets into.
- Design through holes to allow you to poke press-fit parts back out if necessary - these can help with support removal.

## workflow
- If you have a solid vise/workbench, don't insist on sitting at your desk trying to do chisel work.
- Take the time to make jigs, especially if you need any kind of accuracy in the finished part.
  - e.g. the diffuser for the heel leds is a flat part, 0.7mm thick, that has curved ends.  If I'd taken the time to make a jig, it would not look terrible.
  - e.g. the button hinge holes are drilled.  I made a jig that allows the button part to clip in so I get consistent drill holes every time.

## printing
- To make pedals that weigh in at 3.6kg total requires at least `2x that much filament` in development.
- FDM 3D printing not capable of 'smooth' surface finishes, and your designs should understand this.  e.g. polished metal surfaces have very low friction/stiction - a printed surface can be very ridged!
- FDM 3D printing can create really accurate models, but not perfect models - 0.05mm runout over 20mm is enough to cause binding in a dowel/sleeve configuration.
- The speed of the Prusa MK4S really is impressive, halved all printing time compared to the Prusa MK3S.
- If your material is too thin, even an M3 screw will crack it.
- Splitting complex parts in half, using dowels to locate the parts, and gluing really helps cut down on PETG support surface woes.
- When using dowels, undersize the dowel by 1% so your press-fit does not require hydraulic machinery to fit.
- Wait for PETG to cool to ~45C - on the textured build plate it just pops itself loose.
- Clean the textured build plate after every print with 90%+ isopropyl alcohol, I stopped getting layer shifting issues after implementing this.
- PETG supports come off of non-round holes better than round...
- A sharp, small, rounded woodworker's gouge works great for cleaning up support material from M3 insert/dowel holes.

## pcb's & electrical
- Definitely make sure that for newly-designed PCBs you have a PCB test procedure.
- Have the GND pad always be the square pad; be consistent.
- If you are sick, and perhaps tired, do not solder or wire - things will be done backwards and you'll end up re-doing it.

## fusion360
- Rendering is able to give you pretty accurate representations of the final product - duplicate existing materials in Fusion 360 to unlock editing them, custom colours!
- Ideally leave your appearance overrides off until you get to the last assembly model - you can't override inherited appearance choices.
- When applying appearances, do so at the component level, not body - very hard to track down otherwise!
- `USE THE FUSION TIMELINE TO MAKE CHANGES`.  Period.  If you find yourself modifying an object later on instead of going back to edit the original instantiation of it, you will eventually hit an impassable wall of broken design features.
- Constrain your sketches - just do it.
- Don't tie your dimensions to projected lines; rather reference the origin.
- Design for 'melding' your components together; then use joints to hold the parts together.
- In Fusion 360, don't use form-body's as your profiles, wherever possible - they are not consistent and create grief.
- Fusion 360 forms work pretty well when you keep one major form body per project file, and import other form projects into it.
  - skeleton/frame project -> heel form body & bits; -> front-end form body & bits ---> both form projects into 'final assembly' project
- Fusion 360 parameters do not work outside of the origin model - you must upgrade to paid for this functionality.
- The free version of Fusion 360 allows you to have USD$1000/year income, then you must upgrade to paid.

# materials
- M3 screws and inserts; mostly 8mm, some 10, some 12
- JST-XH 2.54mm 6-pin, 4-pin
- wire sleeve & heatshrink tubing & silicone-sheathed 26-awg hookup wire
- RGB WS2812 LED strip (cut to fit pieces)
- PETG filament (black, dark grey, light grey, white), silk PLA silver, 40A TPU
- 2x RP Pico
- 2x custom breakout PCB (no factory PCB-Assembly) https://github.com/christrotter/pedal-breakout-pcb
- 16x custom microswitch PCBs (w. factory PCB-Assembly) https://github.com/christrotter/microswitch-pcb

# highlights in photos

<a href="https://i.imgur.com/HWcTwsK.png"><img src="https://i.imgur.com/HWcTwsK.png" width="800"></a>

<a href="https://i.imgur.com/3J8CH2m.jpg"><img src="https://i.imgur.com/3J8CH2m.jpg" width="800"></a>

<a href="https://i.imgur.com/4nSBUME.jpg"><img src="https://i.imgur.com/4nSBUME.jpg" width="800"></a>

<a href="https://i.imgur.com/CsmT0eQ.jpg"><img src="https://i.imgur.com/CsmT0eQ.jpg" width="800"></a>

<a href="https://i.imgur.com/kzg8itY.jpg"><img src="https://i.imgur.com/kzg8itY.jpg" width="800"></a>

