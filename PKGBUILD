# Author: RickaPrincy <rckprincy@gmail.com>
pkgname=templi
pkgver=3.1.0
pkgrel=1
pkgdesc="Templi is a simple tool designed to expedite the template file generation process"
arch=('x86_64')
depends=('rcli')
url="https://github.com/RickaPrincy/Templi"
license=('MIT')
source=("templi_archlinux@$pkgver.tar.gz::https://github.com/RickaPrincy/Templi/releases/download/v$pkgver/templi_archlinux@$pkgver.tar.gz")

sha256sums=("c861ab51e5dc5cc2ca257c5f6d73236cef155fdbd940b923ca9b5b99eb517b26")

package() {
    echo "Installing to \"$pkgdir/usr/\""
    mkdir -p "$pkgdir/usr/include"
    mkdir -p "$pkgdir/usr/lib"
    mkdir -p "$pkgdir/usr/bin"
    cp -r "templi_archlinux@$pkgver/include" "$pkgdir/usr"
    cp -r "templi_archlinux@$pkgver/lib" "$pkgdir/usr"
    cp -r "templi_archlinux@$pkgver/bin" "$pkgdir/usr"
}
