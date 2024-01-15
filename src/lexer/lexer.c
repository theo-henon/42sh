#include "lexer.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "token.h"

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

enum token_type search_token_type(const char *token)
{
    if (strcmp(token, "if") == 0)
        return TOKEN_IF;
    else if (strcmp(token, "fi") == 0)
        return TOKEN_FI;
    else if (strcmp(token, "else") == 0)
        return TOKEN_ELSE;
    else if (strcmp(token, "then") == 0)
        return TOKEN_THEN;
    else if (strcmp(token, "elif") == 0)
        return TOKEN_ELIF;
    else
        return TOKEN_WORD;
}

static void skip_whitespaces(struct lexer *lexer)
{
    while (isblank(lexer->input[lexer->offset]))
        lexer->offset++;
}

static void skip_commentary(struct lexer *lexer)
{
    while (lexer->input[lexer->offset] != '\0'
           && lexer->input[lexer->offset] != '\n')
        lexer->offset++;
}

static struct token *read_cmd_separator(struct lexer *lexer)
{
    char c = lexer->input[lexer->offset];
    lexer->current =
        token_create(c == '\n' ? TOKEN_EOL : TOKEN_SEMICOLON, NULL);
    lexer->offset++;
    return lexer->current;
}

struct token *lexer_pop(struct lexer *lexer)
{
    if (!lexer)
        return NULL;
    token_free(lexer->current);
    size_t len = 0;
    char c = lexer->input[lexer->offset];
    if (c == '\0')
        return NULL;

    skip_whitespaces(lexer);
    if (c == '#')
        skip_commentary(lexer);
    if (c == '\n' || c == ';')
        return read_cmd_separator(lexer);

    while (c != '\0')
    {
        if (c == '\n' || c == ';' || isblank(c))
            break;

        len++;
        lexer->offset++;
        c = lexer->input[lexer->offset];
    }

    lexer->offset -= len;
    char *new_token = strndup(lexer->input + lexer->offset, len);
    lexer->offset += len;
    lexer->current = token_create(search_token_type(new_token), new_token);
    return lexer->current;
}

void lexer_free(struct lexer *lexer)
{
    if (!lexer)
        return;
    free(lexer);
}
