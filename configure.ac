AC_INIT([scrm], [1.3.9000],[https://github.com/paulstaab/scrm/issues])
AM_INIT_AUTOMAKE([subdir-objects -Wall -Werror foreign])

# Suppress output at compilation
m4_ifndef([AM_SILENT_RULES], [m4_define([AM_SILENT_RULES],[])])
AM_SILENT_RULES([yes])

# Load macros in 'm4'-dir
m4_include([m4/m4_ax_cxx_compile_stdcxx_11.m4])
AC_CONFIG_MACRO_DIR([m4])

AC_PROG_INSTALL
AC_PREREQ
AC_CANONICAL_HOST

# Checks for programs.
AC_PROG_RANLIB

# Check for C++11
AX_CXX_COMPILE_STDCXX_11(,mandatory)

# Checks for libraries
AC_CHECK_LIB(cppunit,TestCase,[])

# Checks for header files for scrm.
AC_HEADER_STDC
AC_LANG(C++) 

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_C_INLINE
AC_TYPE_SIZE_T

# Checks for library functions.
#AC_FUNC_MALLOC (breaks cross-compilate for windows)
#AC_FUNC_REALLOC

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
