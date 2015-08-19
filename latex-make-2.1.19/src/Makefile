
####[ Check Software ]################################################
ifeq ($(filter else-if,$(.FEATURES)),)
$(error GNU Make 3.81 needed. Please, update your software.)
	exit 1
endif

####[ Default installation ]##########################################
prefix=/usr/local

texmf_prefix=$(prefix)/share/texmf

PKGNAME=latex-make

INCLUDEDIR=$(prefix)/include

LATEXDIR=$(texmf_prefix)/tex/latex/$(PKGNAME)
LATEXCFGDIR=$(texmf_prefix)/tex/latex/$(PKGNAME)
DOCDIR=$(texmf_prefix)/doc/latex/$(PKGNAME)
SCRIPTSDIR=$(texmf_prefix)/scripts/$(PKGNAME)

SCRIPTS=figdepth.py gensubfig.py svg2dev.py svgdepth.py latexfilter.py
INCFILES=LaTeX.mk
STYFILES=$(wildcard *.sty)
CFGFILES=$(wildcard *.cfg)
DOCFILES=$(wildcard *.pdf)


####[ Targets ]######################################################

all: generate

.PHONY: all generate install

SCRIPTS=figdepth.py gensubfig.py svg2dev.py svgdepth.py latexfilter.py

GENFILES= figlatex.sty figlatex.cfg texgraphicx.sty \
		pdfswitch.sty texdepends.sty \
		LaTeX.mk LaTeX.mk.conf $(SCRIPTS)

DTX_SOURCES=$(wildcard *.dtx)

generate: $(GENFILES)

install: $(GENFILES) doc
	install -d $(DESTDIR)$(LATEXDIR)
	install -m 644 $(STYFILES) $(DESTDIR)$(LATEXDIR)
	install -d $(DESTDIR)$(LATEXCFGDIR)
	install -m 644 $(CFGFILES) $(DESTDIR)$(LATEXCFGDIR)
	install -d $(DESTDIR)$(SCRIPTSDIR)
	install -m 755 $(SCRIPTS) $(DESTDIR)$(SCRIPTSDIR)
	install -m 644 $(INCFILES) $(DESTDIR)$(SCRIPTSDIR)
	install -d $(DESTDIR)$(INCLUDEDIR)
	ln -sf $(SCRIPTSDIR)/LaTeX.mk $(DESTDIR)$(INCLUDEDIR)/
	install -d $(DESTDIR)$(DOCDIR)
	install -m 644 $(DOCFILES) $(DESTDIR)$(DOCDIR)
	if [ -f $(texmf_prefix)/ls-R ]; then texhash $(texmf_prefix) ; fi

$(GENFILES): stamp.latex-make

stamp.latex-make: latex-make.ins $(DTX_SOURCES)
	latex latex-make.ins
	chmod +x $(SCRIPTS)
	touch $@

distclean::
	$(RM) $(GENFILES) stamp.latex-make

clean::
	$(RM) latex-make.log

doc: pdf

LU_MASTERS=figlatex texdepends latex-make  #pdfswitch texdepends

DEPENDS=LaTeX.mk $(SCRIPTS)
latex-make_MAIN=latex-make.dtx
figlatex_MAIN=figlatex.dtx
texdepends_MAIN=texdepends.dtx

#LATEX=latex -v

# Force using local LaTeX.mk and not system-wide LaTeX.mk if already installed
# Depends on $(GENFILES) so that $(_lu_which) give good results
$(CURDIR)/LaTeX.mk: $(GENFILES)
	/bin/cp --help > /dev/null 2>&1 || ( \
		sed -e '/LU_UTILS/s/GNU/MACOSX/' < $@ > $@.new && \
		mv $@.new $@ )

-include $(CURDIR)/LaTeX.mk

