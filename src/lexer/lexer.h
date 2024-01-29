#ifndef LEXER_H
#define LEXER_H

#include <stdbool.h>
#include <stddef.h>

#include "io.h"
#include "token.h"

enum lexer_status
{
    LEXER_OK,
    LEXER_END,
    LEXER_INVALID_TOKEN,
    LEXER_UNEXPECTED_EOF,
};

struct lexer
{
    struct input *input;
    enum lexer_status status;
    struct token *current;
};

struct lexer *lexer_create(struct input *input);
void lexer_free(struct lexer *lexer);
struct token *lexer_peek(struct lexer *lexer);
struct token *lexer_pop(struct lexer *lexer);

#endif /*! LEXER_H */
