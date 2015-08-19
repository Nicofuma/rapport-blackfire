fig/nab-a_1.fig: fig/nab-a.fig fig/nab-a.subfig
	$(COMMON_PREFIX)bin/figdepth.py             < $< > $@ 10 15 20 50 55

fig/nab-a_2.fig: fig/nab-a.fig fig/nab-a.subfig
	$(COMMON_PREFIX)bin/figdepth.py             < $< > $@ 30 50 55 80

fig/nab-a_3.fig: fig/nab-a.fig fig/nab-a.subfig
	$(COMMON_PREFIX)bin/figdepth.py             < $< > $@ 30 40 50 55 80

fig/nab-a_4.fig: fig/nab-a.fig fig/nab-a.subfig
	$(COMMON_PREFIX)bin/figdepth.py             < $< > $@ 25 35 50 90

fig/nab-a_5.fig: fig/nab-a.fig fig/nab-a.subfig
	$(COMMON_PREFIX)bin/figdepth.py             < $< > $@ 15 35 50 60

FIG/NAB-A_FIGS := $(foreach n,  1  2  3  4  5  , fig/nab-a_$(n).fig)
FILES_TO_DISTCLEAN += $(FIG/NAB-A_FIGS)
FIGS2CREATE_LIST += $(FIG/NAB-A_FIGS)
$(TEMPORAIRE): $(FIG/NAB-A_FIGS)
$(TEMPORAIRE): $(FIG/NAB-A_FIGS)
