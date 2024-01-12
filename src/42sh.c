#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "builtins/builtins.h"
#include "lexer/io.h"

int main(int argc, char *argv[])
{
    char *res = io(argc, argv);
    if (res == NULL)
        return 2;

    char *copy = strdup(res);
    char *token;
    char *words[1024];
    int i = 0;
    int exit_code = 0;
    token = strtok(copy, " ");
    while (token != NULL)
    {
        words[i++] = token;
        token = strtok(NULL, " ");
    }
    words[i++] = NULL;
    for (int j = 0; words[j] != NULL; j++)
    {
        if (strcmp(words[j], "echo") == 0)
        {
            builtin_echo(words + j);
            break;
        }
        if (strcmp(words[j], "true") == 0)
        {
            break;
        }
        if (strcmp(words[j], "false") == 0)
        {
            exit_code = 1;
            break;
        }
    }
    free(copy);
    free(res);
    return exit_code;
}
