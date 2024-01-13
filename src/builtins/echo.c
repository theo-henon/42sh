#include <stdio.h>
#include <string.h>

#include "builtins.h"

static int echo_n_flag(char **argv)
{
    int i = 1;
    if (argv[i] == NULL)
        return 0;
    while (argv[i + 1] != NULL)
    {
        printf("%s ", argv[i]);
        i++;
    }
    printf("%s", argv[i]);
    return 0;
}

static int echo_e_flag(char **arguments)
{
    if (arguments == NULL || arguments[1] == NULL)
    {
        puts("");
        return 0;
    }

    for (int i = 1; arguments[i] != NULL; ++i)
    {
        char *argument = arguments[i];
        while (*argument != '\0')
        {
            if (*argument == '\\')
            {
                argument++;
                switch (*argument)
                {
                case 'n':
                    putchar('\n');
                    break;
                case 't':
                    putchar('\t');
                    break;
                case '\\':
                    putchar('\\');
                    break;
                default:
                    break;
                }
            }
            else
            {
                putchar(*argument);
            }
            ++argument;
        }
        putchar(' ');
    }
    return 1;
}

static int tablen(char **arg)
{
    int i = 0;
    while (arg[i])
        i++;
    return i;
}

int builtin_echo(char **argv)
{
    argv++;
    int argc = tablen(argv);
    if (argc >= 1 && argv[0][0] == '-')
    {
        if (strcmp(argv[0], "-n") == 0)
        {
            return echo_n_flag(argv);
        }
        if (strcmp(argv[0], "-e") == 0)
        {
            return echo_e_flag(argv);
        }
        if (strcmp(argv[0], "-E") == 0)
        {
            argv++;
        }
    }

    int i = 0;
    while (argv[i] != NULL)
    {
        printf("%s ", argv[i]);
        i++;
    }
    printf("\n");
    return 0;
}