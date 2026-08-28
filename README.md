# xtermcontrol

xtermcontrol enables dynamic control of xterm properties: colors, font,
title, geometry, and more. See the xtermcontrol(1) manpage.

## Building from a git clone

Requires autoconf and automake.

    autoreconf -fi
    ./configure
    make
    make install

Release tarballs include the generated configure script, so they build
with just `./configure && make`.

To remove all generated files and restore a pristine tree:

    git clean -dXf

