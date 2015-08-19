
ARCHIVE_NAME=latex-make

all: ctan

ctan: $(ARCHIVE_NAME).zip

$(ARCHIVE_NAME).zip: $(ARCHIVE_NAME) FORCE
	cd $(ARCHIVE_NAME) && \
	zip ../$@ *

$(ARCHIVE_NAME): FORCE
	mkdir -p $@
	$(MAKE) -C .. check
	cp ../src/*.dtx ../src/*.ins ../src/*.pdf README $@
	< ../INSTALL sed -e 's,go to the src/ directory and ,,' \
		-e '/The example[/] directory contains/d' \
		-e '/this software. .to be improved, patches welcome./d' \
		>> $@/README

FORCE:

.phony: FORCE all ctan clean distclean

clean:
	$(RM) -r $(ARCHIVE_NAME)

distclean: clean
	$(RM) $(ARCHIVE_NAME).zip
