#include "lexer.h"

#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "token.h"

static char *skip_blanks(struct lexer *lexer)
{
    char *cur = lexer_cursor(lexer);
    while (isblank(*cur))
    {
        lexer->offset++;
        cur++;
    }
    return cur;
}

static char *skip_comment(struct lexer *lexer)
{
    char *cur = lexer_cursor(lexer);
    while (*cur != '\0' && *cur != '\n')
    {
        lexer->offset++;
        cur++;
    }
    return cur;
}

static void wordlen(char *cur, size_t *len)
{
    while (!is_not_word(*cur))
    {
        *len += 1;
        cur++;
    }
}

static char *lexer_read(struct lexer *lexer, char *cur, enum token_type *type)
{
    size_t len = 1;
    switch (*cur)
    {
    case '\0':
        *type = TOKEN_EOF;
        len = 0;
        lexer->status = LEXER_END;
        break;
    case '\n':
        *type = TOKEN_EOL;
        break;
    case ';':
        *type = TOKEN_SEMICOLON;
        break;
    case '\'':
        *type = TOKEN_SINGLEQUOTE;
        break;
    case ' ':
    case '\t':
        *type = TOKEN_BLANK;
        break;
    default:
        *type = TOKEN_WORD;
        wordlen(cur + 1, &len);
    }

    char *value = strndup(cur, len);
    if (value == NULL)
        lexer->status = LEXER_INVALID_TOKEN;

    lexer->offset += *type == TOKEN_EOF ? 0 : len;
    return value;
}

struct lexer *lexer_create(char *input)
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

    char *cur = lexer_cursor(lexer);

    if (!lexer->single_quote && *cur == '#')
        cur = skip_comment(lexer);

    enum token_type type;
    char *value = lexer_read(lexer, cur, &type);

    if (type == TOKEN_WORD)
        type = token_word_type(value);
    lexer->current = token_create(type, value);
    return lexer->current;
}

struct token *lexer_peek(struct lexer *lexer)
{
    return lexer->current;
}

char *lexer_cursor(struct lexer *lexer)
{
    return lexer->input + lexer->offset;
}

void lexer_free(struct lexer *lexer)
{
    if (!lexer)
        return;
    token_free(lexer->current);
    free(lexer);
}
