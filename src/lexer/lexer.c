#include "lexer.h"

#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "token.h"

static char *lexer_lex_squote(struct lexer *lexer, char first)
{
    size_t len = 1;
    char *quoted = calloc(len, sizeof(char));
    quoted[len - 1] = first;
    char c = input_readchar(lexer->input);
    while (c != '\0' && c != '\'')
    {
        len++;
        quoted = realloc(quoted, len * sizeof(char));
        quoted[len - 1] = c;
        c = input_readchar(lexer->input);
    }

    if (c == '\0')
    {
        lexer->status = LEXER_UNEXPECTED_EOF;
        free(quoted);
        return NULL;
    }
    len += 2;
    quoted = realloc(quoted, len * sizeof(char));
    quoted[len - 2] = c;
    quoted[len - 1] = '\0';
    return quoted;
}

static char *lexer_lex_word(struct lexer *lexer, char first)
{
    size_t len = 1;
    char *word = calloc(len, sizeof(char));
    word[len - 1] = first;

    char c = input_readchar(lexer->input);
    while (!istoken(c) && !isblank(c))
    {
        if (c == '\'')
        {
            char *quoted = lexer_lex_squote(lexer, c);
            if (quoted == NULL)
            {
                free(word);
                return NULL;
            }
            size_t quoted_len = strlen(quoted);
            len += quoted_len;
            word = realloc(word, len * sizeof(char));
            strncpy(word + len, quoted, quoted_len);
        }
        len++;
        word = realloc(word, len * sizeof(char));
        word[len - 1] = c;
        c = input_readchar(lexer->input);
    }

    len++;
    word = realloc(word, len * sizeof(char));
    word[len - 1] = '\0';
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
    char *value = NULL;
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
        lexer->current = token_create(type, value);
    else
        lexer->current = token_create(type, strndup(&first, 1));

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
