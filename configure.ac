AC_INIT([GToy object system for C], [0.1.0], [mdk@mdk.am], [gtoy])
AC_CANONICAL_SYSTEM

AM_CONFIG_HEADER(config.h)
AC_CONFIG_SRCDIR([src/gtoy.h])
AC_CONFIG_MACRO_DIR([m4])
AM_MAINTAINER_MODE

# define PACKAGE_VERSION_* variables
AS_VERSION

# set the libtool versioning
AS_LIBTOOL(GTOY, 0, 0, 0)

GTOY_MAJORMINOR=$PACKAGE_VERSION_MAJOR.$PACKAGE_VERSION_MINOR
AC_SUBST(GTOY_MAJORMINOR)
AC_DEFINE_UNQUOTED(GTOY_MAJORMINOR, "$GTOY_MAJORMINOR", [library major.minor version])

AM_INIT_AUTOMAKE

AC_PROG_CC
AM_PROG_LIBTOOL

AM_PATH_GLIB_2_0([2.8.0], HAS_GLIB=yes, HAS_GLIB=no, [])
if test "x${HAS_GLIB}" != xyes ; then
        AC_ERROR([You need a recent version of glib to compile this package!])
fi

# subs the glib
AC_SUBST(GLIB_CFLAGS)
AC_SUBST(GLIB_LIBS)

# GTOY_OBJ_*
# default vars for all internal objects built on top of gtoy
# includes all the low-level flags
GTOY_OBJ_CFLAGS="\$(CFLAGS) \$(GLIB_CFLAGS) -I\$(top_builddir)/src/"
GTOY_OBJ_LIBS="\$(top_builddir)/src/libgtoy-$GTOY_MAJORMINOR.la \$(GLIB_LIBS)"
AC_SUBST(GTOY_OBJ_CFLAGS)
AC_SUBST(GTOY_OBJ_LIBS)

# build examples (or not)
AC_ARG_WITH(examples, 
            AC_HELP_STRING([--with-examples], [Build the examples]),
            [
             case "${withval}" in
                     yes) BUILD_EXAMPLES=yes ;;
                     no)  BUILD_EXAMPLES=no ;;
                     *)   AC_MSG_ERROR(bad value ${withval} for --with-examples) ;;
             esac],
             [BUILD_EXAMPLES=no])

AM_CONDITIONAL(BUILD_EXAMPLES, test "x$BUILD_EXAMPLES" = "xyes")

# just print out our status
if test x$BUILD_EXAMPLES = xyes; then
        AC_MSG_NOTICE(Will locally build example programs)
else
        AC_MSG_NOTICE(Will not build examples )
fi

AC_CONFIG_FILES([Makefile src/Makefile pkgconfig/Makefile                       \
                 pkgconfig/gtoy.pc examples/Makefile                            \
                 examples/example-01/Makefile examples/example-02/Makefile      \
                 examples/example-09/Makefile                                   \
                 examples/example-03/Makefile examples/example-04/Makefile      \
                 examples/example-05/Makefile examples/example-06/Makefile      \
                 examples/example-07/Makefile                                   \
                 examples/example-08/Makefile examples/example-10/Makefile])

AC_OUTPUT
