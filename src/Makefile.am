AM_CPPFLAGS = @VMOD_INCLUDES@ -Wall -Werror

vmoddir = @VMOD_DIR@
vmod_LTLIBRARIES = libvmod_jemalloc.la

libvmod_jemalloc_la_LDFLAGS = -module -export-dynamic -avoid-version -shared

libvmod_jemalloc_la_SOURCES = \
	vmod_jemalloc.c

nodist_libvmod_jemalloc_la_SOURCES = \
	vcc_if.c \
	vcc_if.h

vmod_jemalloc.lo: vcc_if.c vcc_if.h

vcc_if.c: vcc_if.h

vcc_if.h: @VMODTOOL@ $(top_srcdir)/src/vmod_jemalloc.vcc
	@VMODTOOL@ $(top_srcdir)/src/vmod_jemalloc.vcc

VMOD_TESTS = $(top_srcdir)/src/tests/*.vtc
.PHONY: $(VMOD_TESTS)

$(top_srcdir)/src/tests/*.vtc: libvmod_jemalloc.la
	@VARNISHTEST@ -Dvarnishd=@VARNISHD@ -Dvmod_topbuild=$(abs_top_builddir) $@

check: $(VMOD_TESTS)

EXTRA_DIST = \
	vmod_jemalloc.vcc \
	$(VMOD_TESTS)

CLEANFILES = \
	$(builddir)/vcc_if.c \
	$(builddir)/vcc_if.h \
	$(builddir)/vmod_jemalloc.rst \
	$(builddir)/vmod_jemalloc.man.rst
