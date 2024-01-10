#ifndef LEXER_H
#define LEXER_H

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
    unsigned row;
    unsigned col;
    enum lexer_status lexer_status;
    struct token *current;
};

struct lexer *lexer_create(char *input);
void lexer_free(struct lexer *lexer);
struct token *lexer_peek(struct lexer *lexer);
struct token *lexer_pop(struct lexer *lexer);

#endif /*! LEXER_H */
