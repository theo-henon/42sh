bin_PROGRAMS = parser_tests

parser_tests_SOURCES = parser_tests.c

parser_tests_CPPFLAGS = -I$(top_builddir)/src

parser_tests_CFLAGS = -std=c99 -Wall -Wextra -Wvla -pedantic

parser_tests_LDADD = \
       $(top_builddir)/src/parser/libparser.a \
       -lcriterion

check-local: parser_tests
	./parser_tests
