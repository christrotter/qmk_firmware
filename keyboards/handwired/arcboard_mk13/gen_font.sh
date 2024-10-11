#!/bin/bash

FONT_FILE="$1"
FONT_SIZE=$2
FONT_NAME=$3
#if [ -z $1 ]; then
#    echo "No font file specified!"
#    echo "Defaulting to Futura Heavy..."
#    FONT_FILE="graphics/futura/Futura Heavy font.ttf"
#fi

if [ -z $2 ]; then
    echo "No font size specified!"
    exit 1
fi
if [ -z $3 ]; then
    echo "No font name specified!  This is required cuz i was not willing to spend time doing name formatting."
    exit 1
fi

echo "Making a new font from "$FONT_FILE", size: $FONT_SIZE"
qmk painter-make-font-image --font "$FONT_FILE" --size $FONT_SIZE -o $FONT_NAME.png

echo "Making new font files from image..."
qmk painter-convert-font-image --input $FONT_NAME.png -f mono4

