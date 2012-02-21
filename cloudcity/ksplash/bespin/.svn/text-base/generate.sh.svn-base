#!/bin/bash

if [ $# != 2 ]; then
    echo "usage: $0 <width> <height>"
    exit;
fi

X=$(( ($1-740)/2 ))
Y=$(( ($2-420)/2 ))
DIR="${1}x${2}"

mkdir "$DIR" 2>/dev/null

if [ ! -e "$DIR/background.png" ]; then
    convert -scale $DIR! -filter lanczos ../../kdm/bespin/background.jpg "$DIR/background.png"
fi

if [ ! -e Preview.png ]; then
    convert -scale 740x420! -filter lanczos ../../kdm/bespin/background.jpg ".tmp.png"
    convert -crop 740x420+6660+0 pulse.png ".tmp2.png"
    convert ".tmp.png" ".tmp2.png" -gravity Center -composite Preview.png
    mogrify -scale 400x300 -filter lanczos Preview.png
    rm -f ".tmp.png" ".tmp2.png"
fi

echo "SCALE OFF
BACKGROUND_IMAGE 0 0 background.png

ANIM 1 $X $Y 10 ../init.png 80 1
WAIT_STATE kded
STOP_ANIM 1

ANIM 2 $X $Y 10 ../pulse.png 80 1
WAIT_STATE kcminit
STOP_ANIM 2

ANIM 3 $X $Y 10 ../pulse.png 80 1
WAIT_STATE ksmserver
STOP_ANIM 3

ANIM 4 $X $Y 10 ../pulse.png 80 1
WAIT_STATE wm
STOP_ANIM 4

ANIM 5 $X $Y 10 ../pulse.png 80 1
WAIT_STATE desktop
STOP_ANIM 5

ANIM 6 $X $Y 10 ../pulse.png 80 1
WAIT_STATE ready
STOP_ANIM 6
" > "$DIR/description.txt"
