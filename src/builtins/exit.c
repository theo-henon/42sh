//#include "builtins.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "visitor/visitor.h"
int builtin_exit(char **argv, __attribute__((unused)) struct visitor *visitor)
{
    int exit_code = 0;
    if (argv[1])
    {
        if (isdigit(argv[1][0]) == 0)
        {
            fprintf(stderr, "numeric argument required for exit\n");
            exit(2);
        }
        exit_code = atoi(argv[1]);
    }
    exit(exit_code);
}
