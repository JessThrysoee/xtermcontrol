
CLEANFILES = $(PACKAGE).sh

ROOTNAME = xtermcontrol

EXTRA_DIST = $(ROOTNAME).test

all: $(PACKAGE).sh

test: $(PACKAGE).sh
	./$(PACKAGE).sh

$(PACKAGE).sh: $(ROOTNAME).test
	@echo '#! /bin/sh -e' > $@;\
	echo ' ' >> $@;\
	echo "XTC=\"../src/$(PACKAGE)\"" >> $@;\
	cat $(srcdir)/$(ROOTNAME).test >> $@;\
	chmod 700 $@;

