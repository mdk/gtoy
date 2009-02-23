MAINTAINERCLEANFILES			= Makefile.in
INCLUDES 				= -DG_LOG_DOMAIN=\"GToy\"

libgtoy_@GTOY_MAJORMINOR@includedir	= $(includedir)/gtoy-@GTOY_MAJORMINOR@

libgtoy_@GTOY_MAJORMINOR@include_HEADERS= gtoy.h 		\
					  gtoy-object.h 	\
					  gtoy-object-type.h 	\
					  gtoy-interface-type.h \
					  gtoy-types.h 		\
					  gtoy-macros.h

lib_LTLIBRARIES				= libgtoy-@GTOY_MAJORMINOR@.la

libgtoy_@GTOY_MAJORMINOR@_la_SOURCES 	= gtoy-object.c 	\
					  gtoy-object-type.c 	\
					  gtoy-interface-type.c \
					  gtoy-macros.c

libgtoy_@GTOY_MAJORMINOR@_la_CFLAGS 	= $(GLIB_CFLAGS)
libgtoy_@GTOY_MAJORMINOR@_la_LIBADD 	= $(GLIB_LIBS)
libgtoy_@GTOY_MAJORMINOR@_la_LDFLAGS 	= $(GTOY_LT_LDFLAGS)


