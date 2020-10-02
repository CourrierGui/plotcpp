# Maintainer: Courrier Guillaume <courrier.guillaume.123@gmail.com>
pkgname=plotcpp
pkgver=0.1.1
pkgrel=1
epoch=0
pkgdesc="Simple C++ plot library."
arch=('x86_64')
url="https://github.com/CourrierGui/plotcpp"
license=('MIT')
groups=()
depends=('qcustomplot' 'qt5-base')
makedepends=()
checkdepends=()
optdepends=()
provides=()
conflicts=()
replaces=()
backup=()
options=('!buildflags')
install=
changelog=
source=()
noextract=()
md5sums=()
validpgpkeys=()

prepare() {
	git clone $url "$pkgname-$pkgver"
	mkdir -p "$pkgname-$pkgver"/build
}

build() {
	cd "$pkgname-$pkgver"
	cmake -B build
	cmake --build build -DCMAKE_BUILD_TYPE=Release
}

check() {
	cd "$pkgname-$pkgver"/build
}

package() {
	cd "$pkgname-$pkgver"
	cmake --install build --prefix "$pkgdir"/usr
}
