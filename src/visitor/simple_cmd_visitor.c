#include "simple_cmd_visitor.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#include "builtins/builtins.h"
#include "expansion/simple_cmd_expansion.h"

int simple_cmd_visit(struct visitor *visitor, struct simple_cmd *cmd)
{
    expand_simple_cmd(cmd);

    builtin_t builtin = builtins_find(cmd->args[0]);
    if (builtin == NULL)
    {
        errno = 0;
        int pid = fork();
        if (pid == -1)
        {
            perror("Cannot fork");
            return 2;
        }

        if (pid == 0)
        {
            // Child process
            errno = 0;
            if (execvp(cmd->args[0], cmd->args) == -1)
            {
                fprintf(stderr, "cmd == %s\n", cmd->args[0]);
                perror("Failed to execute command");
            }
            exit(127);
        }

        // Parent process
        int status;
        if (waitpid(pid, &status, 0) == -1)
        {
            perror("Error waiting the child process");
            return 2;
        }
        return WIFEXITED(status) ? WEXITSTATUS(status) : 2;
    }
    else
        return builtin(cmd->args, visitor);
}
