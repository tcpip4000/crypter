#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.65])
AC_INIT([crypter],[1.2.5],[soporte@er-technology.net],[],[http://github.com/tcpip4000/crypter])
AM_INIT_AUTOMAKE
AC_CONFIG_MACRO_DIR([m4])
LT_PREREQ([2.2])
AC_CONFIG_SRCDIR([src/modaler.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC
AM_PROG_CC_C_O
AC_PROG_CC_C99
LT_INIT([dlopen])

# Checks for libraries.
have_gpg_error=no
AC_SEARCH_LIBS([gpg_strerror], [gpg-error], [have_gpg_error=yes])
have_gcrypt=no
AC_SEARCH_LIBS([gcry_cipher_decrypt], [gcrypt], [have_gcrypt=yes])

# Checks for headers
AC_CHECK_HEADERS([stdlib.h string.h stdio.h crypter.h])
AS_IF([test "x${have_gcrypt}" = xyes],
    [AC_CHECK_HEADERS([gcrypt.h], [], [have_gcrypt=no])])

# Checks for existence
if test "x${have_gpg_error}" = xno; then
    echo ""
    echo "Error: -----------------------------------"
    echo " The gpg_error library is required to     "
    echo " build crypter. Stopping...               "
    echo " Check 'config.log' for more information. "
    echo "------------------------------------------"
    (exit 1); exit 1;
fi

if test "x${have_gcrypt}" = xno; then
    echo ""
    echo "Error: -----------------------------------"
    echo " The gcrypt header and library file is   "
    echo " required to build crypter. Stopping...   "
    echo " Check 'config.log' for more information. "
    echo "------------------------------------------"
    (exit 1); exit 1;
fi

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.
AC_CHECK_FUNCS([memset])

AC_CONFIG_FILES([Makefile
                 libcrypter/Makefile
                 src/Makefile])

AC_OUTPUT
