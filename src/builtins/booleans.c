#include <stddef.h>

#include "builtins.h"

int builtin_true(__attribute__((unused)) char **argv)
{
    return 0;
}

int builtin_false(__attribute__((unused)) char **argv)
{
    return 1;
}
