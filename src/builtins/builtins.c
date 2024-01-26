#include "builtins.h"

#include <stdlib.h>
#include <string.h>


static struct builtin builtins[BUILTIN_COUNT] =
{
    {.name = "echo", .func = builtin_echo},
    {.name = "cd", .func = builtin_cd},
    {.name = "false", .func = builtin_false},
    {.name = "true", .func = builtin_true},
    {.name = "exit", .func = builtin_exit}
};

builtin_t builtins_find(const char *name)
{
    for (int i = 0; i < BUILTIN_COUNT; i++)
        if (strcmp(builtins[i].name, name) == 0)
            return builtins[i].func;
    return NULL;
}
