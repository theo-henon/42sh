#include "lexer.h"

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

/*
    void token_print(struct token *token);
    Trouver une convention pour le pretty print des tokens
*/

void token_free(struct token *token)
{
    if (!token)
        return;
    free(token);
}


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

struct token *lexer_peek(struct lexer *lexer);
struct token *lexer_pop(struct lexer *lexer);