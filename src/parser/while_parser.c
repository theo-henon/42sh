#include "while_parser.h"

#include "list_parser.h"

struct while_clause *while_clause_parser(struct parser *parser)
{
    struct list *condition = parse_compound_list(parser);
    struct token *token = lexer_peek(parser->lexer);
    while (token->type == TOKEN_EOL)
        token = lexer_pop(parser->lexer);
    if (token->type != TOKEN_DO || !condition)
    {
        parser->status = PARSER_UNEXPECTED_TOKEN;
        list_free(condition);
        return NULL;
    }

    lexer_peek(parser->lexer);
    struct list *body = parse_compound_list(parser);
    if (token->type != TOKEN_DONE || !body)
    {
        parser->status = PARSER_UNEXPECTED_TOKEN;
        list_free(condition);
        list_free(body);
        return NULL;
    }
    return while_clause_create(condition, body);
}
