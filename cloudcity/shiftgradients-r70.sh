#!/bin/sh
echo
if [ "$1" = "-R" ]; then
echo "REVERSIVE MODE!!!
"
fi
echo "This script should be called ONCE! when changing to rev. >= 70
A backup is created at $HOME/.config/Bespin/Store.bak
If you want to revert this, call $0 -R!
"
read -n 1 -p "Do you really want to proceed? (y/N) " answ
echo
if [ "$answ" != "y" -a "$answ" != "Y" ]; then
exit
fi

if [ "$1" != "-R" ]; then
echo "\"$HOME/.config/Bespin/Store.conf\" to \"$HOME/.config/Bespin/Store.bak\""
cp $HOME/.config/Bespin/Store.conf $HOME/.config/Bespin/Store.bak
fi

echo "shift gradient types"

if [ "$1" = "-R" ]; then
sed -ie "s/Gradient=2/Gradient=x/; s/Gradient=3/Gradient=2/; s/Gradient=4/Gradient=3/; s/Gradient=5/Gradient=4/; s/Gradient=x/Gradient=5/;" $HOME/.config/Bespin/Store.conf
else
sed -ie "s/Gradient=5/Gradient=x/; s/Gradient=4/Gradient=5/; s/Gradient=3/Gradient=4/; s/Gradient=2/Gradient=3/; s/Gradient=x/Gradient=2/;" $HOME/.config/Bespin/Store.conf
fi
echo "...done! (NOTICE that your current settings have not been altered)"
