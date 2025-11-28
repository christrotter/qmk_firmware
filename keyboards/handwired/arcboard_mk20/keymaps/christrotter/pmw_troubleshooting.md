# So you used a PMW3360 in your custom board
...and you're having grief.

Top issues:
- no tracking
- constantly sporadic tracking
- consistent but spaced out sporadic tracking

Your first stop is the datasheet.
- 2.4mm from lens is your goal, +/- 0.2mm
  - please consider how small 0.2mm is, even 0.4mm
- optical center is a thing

# In practice
- optical center can be off by a 1-2mm and your tracking still be fine
- distance from lens can be off by +/-0.65mm and still track fine
  - this is still a pretty small distance!
  - I have a chart in the build journal that illustrates this...i should make this an image...
- use guide/construction sketches to keep yourself on track; e.g. a sketch in your PMW assembly that has a line from optical center up to the middle of your trackball with a point at that distance, so you can lock objects to it with joints

# Testing issues
If you find that tracking is perfect but lags every 500ms or so, this can be due to the serial connection check code.
This code has a timeout that blocks all other code from running.  Once you plug in the other half, the issue goes away.