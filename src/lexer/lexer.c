#include "lexer.h"

#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "token.h"
#include "utils/strbuilder.h"

static struct string *lexer_lex_squote(struct lexer *lexer, char first)
{
    struct string *quoted = string_create();
    string_catbuf(quoted, &first, 1);

    char c = input_readchar(lexer->input);
    while (c != '\0' && c != '\'')
    {
        string_catbuf(quoted, &c, 1);
        c = input_readchar(lexer->input);
    }

    if (c == '\0')
    {
        lexer->status = LEXER_UNEXPECTED_EOF;
        free(quoted);
        return NULL;
    }
    return quoted;
}

static struct string *lexer_lex_word(struct lexer *lexer, char first)
{
    struct string *word = string_create();
    string_catbuf(word, &first, 1);

    char c = input_readchar(lexer->input);
    while (!istoken(c) && !isblank(c))
    {
        if (c == '\'')
        {
            struct string *quoted = lexer_lex_squote(lexer, c);
            if (quoted == NULL)
            {
                free(word);
                return NULL;
            }
            string_catbuf(word, quoted->buf, quoted->size);
            string_free(quoted);
        }
        else
            string_catbuf(word, &c, 1);

        c = input_readchar(lexer->input);
    }
    lexer->input->offset--;
    return word;
}

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
    case '\'':
        type = TOKEN_WORD;
        value = lexer_lex_squote(lexer, first);
        break;
    default:
        type = TOKEN_WORD;
        value = lexer_lex_word(lexer, first);
        break;
    }

    if (lexer->status == LEXER_UNEXPECTED_EOF)
        return NULL;

    if (value != NULL)
        lexer->current = token_create(type, string_tobuf(value));
    else
        lexer->current = token_create(type, strndup(&first, 1));

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
