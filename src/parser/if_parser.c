#include "if_parser.h"

#include "list_parser.h"

struct if_clause *parse_if_clause(struct parser *parser)
{
    struct list *condition = parse_compound_list(parser);
    struct token *token = lexer_peek(parser->lexer);

    if (token->type != TOKEN_THEN || !condition)
    {
        parser->status = PARSER_UNEXPECTED_TOKEN;
        list_free(condition);
        return NULL;
    }
    token = lexer_pop(parser->lexer);

    struct list *body = parse_compound_list(parser);
    token = lexer_peek(parser->lexer);

    if (token->type == TOKEN_ELSE && body != NULL)
    {
        struct else_clause *else_clause =
            else_clause_create(NULL, parse_compound_list(parser));
        return if_clause_create(condition, body, else_clause);
    }
    else if (token->type == TOKEN_ELIF)
    {
        // TODO : case elif
    }
    else
    {
        parser->status = PARSER_UNEXPECTED_TOKEN;
        list_free(condition);
        list_free(body);
        return NULL;
    }
    return NULL;
}
