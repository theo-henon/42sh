#include "token.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct token *token_create(enum token_type type, char *value, unsigned row, unsigned col)
{
    struct token *new_token = calloc(1, sizeof(struct token));
    if (!new_token)
    {
        fprintf(stderr, "Fail allocation!\n");
        return NULL;
    }
    new_token->value = value;
    new_token->type = type;
    new_token->row = row;
    new_token->col = col;
    return new_token;
}

void token_free(struct token *token)
{
    if (!token)
        return;
    free(token->value);
    free(token);
}

void token_print(struct token *token)
{
    // TODO: Trouver une convention pour le pretty print des tokens
    token++;
}
