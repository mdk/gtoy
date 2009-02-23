MAINTAINERCLEANFILES		= Makefile.in

all-local: gtoy-@GTOY_MAJORMINOR@.pc

gtoy-@GTOY_MAJORMINOR@.pc: gtoy.pc
	cp $< $@

pkgconfigdir			= $(libdir)/pkgconfig
pkgconfig_DATA			= gtoy-@GTOY_MAJORMINOR@.pc

EXTRA_DIST			= gtoy.pc.in
CLEANFILES			= gtoy-@GTOY_MAJORMINOR@.pc
