AM_CFLAGS = $(VARNISHAPI_CFLAGS) -Wall -Werror
AM_LDFLAGS = $(VARNISHAPI_LIBS) $(VMOD_LDFLAGS)

vmod_LTLIBRARIES = libvmod_jemalloc.la

libvmod_jemalloc_la_SOURCES = \
	vmod_jemalloc.c

nodist_libvmod_jemalloc_la_SOURCES = \
	vcc_jemalloc_if.c \
	vcc_jemalloc_if.h

dist_man_MANS = vmod_jemalloc.3

@BUILD_VMOD_JEMALLOC@

AM_TESTS_ENVIRONMENT = \
	PATH="$(VMOD_TEST_PATH)" \
	LD_LIBRARY_PATH="$(VARNISH_LIBRARY_PATH)"
TEST_EXTENSIONS = .vtc
VTC_LOG_COMPILER = varnishtest -v
AM_VTC_LOG_FLAGS = -Dvmod_jemalloc="$(VMOD_JEMALLOC)"

TESTS = @VMOD_TESTS@

EXTRA_DIST = \
	vmod_jemalloc.vcc \
	$(VMOD_TESTS)
