#ifndef OPTIONS_H
#define OPTIONS_H

#include <stdbool.h>

#include "lexer/io.h"

struct options
{
    struct input *input;
    bool pretty_print;
};

int options_parse(int argc, char *argv[], struct options *options);

#endif // OPTIONS_H
