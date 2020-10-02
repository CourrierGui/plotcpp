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

pkgver() {
	cd "$srcdir/$pkgname"
	echo "$pkgver.$(git rev-parse --short HEAD)"
}

prepare() {
	if [ -d "$srcdir/$pkgname/.git" ]
	then
		cd "$srcdir/$pkgname"; git pull origin master
	else
		git clone $url "$srcdir/$pkgname"
	fi
	mkdir -p "$srcdir/$pkgname/build"
}

build() {
	cd "$srcdir/$pkgname"
	cmake -B build -DCMAKE_BUILD_TYPE=Release
	cmake --build build
}

package() {
	cd "$srcdir/$pkgname"
	cmake --install build --prefix "$pkgdir"/usr
}
