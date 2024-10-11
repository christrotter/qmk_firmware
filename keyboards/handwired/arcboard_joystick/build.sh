#!/bin/bash
HOME_DIR=/Users/christrotter/git/printing/qmk_fw
KEYBOARD='handwired/arcboard_joystick'
KEYMAP='joystick'
BUILD_CORES=12

if [ -z "$1" ];then
    echo "ERROR: Specify build or flash!"
    exit 1
else
    echo "INFO: We are going to $1"
fi

cd $HOME_DIR

if [ "$1" == "build" ];then
    echo "INFO: Just doing a build..."
    qmk lint -kb $KEYBOARD
    qmk compile -kb $KEYBOARD -km $KEYMAP -j $BUILD_CORES
elif [ "$1" == "flash" ];then
    echo "INFO: Flashing..."
    qmk lint -kb $KEYBOARD
    #make $KEYBOARD:$KEYMAP:dfu
    qmk flash -bl dfu -kb $KEYBOARD -km $KEYMAP -j $BUILD_CORES
    #dfu-programmer atmega32u4 flash
else
    echo "WARN: You didn't specify either 'build' or 'flash'."
fi
