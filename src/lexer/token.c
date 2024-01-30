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

void token_set_type(struct token *token)
{
    if (strcmp(token->value, "if") == 0)
        token->type = TOKEN_IF;
    else if (strcmp(token->value, "fi") == 0)
        token->type = TOKEN_FI;
    else if (strcmp(token->value, "else") == 0)
        token->type = TOKEN_ELSE;
    else if (strcmp(token->value, "then") == 0)
        token->type = TOKEN_THEN;
    else if (strcmp(token->value, "elif") == 0)
        token->type = TOKEN_ELIF;
    else if (strcmp(token->value, "while") == 0)
        token->type = TOKEN_WHILE;
    else if (strcmp(token->value, "do") == 0)
        token->type = TOKEN_DO;
    else if (strcmp(token->value, "done") == 0)
        token->type = TOKEN_DONE;
    else if (strcmp(token->value, "until") == 0)
        token->type = TOKEN_UNTIL;
    else
        token->type = TOKEN_WORD;
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

bool istoken(char c)
{
    return c == '\0' || c == '\n' || c == ';';
}
