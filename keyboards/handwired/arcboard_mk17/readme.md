# handwired/arcboard_mk17

![handwired/arcboard_mk17](https://i.imgur.com/0dzEVQO.jpg)

"The last one" in a line of "the last one"s.  

**Features**
* Split keyboard, connectivity via TRRS
* Dual 34mm thumb trackballs (_unfortunately some software issue preventing one from being used_)
* Dual 5-way dpads
* Quad encoders w. LED backlighting
* Diffused LED indicator panel
* 4x6 keywells with 5-key thumb clusters; 6x6 effective key matrix to program
* Designed for Moonlander keycaps (_DSA?_) and Moonlander piano keys
* TFT screens on both halves for doing fun things with quantum painter (_currently suffering code woes_)
* Dovetail-attached large sloped palm rests (_designed for Grifiti 4"-wide palm rests; dovetail for easy replacement with whatever works best_)
* Modular design with M3 hot-melt inserts and M3x8 countersunk machine screws (_just print a new thumb cluster, for example - or, print a new trackball holder...or keywell...or..._)
* LEDmap per-key code (_which I have since been informed is not a great method, and is indeed blowing up my TFTs...so don't copy this._)

## More views
<table>
<tr>
<td>
<a href="https://i.imgur.com/wIT4whE.jpg"><img src="https://i.imgur.com/wIT4whE.jpg" title="Close up right half" width=400/></a>
</td>
<td>
<a href="https://i.imgur.com/UoVaWhp.jpg"><img src="https://i.imgur.com/UoVaWhp.jpg" title="Trackball feat. dino damage" width=400"/></a>
</td>
</tr>
<tr>
<td>
<a href="https://i.imgur.com/p6ENQgu.jpg"><img src="https://i.imgur.com/p6ENQgu.jpg" title="Wiring jungle" width=400 /></a>
</td>
<td>
<a href="https://i.imgur.com/YtL4W1R.jpg"><img src="https://i.imgur.com/YtL4W1R.jpg" title="Yay" width=400 /></a>
</td>
</tr>
<tr>
<td>
<a href="https://i.imgur.com/xGZekwB.jpg"><img src="https://i.imgur.com/xGZekwB.jpg" title="Fusion360 forms at work" width=400 /></a>
</td>
<td>
<a href="https://i.imgur.com/BKyNX6P.jpg"><img src="https://i.imgur.com/BKyNX6P.jpg" title="Cable pluggies" width=400 /></a>
</td>
</tr>
<tr>
<td>
<a href="https://i.imgur.com/MTUOLPI.jpg"><img src="https://i.imgur.com/MTUOLPI.jpg" title="Indicators in action" width=400 /></a>
</td>
<td>
<a href="https://i.imgur.com/PlIPHms.jpg"><img src="https://i.imgur.com/PlIPHms.jpg" title="Palm rest tray" width=400 /></a>
</td>
</tr>
<tr>
<td>
<a href="https://i.imgur.com/QoRdXTg.jpg"><img src="https://i.imgur.com/QoRdXTg.jpg" title="Design to life" width=400 /></a>
</td>
</tr>
</table>

**More pictures:** https://imgur.com/a/pIDDqV1

## Hardware
* Keyboard Maintainer: [Chris Trotter](https://github.com/christrotter)
* Hardware Supported: RP2040 w. mxledbit 'container' PCBs, ST7789 TFTs, 3D-printed chassis
* Hardware Availability: 
  * Waveshare RP2040-Plus: https://www.aliexpress.com/item/1005003504708746.html
  * per-key PCB: https://github.com/swanmatch/MxLEDBitPCB/tree/master/container (via JLCPCB)
  * wiring PCB: https://www.aliexpress.com/item/4000301371545.html
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
* OR **Bootmagic reset**: Mouse layer on, one key for EEPROM reset (L1,2 or R1,5), one key for resetting into bootloader (L1,1 or R1,6) 
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

For the quantum painter stuff, it's all in the `arcboard_mk17_qp.c` file, and currently kinda broken due to SPI/transport issues - probably more due to my build execution, not QMK.

## Troubleshooting
### serial baudrate
```
Experiment: See what the scan rate change is for each setting:
e.g. keyboard/config.h; #define SERIAL_USART_SPEED 800000
230400 = 640 (default)
460800 = 780 (labeled as 'experimental')
700000 = 840
800000 = 860 (35% improvement! very consistent numbers)
850000 = 'Failed to execute encoder/pointer' errors
900000 = 875, but inconsistent numbers, ranging from 855-875
921600 = 'Failed to execute encoder' errors
```
