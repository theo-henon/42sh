#include "token.h"

#include <ctype.h>
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

enum token_type token_word_type(const char *token)
{
    if (strcmp(token, "if") == 0)
        return TOKEN_IF;
    else if (strcmp(token, "fi") == 0)
        return TOKEN_FI;
    else if (strcmp(token, "else") == 0)
        return TOKEN_ELSE;
    else if (strcmp(token, "then") == 0)
        return TOKEN_THEN;
    else if (strcmp(token, "elif") == 0)
        return TOKEN_ELIF;
    else
        return TOKEN_WORD;
}

bool token_islist_delim(const struct token *token)
{
    // TODO add & token
    return token->type == TOKEN_EOF || token->type == TOKEN_SEMICOLON;
}

bool token_isclist_delim(const struct token *token)
{
    return token->type == TOKEN_EOF || token->type == TOKEN_SEMICOLON
        || token->type == TOKEN_EOL;
}

bool is_not_word(char c)
{
    return c == '\0' || c == '\n' || c == ';' || isblank(c) || c == '\'';
}
