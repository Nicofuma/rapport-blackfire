ifeq ($(filter else-if,$(.FEATURES)),)
$(error GNU Make 3.81 or latter needed. Please, update your software.)
	exit 1
endif

.PHONY: all install clean distclean dist ctan

PKGNAME=latex-make

all:
	$(MAKE) -C src doc

check: all
	$(MAKE) -C examples

install: all
	$(MAKE) -C src $@

clean distclean:
	-$(MAKE) -C examples $@
	-$(MAKE) -C MacOSX $@
	-$(MAKE) -C ctan $@
	$(MAKE) -C src $@

VERSION=$(shell cat VERSION)

dist:
	if [ -d .svn ]; then \
		$(MAKE) dist-svn; \
	elif [ -d .git ]; then \
		$(MAKE) dist-git; \
	else \
		echo "No way to build dist without SCM"; \
		exit 1; \
	fi
	$(MAKE) dist-ctan

dist-svn:
	if [ "$$(svn st)" != "" ] ;then svn st ; exit 1 ; fi
	svn export . $(PKGNAME)-$(VERSION)
	tar cvzf $(PKGNAME)-$(VERSION).tar.gz $(PKGNAME)-$(VERSION)
	rm -rf $(PKGNAME)-$(VERSION)

dist-git:
	if ! LC_ALL=C git status | grep -sq '^nothing to commit' ; then git status ; exit 1 ; fi
	git archive --format=tar --prefix=$(PKGNAME)-$(VERSION)/ HEAD | gzip -9 > $(PKGNAME)-$(VERSION).tar.gz

dist-ctan:
	$(MAKE) -C ctan
