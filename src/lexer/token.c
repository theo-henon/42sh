#include "token.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct token *token_create(enum token_type type, char *value)
{
    struct token *new_token = calloc(1, sizeof(struct token));
    if (!new_token)
    {
        fprintf(stderr, "Fail allocation!\n");
        return NULL;
    }
    new_token->value = value;
    new_token->type = type;
    return new_token;
}

void token_free(struct token *token)
{
    if (!token)
        return;
    free(token->value);
    free(token);
}

static const char *token_to_string(const struct token *token)
{
    switch (token->type)
    {
    case TOKEN_EOF:
        return "EOF";
    case TOKEN_EOL:
        return "EOL";
    case TOKEN_SEMICOLON:
        return ";";
    case TOKEN_WORD:
        return token->value;
    case TOKEN_IF:
        return "if";
    case TOKEN_THEN:
        return "then";
    case TOKEN_FI:
        return "fi";
    case TOKEN_ELSE:
        return "else";
    default:
        return NULL;
    }
}

void token_print(const struct token *token)
{
    if (token == NULL)
        return;
    puts(token_to_string(token));
}
