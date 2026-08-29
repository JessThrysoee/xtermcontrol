
CLEANFILES = $(PACKAGE).sh

ROOTNAME = xtermcontrol

EXTRA_DIST = $(ROOTNAME).test regression.test

check_PROGRAMS = ptytest
ptytest_SOURCES = ptytest.c

TESTS = regression.test
TESTS_ENVIRONMENT = XTC=../src/xtermcontrol PTYTEST=./ptytest

all: $(PACKAGE).sh

test: $(PACKAGE).sh
	./$(PACKAGE).sh

$(PACKAGE).sh: $(ROOTNAME).test
	@echo '#!/bin/sh' > $@;\
	echo ' ' >> $@;\
	echo "XTC=\"../src/$(PACKAGE)\"" >> $@;\
	cat $(srcdir)/$(ROOTNAME).test >> $@;\
	chmod 700 $@;

