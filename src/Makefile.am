SUBDIRS = lexer ast parser builtins

bin_PROGRAMS = 42sh

42sh_SOURCES = 42sh.c

42sh_CPPFLAGS = -I%D%

42sh_CFLAGS = -std=c99 -Werror -Wall -Wextra -Wvla -pedantic -fsanitize=address -g

42sh_LDADD = \
       lexer/liblexer.a \
       ast/libast.a \
       parser/libparser.a \
       builtins/libbuiltins.a
