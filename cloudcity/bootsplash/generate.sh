#!/bin/sh

dest=${2:-"/etc/bootsplash/themes"}

if [ "$1" = "install" ]; then
    echo -e "\nInstalling files to $dest/Bespin\n
    Please enter your sudo password:\n"
    sudo cp -rfd Bespin $dest/
    exit
fi

csize=$(fbresolution)
size=${1:-${csize}}

width=${size%x*}
height=${size#*x}

if [ ! $width ] || [ ! $height ]; then
    echo "usage: $0 <width>x<height>"
    exit
fi

if [ "$(which convert 2>/dev/null )" = "" ]; then
    echo "Sorry, you need ImageMagick to do this"
    exit
fi

read -n1 -p "Do you have a widescreen (16:10) monitor? [y/N] " WIDESCREEN
if [ "$WIDESCREEN" = "y" ] || [ "$WIDESCREEN" = "Y" ]; then
    WIDESCREEN=true
else
    WIDESCREEN=false
fi

if [ ! -d Bespin ]; then mkdir Bespin; fi
if [ ! -d Bespin/config ]; then mkdir Bespin/config; fi
if [ ! -d Bespin/images ]; then mkdir Bespin/images; fi

if $WIDESCREEN; then
    SILENT=silent-16210.jpg
    SPLASH=bootsplash-16210.jpg
else
    SILENT=silent.jpg
    SPLASH=bootsplash.jpg
fi

convert -quality 85 -scale ${width}x${height}! $SPLASH Bespin/images/bootsplash-${width}x${height}.jpg
convert -quality 85 -scale ${width}x${height}! $SILENT Bespin/images/silent-${width}x${height}.jpg

X2=$((1024*$width/1280))
X3=$((512*$width/1280))
Y1=$((918*$height/1024))
Y2=$((926*$height/1024))

TX=$((45*$width/1280))
TY=0
TW=$((1196*$width/1280))
TH=$((846*$height/1024))

echo -e "
# This is a bootsplash configuration file for
# Bespin, resolution ${width}x${height}.
#
# See www.bootsplash.org for more information.
# Written by Thomas Lübking <thomas.luebking@web.de>
#
version=3
state=1
progress_enable=0
overpaintok=1


fgcolor=7
bgcolor=0

tx=$TX
ty=$TY
tw=$TW
th=$TH

jpeg=$dest/Bespin/images/bootsplash-${width}x${height}.jpg
silentjpeg=$dest/Bespin/images/silent-${width}x${height}.jpg

trigger \"isdown\" quit
trigger \"rlreached 5\" toverbose
trigger \"rlchange 0\" tosilent
trigger \"rlchange 6\" tosilent


progress_enable=1
box silent noover 0 $Y1 $X2 $Y2 #ffffff10
box silent inter 0 $Y1 $X3 $Y2 #ffffff80
box silent 0 $Y1 $X2 $Y2 #ffffff80

" > Bespin/config/bootsplash-${width}x${height}.cfg

echo -e "
# This is a bootsplash configuration file for
# Bespin, resolution ${width}x${height}.
#
# See www.bootsplash.org for more information.
# Written by Thomas Lübking <thomas.luebking@web.de>
#
version=3
state=1

fgcolor=7
bgcolor=0

tx=$TX
ty=$TY
tw=$TW
th=$TH

jpeg=$dest/Bespin/images/bootsplash-${width}x${height}.jpg

" > Bespin/config/${width}x${height}.cfg

exit

