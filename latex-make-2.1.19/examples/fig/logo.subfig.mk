fig/logo_1.svg: fig/logo.svg fig/logo.subfig
	$(COMMON_PREFIX)bin/svgdepth.py             < $< > $@ logo_latex

fig/logo_2.svg: fig/logo.svg fig/logo.subfig
	$(COMMON_PREFIX)bin/svgdepth.py             < $< > $@ logo_cnrs

fig/logo_3.svg: fig/logo.svg fig/logo.subfig
	$(COMMON_PREFIX)bin/svgdepth.py             < $< > $@ ex_text ex_rect

FIG/LOGO_FIGS := $(foreach n,  1  2  3  , fig/logo_$(n).svg)
FILES_TO_DISTCLEAN += $(FIG/LOGO_FIGS)
FIGS2CREATE_LIST += $(FIG/LOGO_FIGS)
$(TEMPORAIRE): $(FIG/LOGO_FIGS)
$(TEMPORAIRE): $(FIG/LOGO_FIGS)
