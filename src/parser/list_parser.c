#include "list_parser.h"

#include "and_or_parser.h"

struct list *parse_list(struct parser *parser)
{
    struct and_or *and_or = parse_and_or(parser);
    if (!and_or)
    {
        and_or_free(and_or);
        return NULL;
    }
    struct list *list = list_create(and_or);
    int tmp;
    struct token *token = parser->lexer->current;
    while (token_islist_delim(token))
    {
        tmp = token->type;
        token = lexer_pop(parser->lexer);
        and_or = parse_and_or(parser);
        if (!and_or)
        {
            and_or_free(and_or);
            break;
        }
        else
        {
            list_append(list, and_or, tmp);
            token = lexer_pop(parser->lexer);
        }
    }
    return list;
}

struct list *parse_compound_list(struct parser *parser);
