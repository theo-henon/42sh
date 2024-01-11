#ifndef SIMPLE_CMD_H
#define SIMPLE_CMD_H

#include "ast.h"


struct simple_cmd 
{
    struct base base;
    char **args;
};


#endif /* ! SIMPLE_CMD_H */