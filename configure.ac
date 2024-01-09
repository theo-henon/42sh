AC_INIT([42sh], [1.0])

AM_INIT_AUTOMAKE([])

AM_SILENT_RULES([yes])

AM_PROG_AR      #check ar
AC_PROG_RANLIB  #check ranlib

AX_COMPILER_FLAGS([], [], [], [-Wall -Wextra -Werror -Wvla -pedantic -std=c99])

AC_CONFIG_FILES([
                    Makefile
                    src/Makefile
                    src/parser/Makefile
                ])

AC_OUTPUT
