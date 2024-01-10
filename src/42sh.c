#include "lexer/io.h"

int main(int argc, char *argv[])
{
    char *res = io(argc, argv);
    printf("command: %s\n", res);
    free(res);
    return 0;
}
