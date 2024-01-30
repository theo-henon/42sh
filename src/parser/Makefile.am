lib_LIBRARIES = libparser.a

libparser_a_SOURCES =  \
	and_or_parser.c and_or_parser.h \
	cmd_parser.c cmd_parser.h \
	if_parser.c if_parser.h \
	list_parser.c list_parser.h \
	parser.c parser.h \
	pipeline_parser.c pipeline_parser.h \
	if_parser.c if_parser.h \
	while_parser.c while_parser.h \
	until_parser.c until_parser.h

libparser_a_CPPFLAGS = -I$(top_srcdir)/src -D_POSIX_C_SOURCE=202401L

libparser_a_CFLAGS= -std=c99 -pedantic -Werror -Wall -Wextra -Wvla

noinst_LIBRARIES = libparser.a
