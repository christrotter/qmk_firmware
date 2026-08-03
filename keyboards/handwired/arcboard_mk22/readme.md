# handwired/arcboard_mk22

Note: using F405 instead of F407 b/c clock defaults.  Have to fix this...




# mapping out the layout
this is always trouble, so let's try to capture the method

starting w. left half ohhhh wups - this is the right half w. left switch b/c broken layout. 
well should provide a pattern anyways.

physical row/col to qmk console output
R,C => r/c 01234567
col1
0,0 => 04: 00000100 => physical position of 0,0 is actually row4, col5
1,0 => 03: 00000100 => physical position of 1,0 is actually row3, col5
2,0 => 02: 00000100 => physical position of 2,0 is actually row2, col5
3,0 => 01: 00000100 => physical position of 3,0 is actually row1, col5

col2
0,1 => 04: 00001000 => physical position of 0,1 is actually row4, col4
1,1 => 03: 00001000 => physical position of 1,1 is actually row3, col4
2,1 => 02: 00001000 => physical position of 2,1 is actually row2, col4
3,1 => 01: 00001000 => physical position of 3,1 is actually row1, col4

col3
0,2 => 04: 00010000 => physical position of 0,2 is actually row4, col3
1,2 => 03: 00010000 => physical position of 1,2 is actually row3, col3
2,2 => 02: 00010000 => physical position of 2,2 is actually row2, col3
3,2 => 01: 00010000 => physical position of 3,2 is actually row1, col3

col4
0,3 => 04: 00100000 => physical position of 0,3 is actually row4, col2
1,3 => 03: 00100000 => physical position of 1,3 is actually row3, col2
2,3 => 02: 00100000 => physical position of 2,3 is actually row2, col2
3,3 => 01: 00100000 => physical position of 3,3 is actually row1, col2

col5
0,4 => 04: 01000000 => physical position of 0,4 is actually row4, col1
1,4 => 03: 01000000 => physical position of 1,4 is actually row3, col1
2,4 => 02: 01000000 => physical position of 2,4 is actually row2, col1
3,4 => 01: 01000000 => physical position of 3,4 is actually row1, col1

col6
0,5 => 04: 10000000 => physical position of 0,5 is actually row4, col0
1,5 => 03: 10000000 => physical position of 1,5 is actually row3, col0
2,5 => 02: 10000000 => physical position of 2,5 is actually row2, col0
3,5 => 01: 10000000 => physical position of 3,5 is actually row1, col0

thumbs
physical layout, 1->5
R,C    r/c 01234567
0,1 => 00: 10000000
0,2 => 00: 01000000
0,3 => 00: 00100000
0,4 => 00: 00010000
0,5 => 00: 00001000

So the only weirdness is that row4 in code is row1 physically.
Row0 is thumbs.

Ahhhh also confusing things is that i have 6 keywell rows on the mcu, but only use 4.

this is what we want...
00 thumbs
04 top row
03 
02 
01 bot row
07 paddle row1
08 paddle row2
09 paddle row3
0A dpad row (10)

0B thumbs (11)
13 0F top row (15)
12 0E (14)
11 0D (13)
0C bot row (12)
12 p1 (18)
13 p2 (19)
14 p3 (20)
15 dpad (21)

combining them to satisfy split matrix; putting into decimal
04 top row
15 top row
03 top-mid row
14 top-mid row
02 bot-mid row
13 bot-mid row
01 bot row
12 bot row
00 thumbs
11 thumbs
07 p1
18 p1
08 p2
19 p2
09 p3
20 p3
10 dpad row
21 dpad row

ok, working.
now, what specific row/col are the paddles...
remember these are hex
right r/c 01234567
L 12(18): 00010000 col03
M 13(19): 00010000 
R 14(20): 00010000
left
L 07: 00010000 col03
M 08: 00010000
R 09: 00010000

Ok, ordering is wonk.
pressing L M R
right: mlr
left: lrm

i suspect that the pcb orientation will play a role here...ugh. right.
electrically:
- paddle pcb is row1,2,3, actually 7,8,9 on ffc/mcu
- so it should just flip things
- why we getting weird ordering
                {"matrix": [7, 3], "x": 0, "y": 10},
                {"matrix": [18, 3], "x": 0, "y": 10},

                {"matrix": [8, 3], "x": 0, "y": 10},
                {"matrix": [19, 3], "x": 0, "y": 10},

                {"matrix": [9, 3], "x": 0, "y": 10},
                {"matrix": [20, 3], "x": 0, "y": 10},
- ohhhhhhhhhhhh b/c
        KC_L, KC_M, KC_R,                               KC_L, KC_M, KC_R,

and dpad; follow the clock from 12; should get same pattern
method:
- press each 'button' on the dpad in the ordering i want to see in ocde
- observe output in qmk console w. matrix debug enabled
- capture output
- re-order keyboard.json accordingly

left
U: 0A: 01000000
R: 0A: 00010000
D: 0A: 00100000
L: 0A: 10000000
P: 0A: 00001000
right
U: 15: 01000000
R: 15: 00010000
D: 15: 00100000
L: 15: 10000000
P: 15: 00001000

dpad ordering is:
1
3
2
0
4