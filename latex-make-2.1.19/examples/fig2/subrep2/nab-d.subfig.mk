fig2/subrep2/nab-d_1.fig: fig2/subrep2/nab-d.fig fig2/subrep2/nab-d.subfig
	$(COMMON_PREFIX)bin/figdepth.py             < $< > $@ 10 15 20 50 55

fig2/subrep2/nab-d_2.fig: fig2/subrep2/nab-d.fig fig2/subrep2/nab-d.subfig
	$(COMMON_PREFIX)bin/figdepth.py             < $< > $@ 30 50 55 80

fig2/subrep2/nab-d_3.fig: fig2/subrep2/nab-d.fig fig2/subrep2/nab-d.subfig
	$(COMMON_PREFIX)bin/figdepth.py             < $< > $@ 30 40 50 55 80

fig2/subrep2/nab-d_4.fig: fig2/subrep2/nab-d.fig fig2/subrep2/nab-d.subfig
	$(COMMON_PREFIX)bin/figdepth.py             < $< > $@ 25 35 50 90

fig2/subrep2/nab-d_5.fig: fig2/subrep2/nab-d.fig fig2/subrep2/nab-d.subfig
	$(COMMON_PREFIX)bin/figdepth.py             < $< > $@ 15 35 50 60

FIG2/SUBREP2/NAB-D_FIGS := $(foreach n,  1  2  3  4  5  , fig2/subrep2/nab-d_$(n).fig)
FILES_TO_DISTCLEAN += $(FIG2/SUBREP2/NAB-D_FIGS)
FIGS2CREATE_LIST += $(FIG2/SUBREP2/NAB-D_FIGS)
$(TEMPORAIRE): $(FIG2/SUBREP2/NAB-D_FIGS)
$(TEMPORAIRE): $(FIG2/SUBREP2/NAB-D_FIGS)
