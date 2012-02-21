#!/bin/sh
APPDATA="$HOME/.kde/share/apps"
MENUFILE="$APPDATA/be.shell/MainMenu/kate.xml"

echo '<submenu>' > "$MENUFILE"
echo '   <menu label="Kate">' >> "$MENUFILE"
for name in "$APPDATA"/kate/sessions/*.katesession; do
    name=${name##*/}
    name=${name%.katesession}
    vname="${name//%/\\x}"
    printf "      <action label=\"$vname\" exec=\"kate -n -s \'$vname\'\"/>\n" >> "$MENUFILE"
done
echo '      <separator/>' >> "$MENUFILE"
echo '      <action label="Update" exec="be.katesessions.sh"/>' >> "$MENUFILE"
echo '   </menu>' >> "$MENUFILE"
echo '</submenu>' >> "$MENUFILE"
touch "$APPDATA/be.shell/MainMenu.xml"
