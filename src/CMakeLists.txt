cmake_minimum_required(VERSION 2.4)


PROJECT(rapport NONE)

SET(LATEX_DEFAULT_BUILD pdf)

SET(LATEX_COMPILER_FLAGS
  "-interaction=nonstopmode;--enable-write18;--shell-escape"
  CACHE STRING "Flags passed to latex."
)

INCLUDE(../UseLATEX.cmake)
#  
ADD_LATEX_DOCUMENT(main.tex
	INPUTS title.tex style.tex minted.sty glossaire.tex existant/blackfire.tex existant/blackfire-sonde.tex existant/blackfire-sonde.tex existant/blackfire-agent.tex existant/blackfire-api.tex existant/python.tex existant/python-tiers.tex existant/python-tiers-new_relic.tex existant/python-tiers-optbeat.tex existant/python-python.tex existant/python-python-c_profiler.tex existant/python-python-wsgi.tex probl/ux.tex probl/ux-on_demand.tex probl/mesure.tex probl/mesure-intrumentation.tex probl/mesure-temps.tex probl/mesure-memoire.tex probl/mesure-fonc_args.tex probl/mesure-io.tex probl/api.tex probl/api-comm_agent.tex existant.tex probl.tex annexe/new-relic_decoration-methodes.tex codes/new-relic_decoration_modules.py existant/python-python-pycallgraph.tex existant/python-python-pyinstrument.tex existant/python-python-yappi.tex impl.tex impl/python.tex impl/c.tex codes/probe/blackfire/bootstrap/sitecustomize.py codes/probe/blackfire/wsgi_wrapper.py codes/probe/blackfire/config.py codes/probe/test_wsgi.py contexte.tex codes/profile.dat codes/pile_struct.c codes/graph_struct.c codes/PyCFunctionObject.c annexes.tex
	IMAGE_DIRS images/logo images/ images/schemas/workflow/
	BIBFILES rapport.bib
	USE_GLOSSARY
	USE_INDEX
	)
