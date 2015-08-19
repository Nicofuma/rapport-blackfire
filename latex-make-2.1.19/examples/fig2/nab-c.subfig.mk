fig2/nab-c_1.fig: fig2/nab-c.fig fig2/nab-c.subfig
	$(COMMON_PREFIX)bin/figdepth.py             < $< > $@ 10 15 20 50 55

fig2/nab-c_2.fig: fig2/nab-c.fig fig2/nab-c.subfig
	$(COMMON_PREFIX)bin/figdepth.py             < $< > $@ 30 50 55 80

fig2/nab-c_3.fig: fig2/nab-c.fig fig2/nab-c.subfig
	$(COMMON_PREFIX)bin/figdepth.py             < $< > $@ 30 40 50 55 80

fig2/nab-c_4.fig: fig2/nab-c.fig fig2/nab-c.subfig
	$(COMMON_PREFIX)bin/figdepth.py             < $< > $@ 25 35 50 90

fig2/nab-c_5.fig: fig2/nab-c.fig fig2/nab-c.subfig
	$(COMMON_PREFIX)bin/figdepth.py             < $< > $@ 15 35 50 60

FIG2/NAB-C_FIGS := $(foreach n,  1  2  3  4  5  , fig2/nab-c_$(n).fig)
FILES_TO_DISTCLEAN += $(FIG2/NAB-C_FIGS)
FIGS2CREATE_LIST += $(FIG2/NAB-C_FIGS)
$(TEMPORAIRE): $(FIG2/NAB-C_FIGS)
$(TEMPORAIRE): $(FIG2/NAB-C_FIGS)
