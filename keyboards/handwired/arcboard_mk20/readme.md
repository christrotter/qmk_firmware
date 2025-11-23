# ArcBoard-mk20
*You **should not** build this.  Probably mk21 will be much better.*

The next iteration of the ArcBoard is here...mk20 comes with a lot of improvements pretty much across the board.

<img src="images/mk20-profile.png"  width="1200">

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
- 2.25" LCD screen
- a _lot_ of LEDs
  - ring encoder illumination
  - indicator bar (_e.g. shift-lock on_)
  - "intake" lighting incl. logo illumination
- custom PCBs
  - STM32 mainboard
  - custom FFC for columns/thumbs
  - EC10 to FFC
  - SKRHACE010 to FFC (_dpad, w. 4x LEDs_)
  - SKRHACE010 to FFC (_paddles, w. 1x LED_)
  - LCD pins to FFC
  - PMW3360 to FFC
- designed for the Cyboard column PCB kit
- boot/reset buttons in palm rest
- 6mm Grifiti palm rest pad (_template cut to fit_)
- printed w. PLA in mind; clamshell assembly

## Firmware features
- application sensing companion app for automatic layer switching (_works, but early days_)
- basic UI (_under dev, rather poor_)
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

# More pictures, please
[Imgur gallery here](https://imgur.com/a/g7PXRzy).  Much more detail into the development process. 


<img src="images/header.png"  width="800">
<img src="images/paddles.png"  width="800">

<img src="images/trackball.png"  width="800">
<img src="images/right-half.png"  width="800">

<img src="images/left-half.png"  width="800">
<img src="images/ring-encoder.png"  width="800">

<img src="images/bottom.png"  width="800">
<img src="images/palm-buttons.png"  width="800">


# Build overview
Where to begin.  1000 hours over 6.5 months, 650+ page build journal & 8500+ post build thread, dozens of CAD components, many kilograms of prototype plastic printed, many constraints navigated...




# Bringing the mainboard to life
For 
Run this:
`dfu-util -a 0 --dfuse-address 0x08000000 -D /path/to/your/bootloader.bin`
After running dfu-util, you'll see the device in ioreg.
Now, run the tinyuf2 qmk flash:
`qmk flash -kb $KEYBOARD -km $KEYMAP -j $BUILD_CORES`
Now the device has qmk and behaves as such.

# 

# Managing the rgb matrix

