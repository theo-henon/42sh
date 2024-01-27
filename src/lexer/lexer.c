#include "lexer.h"

#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "token.h"
#include "utils/strbuilder.h"
#include "word.h"

static char lexer_skip_comment(struct lexer *lexer)
{
    char c = input_readchar(lexer->input);
    while (c != '\0' && c != '\n')
        c = input_readchar(lexer->input);
    return c;
}

static char lexer_skip_blanks(struct lexer *lexer)
{
    char c = input_readchar(lexer->input);
    while (isblank(c))
        c = input_readchar(lexer->input);
    return c;
}

struct lexer *lexer_create(struct input *input)
{
    if (input == NULL)
        return NULL;

    errno = 0;
    struct lexer *lexer = calloc(1, sizeof(struct lexer));
    if (lexer != NULL)
        lexer->input = input;
    else
        perror("Cannot create lexer");
    return lexer;
}

struct token *lexer_pop(struct lexer *lexer)
{
    token_free(lexer->current);
    lexer->current = NULL;

    enum token_type type;
    struct string *value = NULL;
    char first = input_readchar(lexer->input);

    if (first == '#')
        first = lexer_skip_comment(lexer);
    if (isblank(first))
        first = lexer_skip_blanks(lexer);

    switch (first)
    {
    case '\0':
        type = TOKEN_EOF;
        break;
    case '\n':
        type = TOKEN_EOL;
        break;
    case ';':
        type = TOKEN_SEMICOLON;
        break;
    default:
        type = TOKEN_WORD;
        value = word_lex(lexer, first);
        break;
    }

    if (lexer->status == LEXER_UNEXPECTED_EOF)
        type = TOKEN_EOF;

    if (value != NULL)
        lexer->current = token_create(type, string_tobuf(value));
    else
        lexer->current = token_create(type, strndup(&first, 1));

    if (type == TOKEN_WORD)
        token_set_type(lexer->current);
    string_free(value);
    return lexer->current;
}

struct token *lexer_peek(struct lexer *lexer)
{
    return lexer->current;
}

void lexer_free(struct lexer *lexer)
{
    if (!lexer)
        return;
    token_free(lexer->current);
    free(lexer);
}
