# handwired/arcboard_mk13

![handwired/arcboard_mk13](https://i.imgur.com/HgmPPui.jpg)

The next iteration of my take on the Tractyl.

**Featuring...**
* Right-hand 34mm thumb trackball with right/left-hand togglable drag-scroll
* 5x7 keywells with 6-key thumb clusters (_feat. two-per-side extra-useless spots for arrow keys or backlit inserts_)
* Designed for Moonlander keycaps (_DSA?_) and Moonlander piano keys
* TFT screens on both halves for doing fun things with quantum painter (_super useful for debugging..._)
* Split connectivity via TRRS
* Weird artsy design that's actually kinda bad functionally
* Dovetail-attached large sloped palm rests (_designed for Grifiti 4"-wide palm rests; dovetail for easy replacement with whatever works best_)
* Modular design with M3 hot-melt inserts and M3x8 countersunk allen bolts (_just print a new thumb cluster, for example - or, print a new trackball holder...or keywell...or..._)
* LEDmap per-key code c/o Mikael Manukyan <arm.localhost@gmail.com>
* RP2040 holders, plus a case for the holder that allows 'blind' resets - a ballbearing is melted into the reset flex arm of the case, you can easily tell by touch which flex arm is which

## More views
<table>
<tr>
<td>
<a href="https://i.imgur.com/LpN2FXA.jpg"><img src="https://i.imgur.com/LpN2FXA.jpg" title="Right half" width=400/></a>
</td>
<td>
<a href="https://i.imgur.com/LyZdaVg.jpg"><img src="https://i.imgur.com/LyZdaVg.jpg" title="Left half" width=400"/></a>
</td>
</tr>
<tr>
<td>
<a href="https://i.imgur.com/dyRULB3.jpg"><img src="https://i.imgur.com/dyRULB3.jpg" title="Tactile reset" width=400 /></a>
</td>
<td>
<a href="https://i.imgur.com/ccpSt0w.jpg"><img src="https://i.imgur.com/ccpSt0w.jpg" title="MCU holder" width=400 /></a>
</td>
</tr>
<tr>
<td>
<a href="https://i.imgur.com/0mQXqwx.jpg"><img src="https://i.imgur.com/0mQXqwx.jpg" title="TFT displays" width=400 /></a>
</td>
<td>
<a href="https://i.imgur.com/LKRukfG.jpg"><img src="https://i.imgur.com/LKRukfG.jpg" title="Side profiles" width=400 /></a>
</td>
</tr>
<tr>
<td>
<a href="https://i.imgur.com/yIK02Zp.jpg"><img src="https://i.imgur.com/yIK02Zp.jpg" title="Design to life" width=400 /></a>
</td>
</tr>
</table>

## Hardware
* Keyboard Maintainer: [Chris Trotter](https://github.com/christrotter)
* Hardware Supported: RP2040 w. mxledbit 'container' PCBs, ST7789 TFTs, 3D-printed chassis
* Hardware Availability: 
  * Waveshare RP2040-Plus: https://www.aliexpress.com/item/1005003504708746.html
  * PCB: https://github.com/swanmatch/MxLEDBitPCB/tree/master/container (via JLCPCB)
  * 2.4" TFT: https://www.aliexpress.com/item/4000219159401.html
  * Chassis: https://github.com/christrotter/3d-models/tree/main/keyboards
  * Hotswap sockets: https://www.aliexpress.com/item/4001051840976.html
  * Capacitors: https://www.aliexpress.com/item/32877282377.html
  * LEDs: https://www.aliexpress.com/item/4000475685852.html

## Build enviro
See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

### Build scripts
I have included some build scripts...
* build.sh - just do a build, lint, or build/flash the right/left halves (code uses EE_HANDS handedness)
  * ./build.sh build
  * ./build.sh right
  * ./build.sh left 
  * ./build.sh lint
* gen_font.sh - helper for dealing with quantum painter fonts

## Bootloader
Enter the bootloader one of two ways:
* **Bootmagic reset**: Hold down the top-left key (left half) or top-right key (right half) and plug in the keyboard.  EEPROM will be reset (e.g. rgb matrix base colour); reset/unplug-replug again to have the whole boot/init cycle run.
* **Physical buttons**: With USB plugged in, double-press the MCU reset button (the part with the bump) to enter bootloader mode.  Or, press the boot button and plug in USB.

## Config
Keymap-level config items...
* CPI of trackball/dragscroll
* backlight power-off timeout
* RGB matrix 'base colour' and brightness - the per-key LED strategy assumes you have a base colour that is augmented by individual keys of note
* Tapping term, oneshot timeout, etc
* RGB 'ledmaps'

```c
const ledmap PROGMEM ledmaps[] = {
    [_QWERTY] = RGB_MATRIX_LAYOUT_LEDMAP(
        RED, ___n___, ___n___, ___n___, ___n___, ___n___, TOG_NAV,              MAGIPLY, ___n___, ___n___, ___n___, ___n___, ___n___,    GOLD,
       CYAN, ___n___, ___n___, ___n___, ___n___, ___n___, TOG_MSE,               ORANGE, ___n___, ___n___, ___n___, ___n___, ___n___,    CYAN,
       GOLD, ___n___, ___n___, ___n___, ___n___, ___n___, TOG_SYM,              ___n___, ___n___, ___n___, ___n___, ___n___, ___n___,    CYAN,
    ___n___, HRM_CTL, HRM_ALT, HRM_GUI, HRM_SFT, ___n___,    PGUP,                 HOME, ___n___, HRM_SFT, HRM_GUI, HRM_ALT, HRM_CTL, ___n___,
       DRAG, ___n___, ___n___, ___n___, ___n___, ___n___,    PGDN,                  END, ___n___, ___n___, ___n___, ___n___, ___n___,    DRAG,
                      ___n___, ___n___,                                                                    ___n___, ___n___,
      SHIFT,  PURPLE,     ESC,     DEL, TOG_NAV,  BCKSPC,                                  SHIFT,   SHIFT, TOG_SYM, TOG_SYM,   ENTER,   SPACE
```

For the quantum painter stuff, it's all in the `arcboard_mk13_ui.c` file, and currently kinda broken due to SPI/transport issues - probably more due to my build execution, not QMK.
