
AUTOMAKE_OPTIONS = foreign

EXTRA_DIST = README.md

SUBDIRS = src doc tests

.PHONY: test
test:
	cd "$(top_builddir)/tests" && $(MAKE) $@;
