#!/bin/bash

if [ $# != 2 ]; then
    echo "usage: $0 <width> <height>"
    exit;
fi

DIR="${1}x${2}"

if [ -e "$DIR" ]; then
    echo -n "A version for $DIR already exists. Do you want to replace it [y/N] "
    read reply
    if [ "$reply" != "y" ] && [ "$reply" != "Y" ]; then
        exit 0
    fi
fi

mkdir "$DIR" 2>/dev/null

ratio=$(( $1 * 1000 / $2 ))

if (( $ratio == 1600 )); then #scale
    echo tata
    convert -scale $DIR! -filter lanczos ../../kdm/tibanna/background.jpg "$DIR/background.png"
    convert -scale $DIR! -filter lanczos flash.png "$DIR/flash.png"
elif (( $ratio < 1600 )); then #crop width
    W=$(( $1 * 1200 / $2 ))
    X=$(( (1920-$W)/2 ))
    convert -crop ${W}x1200+${X}+0 -scale $DIR! -filter lanczos ../../kdm/tibanna/background.jpg "$DIR/background.png"
else # crop height
    H=$(( 1920 * $2 / $1 ))
    Y=$(( (1200-$H)/2 ))
    convert -crop 1920x${H}+0+${Y} -scale $DIR! -filter lanczos ../../kdm/tibanna/background.jpg "$DIR/background.png"
fi

H=$(( 282*$2 / 1200 ))
convert -scale $((7*$1))x${H}! -filter lanczos flash.png "$DIR/flash.png"

Y=$(( ($2*464)/1200 ))



if [ ! -e Preview.png ]; then
    convert -crop 1600x1200+160+0 -scale 400x300! -filter lanczos ../../kdm/tibanna/background.jpg Preview.png
fi

echo "SCALE OFF
BACKGROUND_IMAGE 0 0 background.png

ANIM 1 0 $Y 7 flash.png 80
WAIT_STATE kded
STOP_ANIM 1

ANIM 2 0 $Y 7 flash.png 80
WAIT_STATE kcminit
STOP_ANIM 2

ANIM 3 0 $Y 7 flash.png 80
WAIT_STATE ksmserver
STOP_ANIM 3

ANIM 4 0 $Y 7 flash.png 80
WAIT_STATE wm
STOP_ANIM 4

ANIM 5 0 $Y 7 flash.png 80
WAIT_STATE desktop
STOP_ANIM 5

ANIM 6 0 $Y 7 flash.png 80
WAIT_STATE ready
STOP_ANIM 6
" > "$DIR/description.txt"
