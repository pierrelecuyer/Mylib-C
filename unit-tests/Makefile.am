include $(top_srcdir)/include/Makefile.def

lib_LTLIBRARIES = libunittests.la
libunittests_la_SOURCES = $(UNITTESTSSOURCES)
libunittests_la_LIBADD = $(top_builddir)/mylib/libmylib.la
libunittests_la_LDFLAGS = -no-undefined -version-info 0:1:0