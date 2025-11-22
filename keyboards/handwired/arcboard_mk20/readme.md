# arcboard_mk20
*You should not build this.  Probably mk21 will be much better.*

Where to begin.


# Bringing the mainboard to life
Run this:
`dfu-util -a 0 --dfuse-address 0x08000000 -D /path/to/your/bootloader.bin`
After running dfu-util, you'll see the device in ioreg.
Now, run the tinyuf2 qmk flash:
`qmk flash -kb $KEYBOARD -km $KEYMAP -j $BUILD_CORES`
Now the device has qmk and behaves as such.



18 leds on encoder ring
12 on indicator bar // 8 now
52 on inner-intake // 10 now
44 on outer-intake // 36 (so 24 + 12 for logo)
// this has all changed...and did i write down the changes before buttoning it up?...nooooo
so we should have 30 on the keys plus 18 + 10 + 36 = 94


so turns out the rgb_matrix part of keyboard.json doesn't have error handling or checking or anything
left side now dialed in.
classic 'right side a tire fire only solved by getting counts correct' problems.
and the left side outer intake stopped working.
30 cyboard, 4 dpad, 3 paddle, 18 ring, 8 indicator, 10, or 12? shouldn't matter...ah but it does, cuz the count crossing over to 
37 + 18 + 8 = 63 + 46 = 109

