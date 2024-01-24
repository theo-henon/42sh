#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "builtins.h"

int builtin_cd(char **argv)
{
    if (argv[1] == NULL)
    {
        char *home = getenv("HOME");
        if (home != NULL)
        {
            if (chdir(home) != 0)
            {
                fprintf(stderr, "Error chdir ! \n");
                return -1;
            }
        }
        else
        {
            printf("cd: HOME not set\n");
            return -1;
        }
    }
    else
    {
        if (chdir(argv[1]) != 0)
        {
            fprintf(stderr, "Error chdir !\n");
            return -1;
        }
    }
    return 0;
}
