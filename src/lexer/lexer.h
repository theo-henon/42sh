#ifndef LEXER_H
#define LEXER_H

#include <stdbool.h>
#include <stddef.h>

#include "token.h"

enum lexer_status
{
    LEXER_OK,
    LEXER_END,
    LEXER_INVALID_TOKEN
};

struct lexer
{
    char *input;
    size_t offset;
    enum lexer_status status;
    struct token *current;
    bool single_quote;
};

struct lexer *lexer_create(char *input);
void lexer_free(struct lexer *lexer);
char *lexer_cursor(struct lexer *lexer);
struct token *lexer_peek(struct lexer *lexer);
struct token *lexer_pop(struct lexer *lexer);

#endif /*! LEXER_H */
