#include "options.h"

#include <unistd.h>

int options_parse(int argc, char *argv[], struct options *options)
{
    int opt;
    optind = 1;
    while ((opt = getopt(argc, argv, "c:")) != -1)
    {
        switch (opt)
        {
        case 'c':
            options->input = input_from_string(optarg);
            break;
        case '?':
            return -1;
        }
    }

    if (options->input == NULL)
    {
        if (optind < argc)
            options->input = input_from_file(argv[optind]);
        else
            options->input = input_from_stdin();
        return options->input == NULL ? -1 : 0;
    }

    return 0;
}
