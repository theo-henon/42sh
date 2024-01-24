bin_PROGRAMS = visitor_tests

visitor_tests_SOURCES = visitor_tests.c

visitor_tests_CPPFLAGS = -I$(top_builddir)/src

visitor_tests_CFLAGS = -std=c99 -Wall -Wextra -Wvla -pedantic

visitor_tests_LDADD = \
       $(top_builddir)/src/visitor/libvisitor.a \
       -lcriterion


check-local: visitor_tests
	./visitor_tests
