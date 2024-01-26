//#include "builtins.h"
#include <stdlib.h>

#include "visitor/visitor.h"
int builtin_exit(char **argv, __attribute__((unused)) struct visitor *visitor)
{
    int exit_code = 0;
    exit_code = atoi(argv[1]);
    exit(exit_code);
}
