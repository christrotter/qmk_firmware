# arcboard_mk20

matrix pins

dfu-util -a 0 --dfuse-address 0x08000000 -D /Users/christrotter/Downloads/stm32f405rg_arcboard_mk20/tinyuf2-stm32f405rg_arcboard_mk20.bin

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
