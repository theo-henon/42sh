lib_LIBRARIES = libast.a

liblexer_a_SOURCES =  \
	ast.c ast.h \
	if.c if.h \
	list.c list.h \
    simple_cmd.c simple_cmd.h

liblexer_a_CPPFLAGS = -I$(top_srcdir)/src -D_POSIX_C_SOURCE=200809L

liblexer_a_CFLAGS= -std=c99 -pedantic -Werror -Wall -Wextra -Wvla -fsanitize=address -g

noinst_LIBRARIES = libast.a
