#!/bin/bash
KB_PATH=handwired/arcboard_mk19_fx
HOME_DIR=/Users/christrotter/git/qmk/qmk_firmware
KB_DIR=$HOME_DIR/keyboards/$KB_PATH
USER_DIR=$HOME_DIR/users/christrotter

BUILD_CORES=12
KEYMAP='christrotter'
KEYBOARD='handwired/arcboard_mk19_fx'

if [ -z "$1" ];then
    echo "ERROR: Specify build, left, or right!"
    exit 1
else
    echo "INFO: Building or flashing: $1"
fi

cd $HOME_DIR

if [ "$1" == "build" ];then
    echo "INFO: Linting code..."
    qmk lint -kb $KEYBOARD
    echo "INFO: Just doing a build..."
    qmk compile -kb $KEYBOARD -km $KEYMAP -j $BUILD_CORES
elif [ "$1" == "left" ];then
    # the dfu-split-right/left is an ee_hands thing
    echo "double-press reset please!"
    # sleep 5
    echo "check for a bootable RP2040..."
    RP2040_CHECK=`ioreg -p IOUSB | grep -o "RP2\ Boot" | grep -o "RP2"`
    echo "RP2040_CHECK says: $RP2040_CHECK"
    if [ "$RP2040_CHECK" == "RP2" ];then
        echo "Found an RP2 device in boot state..."
        # watch "ioreg -p IOUSB | grep -o \"RP2\ Boot\"" # you can use this to check if the microcontroller is seen by your OS.
        echo "Copying the UF2 file onto the rpi boot volume..."
        qmk flash -bl uf2-split-left -kb $KEYBOARD -km $KEYMAP -j $BUILD_CORES
        echo "Now do an eeprom reset...unplug USB, hold down the far left key (e.g. ESC)...and plug in USB."
    else
        echo "ERROR: Did not find an RP2 device in boot state!"
    fi
elif [ "$1" == "right" ];then
        echo "double-press reset please!"
    # sleep 5
    echo "check for a bootable RP2040..."
    RP2040_CHECK=`ioreg -p IOUSB | grep -o "RP2\ Boot" | grep -o "RP2"`
    echo "RP2040_CHECK says: $RP2040_CHECK"
    if [ "$RP2040_CHECK" == "RP2" ];then
        echo "Found an RP2 device in boot state..."
        echo "Copying the UF2 file onto the rpi boot volume..."
        qmk flash -kb $KEYBOARD -km $KEYMAP -j $BUILD_CORES
        echo "Now do an eeprom reset...unplug USB, hold down the far right key (e.g. F12)...and plug in USB."
    else
        echo "ERROR: Did not find an RP2 device in boot state!"
    fi
elif [ "$1" == "flash" ];then
        echo "double-press reset please!"
    # sleep 5
    echo "check for a bootable RP2040..."
    RP2040_CHECK=`ioreg -p IOUSB | grep -o "RP2\ Boot" | grep -o "RP2"`
    echo "RP2040_CHECK says: $RP2040_CHECK"
    if [ "$RP2040_CHECK" == "RP2" ];then
        echo "Found an RP2 device in boot state..."
        echo "Copying the UF2 file onto the rpi boot volume..."
        qmk flash -kb $KEYBOARD -km $KEYMAP -j $BUILD_CORES
        echo "Now do an eeprom reset...unplug USB, hold down the far right key (e.g. F12)...and plug in USB."
    else
        echo "ERROR: Did not find an RP2 device in boot state!"
    fi
fi
