#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT([elm-demo-tizen-mobile], [0.1], [amitesh.sh@samsung.com])
AC_CONFIG_SRCDIR([src/main.c])
AC_CONFIG_HEADERS([config.h])

AC_CONFIG_AUX_DIR([.])
AM_INIT_AUTOMAKE([foreign])
# Checks for programs.
AC_PROG_CC
AC_CONFIG_MACRO_DIR([m4])
# Checks for libraries.
CapiCheck = 0
DESKTOP=0
AC_CHECK_LIB([capi-appfw-application],[app_efl_exit],[CapiCheck=1],[CapiCheck=0])
# Checks for header files.
# Checks for typedefs, structures, and compiler characteristics.
AC_LIBTOOL_DLOPEN
LT_INIT
AC_PROG_LIBTOOL
# Checks for library functions.
PKG_CHECK_MODULES([ELEMENTARY],[elementary])
PKG_CHECK_MODULES([EFLEXTENSION],[efl-extension])

if test $CapiCheck == 1
then
    PKG_CHECK_MODULES([CAPIFW],[capi-appfw-application])
else
    DESKTOP=1
fi
AC_SUBST([DESKTOP])
AC_DEFINE_UNQUOTED([DESKTOP],[${DESKTOP}],["Desktop build is enabled"])

AC_CONFIG_FILES([Makefile
            data/Makefile
            data/edc/Makefile
            data/images/Makefile
            src/Makefile
            ])
AC_OUTPUT
