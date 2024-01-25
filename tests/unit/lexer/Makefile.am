bin_PROGRAMS = lexer_tests

lexer_tests_SOURCES = token_tests.c lexer_tests.c io_tests.c

lexer_tests_CPPFLAGS = -I$(top_builddir)/src

lexer_tests_CFLAGS = -std=c99 -Wall -Wextra -Wvla -pedantic

lexer_tests_LDADD = \
       $(top_builddir)/src/lexer/liblexer.a \
       -lcriterion

check-local:
	./lexer_tests
