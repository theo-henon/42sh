#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


#include "builtins.h"

int builtin_cd(char **argv, __attribute__((unused)) struct visitor *visitor)
{

    char *home = getenv("HOME");
    if (strcmp(argv[1], "-") == 0)
    {
        printf("%s", home);
        return 0;
    }
    if (argv[1] == NULL)
    {
        if (home != NULL)
        {
            if (chdir(home) != 0)
            {
                fprintf(stderr, "Error chdir ! \n");
                return 1;
            }
        }
        else
        {
            printf("cd: HOME not set\n");
            return 1;
        }
    }
    else
    {
        if (chdir(argv[1]) != 0)
        {
            fprintf(stderr, "Error chdir !\n");
            return 1;
        }
    }
    return 0;
}
