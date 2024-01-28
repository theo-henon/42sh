#ifndef OPTIONS_H
#define OPTIONS_H

#include <stdbool.h>

#include "lexer/io.h"

struct options
{
    struct input *input;
#ifdef PRETTY_PRINT
    bool pretty_print;
#endif // PRETTY_PRINT
};

int options_parse(int argc, char *argv[], struct options *options);

#endif // OPTIONS_H
