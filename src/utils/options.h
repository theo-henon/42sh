#ifndef OPTIONS_H
#define OPTIONS_H

#include <stdbool.h>

#include "lexer/io.h"

struct options
{
    struct input *input;
};

int options_parse(int argc, char *argv[], struct options *options);

#endif // OPTIONS_H
