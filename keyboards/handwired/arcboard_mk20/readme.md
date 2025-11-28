# ArcBoard-mk20
*You **should not** build this.  Probably mk21 will be much better.*

The next iteration of the ArcBoard is here...mk20 comes with a lot of improvements pretty much across the board.

<a href="https://i.imgur.com/qV5I5p4.png"><img src="https://i.imgur.com/qV5I5p4.png" width="1200"></a>

## But y, tho
Very important to note that this design isn't for everyone.  I have fibromyalgia which requires my hands to be in a resting position - can't use a mouse, can't rest on any edges, all sorts of restrictions.  Failure to abide by 'resting position' leads to a bad time, and without this keyboard layout (trackball location, specifically), I would not be able to do my day job (software stuff).

## tl;dr
New keyboard, who dis.  Trying out a smaller form factor, a large ring encoder, and paddle switches (curl your finger inwards a bit).
So far, very promising results.  So far, lots of prototype-lyfe problems.  So far, so good.  In fact, I'm hopeful that mk21 will be a polished version of this.

## Community effort
It continues to be a theme - the keyboard community has been foundational.
Thanks to `burkfers`, `Wimads` (cactus), `Drashna`, `GeorgeN`, `Yingeling`, `Dasky`, so many more.

## Hardware features
- 4x6 main keywell + 5 thumb keys (_6 on left half_)
- 34mm trackball w. NSK roller bearings
- 5-way directional pad (dpad) near thumb
- 3x "paddle" keys between keywell and thumbcluster
- EC10 encoders
  - 2x near LCD screen, w. 25mm silicone ring for grip
  - 1x large gear-driven ring around thumbcluster, w. translucent TPU grip
