#!/bin/sh
rm -Rf debian
cp -Rf debian-upstream debian
cat debian/changelog.in | sed "s/##DATE##/`date +%Y%m%d`/g" | sed "s/##RDATE##/`date -R`/g" | sed "s/##DIST##/`lsb_release -cs`/g" > debian/changelog
debuild -b
fakeroot debian/rules clean
rm -Rf debian
#blind change to force update

