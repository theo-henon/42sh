#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "builtins.h"

static int tablen(char **arg)
{
    int i = 0;
    while (arg[i])
        i++;
    return i;
}

static void echo_n_flag(char **args, int index)
{
    if (index >= tablen(args))
        return;
    int i;
    for (i = index; args[i + 1] != NULL; i++)
        printf("%s ", args[i]);
    printf("%s", args[i]);
}

static void print_special(char c)
{
    switch (c)
    {
    case 'n':
        printf("\n");
        break;
    case 't':
        printf("\t");
        break;
    case '\\':
        printf("\\");
        break;
    default:
        printf("%c", c);
    }
}

static void echo_e_flag(char **args, int index)
{
    if (index >= tablen(args))
        return;
    int i;
    int j;
    for (i = index; args[i] != NULL; i++)
    {
        for (j = 0; args[i][j] != '\0'; j++)
        {
            if (args[i][j] == '\\')
            {
                j++;
                print_special(args[i][j]);
            }
            else
            {
                printf("%c", args[i][j]);
            }
        }
        if (args[i + 1] != NULL)
            printf(" ");
    }
}

int flags_parsing(char *argv[], int *line_feed, int *interpret)
{
    int argc = tablen(argv);
    int opt;
    opterr = 0;
    *line_feed = 1;
    *interpret = 0;
    int is_valide = 1;
    while ((opt = getopt(argc, argv, "neE")) != -1)
    {
        switch (opt)
        {
        case 'n':
            *line_feed = 0;
            break;
        case 'e':
            *interpret = 1;
            break;
        case 'E':
            *interpret = 0;
            break;
        default:
            is_valide = 0;
            optind--;
            break;
        }
        if (is_valide == 0)
            break;
    }
    return optind;
}

int builtin_echo(char **argv)
{
    int line_feed;
    int interpret;
    int index = flags_parsing(argv, &line_feed, &interpret);

    if (interpret == 1)
    {
        echo_e_flag(argv, index);
        if (line_feed == 1)
            puts("");
    }
    else
    {
        if (line_feed == 0)
            echo_n_flag(argv, index);
        else
        {
           echo_n_flag(argv, index);
           putchar('\n');
        }
    }
    return 0;
}

