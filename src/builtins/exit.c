#include "builtins.h"
#include <stdlib.h>

int builtin_exit(char **argv)
{
    int exit_code = 0;
    exit_code = atoi(argv[1]);
    exit(exit_code);
}
