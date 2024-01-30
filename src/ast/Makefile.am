lib_LIBRARIES = libast.a

libast_a_SOURCES =  \
	and_or.c and_or.h \
	ast.c ast.h \
	if.c if.h \
	list.c list.h \
	pipeline.c pipeline.h \
	simple_cmd.c simple_cmd.h \
	while.c while.h

libast_a_CPPFLAGS = -I$(top_srcdir)/src -D_POSIX_C_SOURCE=202401L

libast_a_CFLAGS= -std=c99 -pedantic -Werror -Wall -Wextra -Wvla

noinst_LIBRARIES = libast.a
