#!/bin/bash

if [ $# != 2 ]; then
    echo "usage: $0 <width> <height>"
    exit;
fi

X1=$(( ($1-630)/2 ))
Y1=$(( ($2-630)/2 ))
X2=$(( ($1-399)/2 ))
Y2=$(( ($2-399)/2 ))
DIR="${1}x${2}"

mkdir "$DIR" 2>/dev/null

if [ ! -e "$DIR/background.png" ]; then
    convert -resize ${DIR}^ -gravity Center -crop ${DIR}+0+0 +repage -filter lanczos ../../kdm/aperture/background.jpg "$DIR/background.png"
fi

echo "SCALE OFF
BACKGROUND_IMAGE 0 0 background.png

ANIM 1 $X1 $Y1 8 intro.png 60 1
WAIT_STATE kded
STOP_ANIM 1

ANIM 2 $X2 $Y2 6 splash.png 40 0
WAIT_STATE ready
STOP_ANIM 2
" > "$DIR/description.txt"
