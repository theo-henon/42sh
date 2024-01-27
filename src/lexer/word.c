#include "word.h"

#include <ctype.h>
#include <stdlib.h>

struct string *single_quote_lex(struct lexer *lexer, char first)
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
        string_free(quoted);
        return NULL;
    }
    return quoted;
}

int word_append(struct lexer *lexer, struct string *word, char c)
{
    if (c == '\'')
    {
        struct string *quoted = single_quote_lex(lexer, c);
        if (quoted == NULL)
        {
            string_free(word);
            return 1;
        }
        string_catbuf(word, quoted->buf, quoted->size);
        string_free(quoted);
    }
    else
        string_catbuf(word, &c, 1);
    return 0;
}

struct string *word_lex(struct lexer *lexer, char first)
{
    struct string *word = string_create();
    if (word_append(lexer, word, first) == 1)
        return NULL;

    char c = input_readchar(lexer->input);
    while (!istoken(c) && !isblank(c))
    {
        if (word_append(lexer, word, c) == 1)
            return NULL;
        c = input_readchar(lexer->input);
    }
    lexer->input->offset--;
    return word;
}