- USB-C connectivity for main and split
- [2.25" LCD screen](https://www.aliexpress.com/item/1005009184422205.html)
- a _lot_ of LEDs
  - ring encoder illumination
  - indicator bar (_e.g. shift-lock on_)
  - "intake" lighting incl. logo illumination
- custom PCBs
  - [STM32 mainboard](https://github.com/christrotter/arcboard-stm32)
  - [custom FFC for columns/thumbs](https://github.com/christrotter/mk19-flex-pcb)
  - [EC10 to FFC](https://github.com/christrotter/mouse-encoder-pcb)
  - [SKRHACE010 to FFC (_dpad, w. 4x LEDs_)](https://github.com/christrotter/led-pad)
  - [SKRHACE010 to FFC (_paddles, w. 1x LED_)](https://github.com/christrotter/paddle-dpad-pcb)
  - LCD pins to FFC (*aliexpress*)
  - [PMW3360 to FFC](https://github.com/christrotter/charybdis-pmw-3360-sensor-pcb/tree/arcboarding) (*forked from* [Charybdis](https://github.com/Bastardkb/charybdis-pmw-3360-sensor-pcb))
- designed for ([the Cyboard column PCB kit](https://cyboard.digital/products/dactyl-flex-pcbs))
- boot/reset buttons in palm rest
- 6mm Grifiti palm rest pad (_template cut to fit_)
- printed w. PLA in mind; clamshell assembly

## Firmware features
- application sensing companion app for automatic layer switching (_works, but early days_)
  - also integrates the keyboard with the mk3 pedals
  - also integrates the keyboard/pedals with the monitor LED surround
- basic UI (_under dev, rather poor_)
- improved ledmap code, much toil reduction
- the usual QMK goodness (_layer hold!_)
- aesthetic lighting changes w. layers

## Design features
Some new methods that made life much better.
- **single-piece keywell**
  - Took several weeks (*ok a lot of weeks*) to get right.  Actually holds the Cyboard PCBs in place, tool-less install!
  - keywell-capper part allows customizing what components you want mounted (*ok so it's not entirely single-piece...*)
  - integrated pcb mounts, paddle-assembly mount, thumbcluster mounts
- **multi-piece thumbcluster** - a layered approach made updating for the left-half relatively painless (*thumbcluster is always the hard part*)
- **clamshell** - Bottom shell, then components assembly, then top shell.  Many packaging/fabrication lessons learned here, wow.
- **remote-mount USB-C ports** (*vs. being soldered directly to the mainboard*)
- **multi-colour printing** - I tried doing inlays & CA glue for the bottom shell graphics and it was a sad time.  burkfers encouraged/shamed me into trying multi-filament and wow, what a game-changer.  (*I don't have an automatic change system, either, and still amazing.*)

# Links
- Build journal
  - https://docs.google.com/document/d/1H42WKKSJjMTwKAtwSacicEkNXHAzItHnSK0OiVTYifs/edit?usp=sharing
- Print list
  - https://docs.google.com/document/d/19vgn_IOVY2ncgV_MKY-XW2Omr_Vd-NVtJHTEubr_N-U/edit?tab=t.0#heading=h.80pmugz15mks
- Lessons learned
  - https://docs.google.com/document/d/1k8chGCqfj4JBooXbeX9SU0YzzGC2gb9ey4XtdSIj2rA/edit?usp=sharing
- Reddit posts
  - https://www.reddit.com/r/ErgoMechKeyboards/comments/1cfgai1/arcboard_mk19_the_learning_continues/
  - https://www.reddit.com/r/ErgoMechKeyboards/comments/1goqo3v/the_next_step_arcpedals_mk3/
  - https://www.reddit.com/r/ErgoMechKeyboards/comments/1kphv10/arcboard_mk20_dev_demo_appsense_for_qmk_or_mild/
- QMK
  - https://github.com/christrotter/qmk_firmware/tree/arcboard-series/keyboards/handwired/arcboard_mk19
  - https://github.com/christrotter/qmk_firmware/tree/arcboard-series/keyboards/handwired/arcpedals_mk3
- PCBs
  - dpad: https://github.com/christrotter/led-pad
  - paddle: https://github.com/christrotter/paddle-dpad-pcb
  - stm32 mainboard: https://github.com/christrotter/arcboard-stm32
  - ec10 encoder to ffc: https://github.com/christrotter/mouse-encoder-pcb
  - my fork of the Charybdis PMW pcb: https://github.com/christrotter/charybdis-pmw-3360-sensor-pcb/tree/arcboarding
  - Cyboard connector: https://github.com/christrotter/mk19-flex-pcb
# Prototype videos
- Paddle switch prototype: https://youtu.be/c5nMtVwbkb0?si=nyleiMdXyoZ9cqYi
- Ring encoder prototypes:
  - https://youtu.be/lQFwvmERC6w?si=Wq_1y33K7FKhAAh9
  - https://youtu.be/TqfIjvzGV10?si=Oi7gQAPyGjwN09Q8
  - https://youtu.be/iZfNFKMe5Hg?si=l5-QiT3U4LrNl27g
  - https://youtu.be/t9WXgvk5tNE?si=ZtXXiSQfZwNoUTdk
  - https://youtu.be/0Gul08TXhzs?si=-Fqa02d69KASMguV
- AppSense demo: https://youtu.be/pHvF_KDkxHM?si=VKkWK1cEtEMsvbvx
- Monitor surround: https://youtu.be/IdejM_AcEIY?si=hktS4YOHlLD4JPLp

# More pictures, please
[Imgur gallery here](https://imgur.com/a/g7PXRzy).  Much more detail into the development process. 

<a href="https://i.imgur.com/a0HeC0H.png"><img src="https://i.imgur.com/a0HeC0H.png" width="800"></a>
<a href="https://i.imgur.com/xmHka58.png"><img src="https://i.imgur.com/xmHka58.png" width="800"></a>

<a href="https://i.imgur.com/CdsrMOP.png"><img src="https://i.imgur.com/CdsrMOP.png" width="800"></a>
<a href="https://i.imgur.com/HogVive.png"><img src="https://i.imgur.com/HogVive.png" width="800"></a>

<a href="https://i.imgur.com/ka6fmzS.png"><img src="https://i.imgur.com/ka6fmzS.png" width="800"></a>
<a href="https://i.imgur.com/MhT0z1k.png"><img src="https://i.imgur.com/MhT0z1k.png" width="800"></a>

<a href="https://i.imgur.com/OBkJhMV.png"><img src="https://i.imgur.com/OBkJhMV.png" width="800"></a>
<a href="https://i.imgur.com/6gFmnHj.png"><img src="https://i.imgur.com/6gFmnHj.png" width="800"></a>


# Bringing the mainboard to life
For 
Run this:
`dfu-util -a 0 --dfuse-address 0x08000000 -D /path/to/your/bootloader.bin`
After running dfu-util, you'll see the device in ioreg.
Now, run the tinyuf2 qmk flash:
`qmk flash -kb $KEYBOARD -km $KEYMAP -j $BUILD_CORES`
Now the device has qmk and behaves as such.

# ToDo
## Managing the rgb matrix, ledmaps, indicators
## Troubleshooting custom PMW installs
## 