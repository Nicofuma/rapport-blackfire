fig/subrep/nab-b_1.fig: fig/subrep/nab-b.fig fig/subrep/nab-b.subfig
	$(COMMON_PREFIX)bin/figdepth.py             < $< > $@ 10 15 20 50 55

fig/subrep/nab-b_2.fig: fig/subrep/nab-b.fig fig/subrep/nab-b.subfig
	$(COMMON_PREFIX)bin/figdepth.py             < $< > $@ 30 50 55 80

fig/subrep/nab-b_3.fig: fig/subrep/nab-b.fig fig/subrep/nab-b.subfig
	$(COMMON_PREFIX)bin/figdepth.py             < $< > $@ 30 40 50 55 80

fig/subrep/nab-b_4.fig: fig/subrep/nab-b.fig fig/subrep/nab-b.subfig
	$(COMMON_PREFIX)bin/figdepth.py             < $< > $@ 25 35 50 90

fig/subrep/nab-b_5.fig: fig/subrep/nab-b.fig fig/subrep/nab-b.subfig
	$(COMMON_PREFIX)bin/figdepth.py             < $< > $@ 15 35 50 60

FIG/SUBREP/NAB-B_FIGS := $(foreach n,  1  2  3  4  5  , fig/subrep/nab-b_$(n).fig)
FILES_TO_DISTCLEAN += $(FIG/SUBREP/NAB-B_FIGS)
FIGS2CREATE_LIST += $(FIG/SUBREP/NAB-B_FIGS)
$(TEMPORAIRE): $(FIG/SUBREP/NAB-B_FIGS)
$(TEMPORAIRE): $(FIG/SUBREP/NAB-B_FIGS)
