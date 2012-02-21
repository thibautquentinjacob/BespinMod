#Contributor: <thomas.luebking@gmail.com>

pkgname=bespin
_realname=bespin
pkgver=1
_upstream_ver=1
pkgrel=1
pkgdesc="Advanced Qt style, KWin deco, XBar plugin"
arch=('i686' 'x86_64')
#url="http://kde-look.org/content/show.php?content=117542&forumpage=0"
depends=('kdebase-workspace>=4.6.0')
makedepends=('cmake' 'automoc4' 'gcc')
license=('GPL')

build()
{
    SRC_DIR="$PWD"
    cd ..
	for sd in '.' 'animator' 'blib' 'config' 'XBar' 'kwin'; do
        mkdir -p src/$sd
        pushd $sd
        for name in *; do
            if [ ! -d "$name" ]; then
                ln -ft "$SRC_DIR/$sd/" "$name"
            fi
        done
        popd
    done
    cd src
    rm -f src pgk

    if [ ! -d build ]; then
        ./configure
    fi
    cd build
    make || return 1

    make DESTDIR=$pkgdir install
}
