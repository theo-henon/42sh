#include <stddef.h>

#include "builtins.h"

int builtin_true(char **argv)
{
    argv++;
    return 0;
}

int builtin_false(char **argv)
{
    argv++;
    return 1;
}
