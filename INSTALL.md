# Build
qmake
make

## Try locally
./bin/Pentaminos

## Install
sudo make install

## Play
/usr/bin/Pentaminos

# Remove
sudo make uninstall

# Clean
make distclean

# Build Debian package
dpkg-buildpackage -rfakeroot -us -uc
