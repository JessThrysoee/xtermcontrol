#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.
#
# Compile pedantic and with debug symbols:
#    CFLAGS="-ggdb -Wall -Wextra -pedantic -ansi -O0" ./configure
#
# Verbose output can be enabled with
#    "./configure --disable-silent-rules" or "make V=1"
#

AC_INIT(xtermcontrol, 2.11, )
AC_CONFIG_SRCDIR([src/xtermcontrol.c])
AC_CONFIG_HEADER([config.h])

AM_INIT_AUTOMAKE

XTC_PACKAGE_DATE

m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])

# Checks for programs.
AC_PROG_CC

# features of Posix that are extensions to C (define _GNU_SOURCE)
AC_USE_SYSTEM_EXTENSIONS

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([fcntl.h libintl.h stdlib.h string.h strings.h termios.h unistd.h wchar.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([memset regcomp strchr strrchr strstr])
AC_CHECK_FUNC([snprintf], [], AC_MSG_ERROR([required function missing]))

AC_CONFIG_FILES([Makefile
                 doc/Makefile
                 src/Makefile
                 tests/Makefile])
AC_OUTPUT
