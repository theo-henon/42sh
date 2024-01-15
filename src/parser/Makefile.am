lib_LIBRARIES = libparser.a

libparser_a_SOURCES =  \
	parser.c parser.h \
libparser_a_CPPFLAGS = -I$(top_srcdir)/src -D_POSIX_C_SOURCE=200809L

libparser_a_CFLAGS= -std=c99 -pedantic -Werror -Wall -Wextra -Wvla -fsanitize=address -g

noinst_LIBRARIES = libparser.a
