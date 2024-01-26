#include "simple_cmd_expansion.h"

#include <stdlib.h>

#include "quotes.h"

void expand_simple_cmd(struct simple_cmd *cmd)
{
    for (int i = 0; i < cmd->argc - 1; i++)
    {
        char *old = cmd->args[i];
        cmd->args[i] = expand_squote(old);
        free(old);
    }
}
