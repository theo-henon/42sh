#include <stddef.h>

//#include "builtins.h"
#include "visitor/visitor.h"

int builtin_true(__attribute__((unused)) char **argv,
                 __attribute__((unused)) struct visitor *visitor)
{
    return 0;
}

int builtin_false(__attribute__((unused)) char **argv,
                  __attribute__((unused)) struct visitor *visitor)
{
    return 1;
}
