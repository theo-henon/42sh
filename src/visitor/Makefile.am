lib_LIBRARIES = libvisitor.a

libvisitor_a_SOURCES =  \
	and_or_visitor.c and_or_visitor.h \
	list_visitor.c list_visitor.h \
	pipeline_visitor.c pipeline_visitor.h \
	simple_cmd_visitor.c simple_cmd_visitor.h \
	if_visitor.c if_visitor.h \
	visitor.c visitor.h

libvisitor_a_CPPFLAGS = -I$(top_srcdir)/src -D_POSIX_C_SOURCE=202401L

libvisitor_a_CFLAGS= -std=c99 -pedantic -Wall -Werror -Wextra -Wvla

noinst_LIBRARIES = libvisitor.a
