%.h: ${MYLIB}/%.tex
	${top_srcdir}/tcode $< $@

%.h: ${UNITTESTS}/%.tex
	${top_srcdir}/tcode $< $@
	
include Makefile.def

include_HEADERS = $(MYLIBHEADERS) $(UNITTESTSHEADERS) gdefconf.h

noinst_HEADERS = $(MYLIBTEX) $(UNITTESTSTEX)
noinst_SCRIPTS = makedef

CLEANFILES = $(MYLIBHEADERS) $(UNITTESTSHEADERS) gdefconf.h
MAINTAINERCLEANFILES = Makefile.in Makefile.def
