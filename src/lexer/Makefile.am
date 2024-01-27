lib_LIBRARIES = liblexer.a

liblexer_a_SOURCES =  \
	io.c io.h \
	lexer.c lexer.h \
	token.c token.h \
	word.c word.h

liblexer_a_CPPFLAGS = -I$(top_srcdir)/src -D_POSIX_C_SOURCE=202401L

liblexer_a_CFLAGS= -std=c99 -pedantic -Werror -Wall -Wextra -Wvla

noinst_LIBRARIES = liblexer.a
