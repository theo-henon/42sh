#include "lexer/io.h"

int main(int argc, char *argv[])
{
    char *res = io(argc, argv);
    printf("command: %s\n", res);
    return 0;
}
