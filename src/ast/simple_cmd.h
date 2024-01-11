#ifndef SIMPLE_CMD_H
#define SIMPLE_CMD_H

#include "ast.h"

struct simple_cmd 
{
    struct base base;
    char **args;
};


struct simple_cmd *create_simple_cmd(char **args);
void free_simple_cmd(struct simple_cmd *cmd);


#endif /* ! SIMPLE_CMD_H */