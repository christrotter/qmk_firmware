# mapping the matrix

Ok important stuff
- top = row4 (remaining keywell rows are row3,2,1)
- thumbs = row0
- dpad = row5
- paddle = row4/col6, row5/col6, row6/col6
so kinda weird, nothing on row6 but paddle...kay.

kinda looks like it thinks it has 7 rows per half...
which would make sense for mk19. owait.
row0 = thumbs, row1-4 = keys, row5 = dpad, row6=last paddle
7 rows

so we need a 7 row matrix, 



left dpad is row5 (makes sense, rows0-4 are cyboard pcbs)
cols 6,7,8,9,A

left dpad (left, up, right, down, middle)
r/c 0123456789ABCDEF
05: 0000001000000000 (5/6) <--
05: 0000000100000000 (5/7)
05: 0000000001000000 (5/9)
05: 0000000010000000 (5/8)
05: 0000000000100000 (5/10)
left paddles (left, mid, right)
r/c 0123456789ABCDEF
04: 0000001000000000 (4/6)
05: 0000001000000000 (5/6) <-- duplicates dpad :(
06: 0000001000000000 (6/6)


right dpad (left, up, right, down, middle)
r/c 0123456789ABCDEF
0C: 0000001000000000
0C: 0000000100000000
0C: 0000000001000000
0C: 0000000010000000
0C: 0000000000100000



right paddles (left, mid, right)
r/c 0123456789ABCDEF
0B: 0000001000000000
0C: 0000001000000000
0D: 0000001000000000

uhhh here's the issue
0123456 7
8 9 A B C D E F
8 9 101112131415

right half, last paddle
row0D row13/col6
Chris Trotter:arcboard_mk20:1: r/c 0123456789ABCDEF
Chris Trotter:arcboard_mk20:1: 00: 0000000000000000
Chris Trotter:arcboard_mk20:1: 01: 0000000000000000
Chris Trotter:arcboard_mk20:1: 02: 0000000000000000
Chris Trotter:arcboard_mk20:1: 03: 0000000000000000
Chris Trotter:arcboard_mk20:1: 04: 0000000000000000
Chris Trotter:arcboard_mk20:1: 05: 0000000000000000
Chris Trotter:arcboard_mk20:1: 06: 0000000000000000
Chris Trotter:arcboard_mk20:1: 07: 0000000000000000
Chris Trotter:arcboard_mk20:1: 08: 0000000000000000
Chris Trotter:arcboard_mk20:1: 09: 0000000000000000
Chris Trotter:arcboard_mk20:1: 0A: 0000000000000000
Chris Trotter:arcboard_mk20:1: 0B: 0000000000000000
Chris Trotter:arcboard_mk20:1: 0C: 0000000000000000
Chris Trotter:arcboard_mk20:1: 0D: 0000001000000000

right half, top keywell 0/0
thinks it is row 11
Chris Trotter:arcboard_mk20:1: r/c 0123456789ABCDEF
Chris Trotter:arcboard_mk20:1: 00: 0000000000000000
Chris Trotter:arcboard_mk20:1: 01: 0000000000000000
Chris Trotter:arcboard_mk20:1: 02: 0000000000000000
Chris Trotter:arcboard_mk20:1: 03: 0000000000000000
Chris Trotter:arcboard_mk20:1: 04: 0000000000000000
Chris Trotter:arcboard_mk20:1: 05: 0000000000000000
Chris Trotter:arcboard_mk20:1: 06: 0000000000000000
Chris Trotter:arcboard_mk20:1: 07: 0000000000000000
Chris Trotter:arcboard_mk20:1: 08: 0000000000000000
Chris Trotter:arcboard_mk20:1: 09: 0000000000000000
Chris Trotter:arcboard_mk20:1: 0A: 0000000000000000
Chris Trotter:arcboard_mk20:1: 0B: 1000000000000000
Chris Trotter:arcboard_mk20:1: 0C: 0000000000000000
Chris Trotter:arcboard_mk20:1: 0D: 0000000000000000
keywell row1 1/0
thinks it is row 10
Chris Trotter:arcboard_mk20:1: r/c 0123456789ABCDEF
Chris Trotter:arcboard_mk20:1: 00: 0000000000000000
Chris Trotter:arcboard_mk20:1: 01: 0000000000000000
Chris Trotter:arcboard_mk20:1: 02: 0000000000000000
Chris Trotter:arcboard_mk20:1: 03: 0000000000000000
Chris Trotter:arcboard_mk20:1: 04: 0000000000000000
Chris Trotter:arcboard_mk20:1: 05: 0000000000000000
Chris Trotter:arcboard_mk20:1: 06: 0000000000000000
Chris Trotter:arcboard_mk20:1: 07: 0000000000000000
Chris Trotter:arcboard_mk20:1: 08: 0000000000000000
Chris Trotter:arcboard_mk20:1: 09: 0000000000000000
Chris Trotter:arcboard_mk20:1: 0A: 1000000000000000
Chris Trotter:arcboard_mk20:1: 0B: 0000000000000000
Chris Trotter:arcboard_mk20:1: 0C: 0000000000000000
Chris Trotter:arcboard_mk20:1: 0D: 0000000000000000

thumb key
Chris Trotter:arcboard_mk20:1: r/c 0123456789ABCDEF
Chris Trotter:arcboard_mk20:1: 00: 0000000000000000
Chris Trotter:arcboard_mk20:1: 01: 0000000000000000
Chris Trotter:arcboard_mk20:1: 02: 0000000000000000
Chris Trotter:arcboard_mk20:1: 03: 0000000000000000
Chris Trotter:arcboard_mk20:1: 04: 0000000000000000
Chris Trotter:arcboard_mk20:1: 05: 0000000000000000
Chris Trotter:arcboard_mk20:1: 06: 0000000000000000
Chris Trotter:arcboard_mk20:1: 07: 1000000000000000
Chris Trotter:arcboard_mk20:1: 08: 0000000000000000
Chris Trotter:arcboard_mk20:1: 09: 0000000000000000
Chris Trotter:arcboard_mk20:1: 0A: 0000000000000000
Chris Trotter:arcboard_mk20:1: 0B: 0000000000000000
Chris Trotter:arcboard_mk20:1: 0C: 0000000000000000
Chris Trotter:arcboard_mk20:1: 0D: 0000000000000000


looking at how it's interpreting our cols...
right half, going from 0,0 to 0,5 on the top keywell row
Chris Trotter:arcboard_mk20:1: r/c 0123456789ABCDEF
Chris Trotter:arcboard_mk20:1: 0B: 1000000000000000
Chris Trotter:arcboard_mk20:1: 0B: 0100000000000000
Chris Trotter:arcboard_mk20:1: 0B: 0010000000000000
Chris Trotter:arcboard_mk20:1: 0B: 0001000000000000
Chris Trotter:arcboard_mk20:1: 0B: 0000100000000000
Chris Trotter:arcboard_mk20:1: 0B: 0000010000000000

and left half, 0,0 position..
Chris Trotter:arcboard_mk20:1: r/c 0123456789ABCDEF
Chris Trotter:arcboard_mk20:1: 04: 1000000000000000

and what do the rows look like; press top keywell row, 0,0, and each subsequent keywell row
Chris Trotter:arcboard_mk20:1: r/c 0123456789ABCDEF
Chris Trotter:arcboard_mk20:1: 0B: 1000000000000000 (row11/col0)
Chris Trotter:arcboard_mk20:1: 0A: 1000000000000000 (row10/col0)
Chris Trotter:arcboard_mk20:1: 09: 1000000000000000 (row9/col0)
Chris Trotter:arcboard_mk20:1: 08: 1000000000000000 (row8/col0)
and thumbs
Chris Trotter:arcboard_mk20:1: 07: 1000000000000000 (row7/col0)


so the keys are all in cols 0-5
i.e. 
cyboard: col0-5,  row4-0(left), row11-7(right)
dpads:   col6-10, row5(left), row12(left)
paddles: col6, row4-6(left), row11-13(right) 

matrix needs to be
7 cols by 14 rows

but we can ignore bits we're not using, i think?
yes, "the layout macro only contains the keys that actually exist in the layout, empty matrix positions are ignored"


```json
    "layouts": {
        "LAYOUT": {
            "layout": [
                {"matrix": [4, 0], "x": 0, "y": 0},
                {"matrix": [4, 1], "x": 1, "y": 0},
                {"matrix": [4, 2], "x": 2, "y": 0},
                {"matrix": [4, 3], "x": 3, "y": 0},
                {"matrix": [4, 4], "x": 4, "y": 0},
                {"matrix": [4, 5], "x": 5, "y": 0},
                {"matrix": [4, 6], "x": 5, "y": 0},
                {"matrix": [11, 0], "x": 0, "y": 0},
                {"matrix": [11, 1], "x": 1, "y": 0},
                {"matrix": [11, 2], "x": 2, "y": 0},
                {"matrix": [11, 3], "x": 3, "y": 0},
                {"matrix": [11, 4], "x": 4, "y": 0},
                {"matrix": [11, 5], "x": 5, "y": 0},
                {"matrix": [11, 6], "x": 5, "y": 0},
                {"matrix": [3, 0], "x": 0, "y": 0},
                {"matrix": [3, 1], "x": 1, "y": 0},
                {"matrix": [3, 2], "x": 2, "y": 0},
                {"matrix": [3, 3], "x": 3, "y": 0},
                {"matrix": [3, 4], "x": 4, "y": 0},
                {"matrix": [3, 5], "x": 5, "y": 0},
                {"matrix": [10, 0], "x": 0, "y": 0},
                {"matrix": [10, 1], "x": 1, "y": 0},
                {"matrix": [10, 2], "x": 2, "y": 0},
                {"matrix": [10, 3], "x": 3, "y": 0},
                {"matrix": [10, 4], "x": 4, "y": 0},
                {"matrix": [10, 5], "x": 5, "y": 0},
                {"matrix": [2, 0], "x": 0, "y": 0},
                {"matrix": [2, 1], "x": 1, "y": 0},
                {"matrix": [2, 2], "x": 2, "y": 0},
                {"matrix": [2, 3], "x": 3, "y": 0},
                {"matrix": [2, 4], "x": 4, "y": 0},
                {"matrix": [2, 5], "x": 5, "y": 0},
                {"matrix": [9, 0], "x": 0, "y": 0},
                {"matrix": [9, 1], "x": 1, "y": 0},
                {"matrix": [9, 2], "x": 2, "y": 0},
                {"matrix": [9, 3], "x": 3, "y": 0},
                {"matrix": [9, 4], "x": 4, "y": 0},
                {"matrix": [9, 5], "x": 5, "y": 0},
                {"matrix": [1, 0], "x": 0, "y": 0},
                {"matrix": [1, 1], "x": 1, "y": 0},
                {"matrix": [1, 2], "x": 2, "y": 0},
                {"matrix": [1, 3], "x": 3, "y": 0},
                {"matrix": [1, 4], "x": 4, "y": 0},
                {"matrix": [1, 5], "x": 5, "y": 0},
                {"matrix": [8, 0], "x": 0, "y": 0},
                {"matrix": [8, 1], "x": 1, "y": 0},
                {"matrix": [8, 2], "x": 2, "y": 0},
                {"matrix": [8, 3], "x": 3, "y": 0},
                {"matrix": [8, 4], "x": 4, "y": 0},
                {"matrix": [8, 5], "x": 5, "y": 0},
                {"matrix": [0, 0], "x": 0, "y": 0},
                {"matrix": [0, 1], "x": 1, "y": 0},
                {"matrix": [0, 2], "x": 2, "y": 0},
                {"matrix": [0, 3], "x": 3, "y": 0},
                {"matrix": [0, 4], "x": 4, "y": 0},
                {"matrix": [0, 5], "x": 5, "y": 0},
                {"matrix": [7, 0], "x": 0, "y": 0},
                {"matrix": [7, 1], "x": 1, "y": 0},
                {"matrix": [7, 2], "x": 2, "y": 0},
                {"matrix": [7, 3], "x": 3, "y": 0},
                {"matrix": [7, 4], "x": 4, "y": 0},
                {"matrix": [7, 5], "x": 5, "y": 0},
                {"matrix": [5, 6], "x": 0, "y": 0},
                {"matrix": [5, 7], "x": 1, "y": 0},
                {"matrix": [5, 8], "x": 2, "y": 0},
                {"matrix": [5, 9], "x": 3, "y": 0},
                {"matrix": [5, 10], "x": 4, "y": 0},
                {"matrix": [11, 6], "x": 0, "y": 0},
                {"matrix": [11, 7], "x": 1, "y": 0},
                {"matrix": [11, 8], "x": 2, "y": 0},
                {"matrix": [11, 9], "x": 3, "y": 0},
                {"matrix": [11, 10], "x": 4, "y": 0},
                {"matrix": [6, 6], "x": 5, "y": 0},
                {"matrix": [13, 6], "x": 5, "y": 0}
```


/*
    [_QWERTY] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______,      _______,_______,_______,_______, _______, _______, _______, //row4 keywell-top + paddle
        _______, _______, _______, _______, _______, _______,               _______,_______,_______,_______, _______, _______,          //row3 keywell-top
        _______, _______, _______, _______, _______, _______,               _______,_______,_______,_______, _______, _______,          //row2 keywell-top
        _______, _______, _______, _______, _______, _______,               _______,_______,_______,_______, _______, _______,          //row1 keywell-top
        _______, _______, _______, _______, _______, _______,               _______,_______,_______,_______, _______, _______,          //row0 thumbs
        _______, _______, _______, _______, _______,          _______,      _______,_______,_______,_______, _______,          _______, //row5, dpad + paddle
                                                              _______,                                                         _______  //row6, paddle
    ),

*/

ahhh ok.
so i'm missing some col pins in the def.
huh, i only have 12 col pins configured in the matrix.
so '13' is incorrect.
wat did i do




r/c 0123456789ABCDEF
0B: 0000001000000000
0C: 0000001000000000
0D: 0000001000000000

kay so how is it possible that they are rows BCD 11-13
we have 7 row pins; so 13 makes sense.
ok, it's the col that must be wrong.
OHHHH
i've forgotten that the middle paddle and dpad item are duplicated.
so the matrix is not 7x7, it's (7x7)-1


thumb keys are out of order...
1-0=0
2-1=1
3-2=5
4-3=3
5-4=2
6-5=6

So this needs to transform....
```json
                {"matrix": [0, 0], "x": 0, "y": 0},
                {"matrix": [0, 1], "x": 1, "y": 0},
                {"matrix": [0, 2], "x": 2, "y": 0},
                {"matrix": [0, 3], "x": 3, "y": 0},
                {"matrix": [0, 4], "x": 4, "y": 0},
                {"matrix": [0, 5], "x": 5, "y": 0},


                {"matrix": [0, 0], "x": 0, "y": 0},
                {"matrix": [0, 1], "x": 1, "y": 0},
                {"matrix": [0, 4], "x": 2, "y": 0},
                {"matrix": [0, 3], "x": 3, "y": 0},
                {"matrix": [0, 2], "x": 4, "y": 0},
                {"matrix": [0, 5], "x": 5, "y": 0},
```