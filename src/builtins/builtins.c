#include "builtins.h"

#include <stdlib.h>
#include <string.h>

struct builtin **builtins_load(void)
{
    int builtin_count = 5;
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

        builtins[3]->name = "cd";
        builtins[3]->func = builtin_cd;

        builtins[4]->name = "exit";
        builtins[4]->func = builtin_exit;
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

int builtins_find(struct builtin **builtins, const char *name)
{
    const struct builtin *builtin = NULL;
    int i = 0;
    while ((builtin = builtins[i]) != NULL)
    {
        if (strcmp(builtin->name, name) == 0)
            return i;
        i++;
    }
    return -1;
}
