#include "builtins.h"

#include <stdlib.h>

struct builtin **builtins_load(void)
{
    int builtin_count = 3;
    struct builtin **builtins =
        calloc(builtin_count + 1, sizeof(struct builtin *));
    if (builtins != NULL)
    {
        for (int i = 0; i < builtin_count; i++)
        {
            builtins[i] = calloc(1, sizeof(struct builtin));
            if (builtins[i] == NULL)
            {
                builtins_free(builtins);
                return NULL;
            }
        }

        builtins[0]->name = "echo";
        builtins[0]->func = builtin_echo;

        builtins[1]->name = "true";
        builtins[1]->func = builtin_true;

        builtins[2]->name = "false";
        builtins[2]->func = builtin_false;
    }
    return builtins;
}

void builtins_free(struct builtin **builtins)
{
    if (builtins != NULL)
    {
        int i = 0;
        while (builtins[i] != NULL)
            free(builtins[i++]);
        free(builtins);
    }
}