# Getting to a workable i2c config

## Hardware
Needs four pins:
1. 3v power
2. any gnd
3. SDA (data) pin (w. 4.7k resistor to 3v rail)
4. SCL (clock) pin (w. 4.7k resistor to 3v rail)

Other I2C devices come off the same pins, you only need one resistor per SDA/SCL pins.

* you are using I2C1 as labeled in the Waveshare pinout diagram: https://www.waveshare.com/w/upload/8/8e/RP2040-LCD-0.96-details-7.jpg
* e.g. GP14 for SDA, GP15 for SCL
* you are certain of the wiring!! (using the fpc breakout board caused issues)


## keyboard/rules.mk
```c
POINTING_DEVICE_ENABLE = yes
#POINTING_DEVICE_DRIVER = pimoroni_trackball
POINTING_DEVICE_DRIVER = cirque_pinnacle_i2c
```

## keyboard/mcuconf.h
```c
#undef RP_I2C_USE_I2C1
#define RP_I2C_USE_I2C1 TRUE
```
## keyboard/halconf.h
```c
#define HAL_USE_I2C TRUE
```

## keyboard/config.h
```c
// note that qmk only supports one i2c bus atm!!!
#define I2C_DRIVER I2CD2 // due to chibios/rp2040 naming issues, I2C1 == I2CD2
#define I2C1_SDA_PIN GP14
#define I2C1_SCL_PIN GP15

// Cirque config
#define CIRQUE_PINNACLE_DIAMETER_MM 40
#define CIRQUE_PINNACLE_TAP_ENABLE
#define POINTING_DEVICE_GESTURES_SCROLL_ENABLE

// Pimoroni config
#define PIMORONI_TRACKBALL_SCALE 1

// Generic config
#define POINTING_DEVICE_TASK_THROTTLE_MS 1
#define MOUSE_EXTENDED_REPORT
```
