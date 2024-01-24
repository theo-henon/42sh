lib_LIBRARIES = libbuiltins.a

libbuiltins_a_SOURCES =  \
	builtins.c builtins.h \
	booleans.c \
	echo.c \
	cd.c \
	exit.c

libbuiltins_a_CPPFLAGS = -I$(top_srcdir)/src -D_POSIX_C_SOURCE=202401L

libbuiltins_a_CFLAGS= -std=c99 -pedantic -Werror -Wall -Wextra -Wvla

noinst_LIBRARIES = libbuiltins.a
