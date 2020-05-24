# Build
qmake
make

## Try locally
./bin/Pentanimos

## Install
sudo make install

## Play
/usr/bin/Pentanimos

# Remove
sudo make uninstall

# Clean
make distclean

# Build Debian package
dpkg-buildpackage -rfakeroot -us -uc
