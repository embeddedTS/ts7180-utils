#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT(ts4100-utils, 1.0, mark@embeddedTS.com)
AC_CONFIG_SRCDIR([src/tshwctl.c])
#AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE([1.00 foreign no-define])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.
# FIXME: Replace `main' with a function in `-lm':
AC_CHECK_LIB([m], [main])

# Checks for header files.
AC_CHECK_HEADERS([fcntl.h stdint.h stdlib.h string.h sys/ioctl.h termios.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_INLINE
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT8_T

# Checks for library functions.
AC_CHECK_FUNCS([strtoull])

AC_CONFIG_FILES([Makefile
                 src/Makefile])
AC_OUTPUT
