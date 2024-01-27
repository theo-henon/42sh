#ifndef BUILTINS_H
#define BUILTINS_H

#include "visitor/visitor.h"

#define BUILTIN_COUNT 5

typedef int (*builtin_t)(char **argv, struct visitor *visitor);

struct builtin
{
    const char *name;
    builtin_t func;
};

int builtin_cd(char **argv, struct visitor *visitor);
int builtin_exit(char **argv, struct visitor *visitor);
int builtin_echo(char **argv, struct visitor *visitor);
int builtin_true(char **argv, struct visitor *visitor);
int builtin_false(char **argv, struct visitor *visitor);
builtin_t builtins_find(const char *name);

#endif /* ! BUILTINS_H */
