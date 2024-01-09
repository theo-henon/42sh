AC_INIT([42sh], [1.0], [pierre.pagnoux@epita.fr])

AM_INIT_AUTOMAKE([subdir-objects] [foreign])

AM_SILENT_RULES([yes])

AM_PROG_AR      #check ar
AC_PROG_RANLIB  #check ranlib
AC_PROG_CC

AX_COMPILER_FLAGS([], [], [], [-Wall -Wextra -Werror -Wvla -pedantic -std=c99])

AC_CONFIG_FILES([
                    Makefile
                    src/Makefile
                    src/parser/Makefile
                ])

AC_OUTPUT
