
CLEANFILES = $(PACKAGE).1 changelog.txt

ROOTNAME = xtermcontrol
## Date used in manpage header
PACKAGE_DATE = @PACKAGE_DATE@

man_MANS = $(PACKAGE).1
EXTRA_DIST = $(ROOTNAME).roff ctlseqs.txt

all: $(PACKAGE).1

$(PACKAGE).1: $(ROOTNAME).roff
	@PACKAGE_CAPS=`echo $(PACKAGE) | tr [a-z] [A-Z]`;\
	echo '.\" troff' > $@;\
	echo ".ds x $(PACKAGE)" >> $@;\
	echo ".TH $$PACKAGE_CAPS 1 \"$(PACKAGE_DATE)\" \"$(PACKAGE) $(VERSION)\" \"User Commands\"" >> $@;\
	cat $(srcdir)/$(ROOTNAME).roff >> $@;\
	echo "Copyright \(co 2002-$(PACKAGE_YEAR) Jess Thrysoee <jess@thrysoee.dk>" >> $@;

changelog.txt: ../ChangeLog
	@sed 's/@/ (at)/g;s/&/\&amp;/g;s/</\&lt;/g;s/>/\&gt;/g' $(srcdir)/$< > $@;

