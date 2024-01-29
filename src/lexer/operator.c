#include "operator.h"

#include <ctype.h>

struct string *operator_lex(struct lexer *lexer, char first,
                            enum token_type *type)
{
    struct string *op = string_create();
    string_catbuf(op, &first, 1);
    char second = input_readchar(lexer->input);
    if (first == second)
    {
        string_catbuf(op, &second, 1);
        *type = first == '&' ? TOKEN_AND : TOKEN_OR;
    }
    else
    {
        *type = TOKEN_WORD;
        lexer->input->offset--;
    }

    return op;
}

