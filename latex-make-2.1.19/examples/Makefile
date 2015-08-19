
#COMPATIBILITY=true

all: example.pdf

example.pdf:

example.ps:

traces-tsi.pdf_DEPENDS = eps/paje.pdf

clean::
	$(RM) eps/paje.pdf

include $(CURDIR)/LaTeX.mk

# Splitting master bibfile for use with bibtopic.sty
# Thanks to bibtool program
conf_int.bib: BIB_GENRE=Conf_Int
conf_nat.bib: BIB_GENRE=Conf_Nat
revues_nat.bib: BIB_GENRE=Revue_Nat
colloques.bib: BIB_GENRE=Coll_Int
rapports.bib: BIB_GENRE=Rapport
manuels.bib: BIB_GENRE=Manuel

BIB_MASTER=danjean.bib
BIB_SLAVES=conf_int.bib conf_nat.bib colloques.bib rapports.bib \
        revues_nat.bib manuels.bib cv.bib
BIBTOOL=bibtool -r $(HOME)/travail/Biblio/bibtool/normalize

$(filter-out cv.bib, $(BIB_SLAVES)): %.bib: $(BIB_MASTER)
	< $^ $(BIBTOOL) -- 'select.by.string{genre "$(BIB_GENRE)"}' \
		| sed -e 's/^\(@[^{]*{[^{}]*[^\s,]\)[\s,]*$$/\1:publis,/' \
		| sed -e 's/\(\\cite{[^{}]*\)}/\1:publis}/g' > $@

cv.bib: %.bib: $(BIB_MASTER)
	< $^ $(BIBTOOL) -- 'select.by.string{genre "$(BIB_GENRE)"}' > $@

clean::
	$(RM) $(BIB_SLAVES)

$(CURDIR)/LaTeX.mk:
	$(MAKE) -C ../src
