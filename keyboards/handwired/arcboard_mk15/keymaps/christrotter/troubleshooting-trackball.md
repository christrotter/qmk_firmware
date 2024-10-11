# trackball tracking is broken
It works, but jumps all over the place.

# Symptoms
- tracing a circle with the cursor eventually causes your cursor to drift across the screen
- trying to draw a straight line, left to right, draws a line that occasionally jumps up/down, and has 'jitter', and has less smooth edges, more jagged edges

## changing polling speed
tried down to 1ms, no change.

## changing spi divisor
- 16, 128, 256; these all really bad
- 32; sort of ok, still jerky
- 64; closest to ok, but still jumps

## fixing split transport
theory was that broken split transport (i.e. left half not connected) was causing thrash or something.
after fixing split transport, no change.

## solder joints
Maybe some of the solder joints to/from the pmw are bad?

## changing liftoff distance
this might still be the issue...
- set to 0x02 (default min) it's not great
- set to 0x07 (where i normally put it), it's worse
- set to 0x27 even worse
- set to 0x00 better...but that's as low as it goes

### adding a shim
I put in a .4mm shim (cardboard) and set liftoff back to 0x07.

Success?
Success.

# conclusion
So any kind of jerky movement is indicative of sensor-to-trackball distance problems, either too near or too far.
