#include "simple_cmd.h"

#include <stdlib.h>

struct simple_cmd *create_simple_cmd(char **args)
{
    struct simple_cmd *simple_cmd = calloc(1, sizeof(struct simple_cmd));
    simple_cmd->base.type = SIMPLE_CMD;
    simple_cmd->args = args;

    return simple_cmd;
}

void free_simple_cmd(struct simple_cmd *cmd)
{
    char **tmp = cmd->args;
    while (*tmp)
    {
        free(*tmp);
        tmp++;
    }
    free(cmd);
}
