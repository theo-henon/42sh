bin_PROGRAMS = ast_tests

ast_tests_SOURCES = ast_tests.c simple_cmd_tests.c

ast_tests_CPPFLAGS = -I$(top_builddir)/src

ast_tests_CFLAGS = -std=c99 -Wall -Wextra -Wvla -pedantic

ast_tests_LDADD = \
       $(top_builddir)/src/ast/libast.a \
       -lcriterion

check-local:
	./ast_tests
