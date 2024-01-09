MODULE = parser

lib_LIBRARIES = lib$(MODULE).a

libparser_a_SOURCES =  \
	$(MODULE).c \
	$(MODULE).h \
	io.c \
	io.h

libparser_a_CFLAGS= -std=c99 -pedantic -Werror -Wall -Wextra -Wvla

noinst_LIBRARIES = lib$(MODULE).a
