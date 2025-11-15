#!/bin/bash
KB_PATH=handwired/arcboard_mk20
HOME_DIR=/Users/christrotter/git/qmk_firmware
KB_DIR=$HOME_DIR/keyboards/$KB_PATH
USER_DIR=$HOME_DIR/users/christrotter

BUILD_CORES=12
KEYMAP='christrotter'
KEYBOARD='handwired/arcboard_mk20'

if [ -z "$1" ];then
    echo "ERROR: Specify build, or flash!"
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
elif [ "$1" == "flash" ];then
    qmk flash -kb $KEYBOARD -km $KEYMAP -j $BUILD_CORES
fi
