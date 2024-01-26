lib_LIBRARIES = libexpansion.a

libexpansion_a_SOURCES =  \
	quotes.c quotes.h \
	simple_cmd_expansion.c simple_cmd_expansion.h

libexpansion_a_CPPFLAGS = -I$(top_srcdir)/src -D_POSIX_C_SOURCE=202401L

libexpansion_a_CFLAGS= -std=c99 -pedantic -Werror -Wall -Wextra -Wvla

noinst_LIBRARIES = libexpansion.a
