#!/bin/sh

rm -f \
compile \
depcomp \
aclocal.m4 \
config.h \
config.h.in \
config.log \
config.status \
config.h.in~ \
configure \
missing \
install-sh \
stamp-h1 \
Makefile \
Makefile.in \
src/Makefile \
src/Makefile.in \
doc/Makefile \
doc/Makefile.in \
tests/Makefile \
tests/Makefile.in

rm -rf a.out.dSYM
rm -rf autom4te.cache

autoreconf -fi
