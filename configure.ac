# Process this file with autoconf to produce a configure script.
AC_INIT
AM_INIT_AUTOMAKE(murpi, 0.1)
AC_CONFIG_SRCDIR([src/main.cc])
AM_CONFIG_HEADER(config.h)
CXXFLAGS="-Wall -O6"

# Extra variables.
COPYRIGHT="2002  Volker Grabsch <vog@uni.de>"
AC_SUBST(COPYRIGHT)
AC_DEFINE_UNQUOTED(COPYRIGHT, "$COPYRIGHT", Copyright)

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_MAKE_SET
AC_PROG_AWK

# Checks for libraries.

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST

# Checks for library functions.

AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT
