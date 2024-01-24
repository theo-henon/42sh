bin_PROGRAMS = builtins_tests

builtins_tests_SOURCES = builtins_tests.c

builtins_tests_CPPFLAGS = -I$(top_builddir)/src

builtins_tests_CFLAGS = -std=c99 -Wall -Wextra -Wvla -pedantic

builtins_tests_LDADD = \
       $(top_builddir)/src/builtins/libbuiltins.a \
       -lcriterion

check-local: builtins_tests
	./builtins_tests       
