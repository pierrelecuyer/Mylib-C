%.h: ${MYLIB}/%.tex
	${top_srcdir}/tcode $< $@

include Makefile.def

include_HEADERS = $(MYLIBHEADERS) gdefconf.h

noinst_HEADERS = $(MYLIBTEX)
noinst_SCRIPTS = makedef

CLEANFILES = $(MYLIBHEADERS) gdefconf.h
MAINTAINERCLEANFILES = Makefile.in Makefile.def
