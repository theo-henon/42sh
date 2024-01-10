#include <stdlib.h>

#include "lexer/io.h"

int main(int argc, char *argv[])
{
    char *res = io(argc, argv);
    if (res == NULL)
        return 2;

    printf("command: %s\n", res);
    free(res);
    return 0;
}
