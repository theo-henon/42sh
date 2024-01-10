#include "lexer.h"

#include <stdio.h>
#include <stdlib.h>

struct lexer *lexer_create(char *input)
{
    struct lexer *new_lexer = calloc(1, sizeof(struct lexer));
    if (!new_lexer)
    {
        fprintf(stderr, "Fail allocation!\n");
        return NULL;
    }
    new_lexer->input = input;
    return new_lexer;
}

void lexer_free(struct lexer *lexer)
{
    if (!lexer)
        return;
    free(lexer);
}
