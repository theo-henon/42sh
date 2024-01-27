#include "simple_cmd.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

struct simple_cmd *simple_cmd_init(void)
{
    errno = 0;
    struct simple_cmd *simple_cmd = calloc(1, sizeof(struct simple_cmd));
    if (!simple_cmd)
    {
        perror("Cannot init a simple_cmd");
        return NULL;
    }
    simple_cmd->base.type = SIMPLE_CMD;
    simple_cmd->argc = 1;

    return simple_cmd;
}

void simple_cmd_addarg(struct simple_cmd *cmd, char *arg)
{
    errno = 0;
    cmd->argc++;
    cmd->args = realloc(cmd->args, cmd->argc * sizeof(char *));
    if (!cmd->args)
        perror("Fail to add an arg to simple_cmd\n");
    else
    {
        cmd->args[cmd->argc - 2] = arg;
        cmd->args[cmd->argc - 1] = NULL;
    }
}

void simple_cmd_print(const struct simple_cmd *cmd)
{
    for (int i = 0; i < cmd->argc - 1; i++)
    {
        printf("%s", cmd->args[i]);
        if (i + 1 < cmd->argc - 1)
            printf(" ");
    }
}

void simple_cmd_free(struct simple_cmd *cmd)
{
    if (cmd == NULL)
        return;

    if (cmd->args != NULL)
        for (int i = 0; i < cmd->argc; i++)
            free(cmd->args[i]);
    free(cmd->args);
    free(cmd);
}
