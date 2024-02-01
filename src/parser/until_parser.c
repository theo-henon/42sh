#include "until_parser.h"

#include "list_parser.h"

struct until_clause *parse_until_clause(struct parser *parser)
{
    struct list *condition = parse_compound_list(parser);
    struct token *token = lexer_peek(parser->lexer);
    while (token->type == TOKEN_EOL)
        token = lexer_pop(parser->lexer);
    if (token->type != TOKEN_DO || !condition)
    {
        fprintf(stderr, "condition null or no do\n");
        parser->status = PARSER_UNEXPECTED_TOKEN;
        list_free(condition);
        return NULL;
    }

    lexer_peek(parser->lexer);
    struct list *body = parse_compound_list(parser);
    token = lexer_peek(parser->lexer);
    if (token->type != TOKEN_DONE || !body)
    {
        fprintf(stderr, "body null or not done");
        parser->status = PARSER_UNEXPECTED_TOKEN;
        list_free(condition);
        list_free(body);
        return NULL;
    }
    token = lexer_pop(parser->lexer);
    return until_clause_create(condition, body);
}
