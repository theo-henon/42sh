#include "lexer.h"

#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "token.h"

static void skip_blanks(struct lexer *lexer)
{
    char c = input_readchar(lexer->input);
    while (isblank(c))
        c = input_readchar(lexer->input);
}

static void skip_comment(struct lexer *lexer)
{
    char c = input_readchar(lexer->input);
    while (c != '\0' && c != '\n')
        c = input_readchar(lexer->input);
}

static char *read_word(struct input *input)
{
    char c = input_getchar(input);
    char *word = NULL;
    size_t len = 0;
    do
    {
        word = realloc(word, ++len + 1);
        word[len - 1] = '\0';
        word[len - 2] = c;
    } while (!is_not_word(c));
    return word;
}

static struct token *lexer_read(struct lexer *lexer)
{
    enum token_type type;
    char *value = NULL;
    char c = input_readchar(lexer->input);
    switch (c)
    {
    case '\0':
        type = TOKEN_EOF;
        lexer->status = LEXER_END;
        break;
    case '\n':
        type = TOKEN_EOL;
        break;
    case ';':
        type = TOKEN_SEMICOLON;
        break;
    case '\'':
        type = TOKEN_SINGLEQUOTE;
        break;
    case ' ':
    case '\t':
        type = TOKEN_BLANK;
        break;
    default:
        type = TOKEN_WORD;
        value = read_word(lexer->input);
    }

    if (value == NULL)
        value = strndup(&c, 1);
    if (value == NULL)
        lexer->status = LEXER_INVALID_TOKEN;

    lexer->current = token_create(type, value);
    return lexer->current;
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

    if (!lexer->single_quote)
        skip_blanks(lexer);

    char c = input_readchar(lexer->input);
    if (!lexer->single_quote && c == '#')
        skip_comment(lexer);

    struct token *token = lexer_read(lexer);
    if (token->type == TOKEN_WORD)
        token_set_type(token);
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
