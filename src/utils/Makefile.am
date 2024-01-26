lib_LIBRARIES = libutils.a

libutils_a_SOURCES =  \
	strbuilder.c strbuilder.h

libutils_a_CPPFLAGS = -I$(top_srcdir)/src -D_POSIX_C_SOURCE=202401L

libutils_a_CFLAGS= -std=c99 -pedantic -Werror -Wall -Wextra -Wvla

noinst_LIBRARIES = libutils.a
