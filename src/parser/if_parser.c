#include "if_parser.h"

#include "list_parser.h"

struct else_clause *parse_elif_clause(struct parser *parser)
{
    struct token *token = lexer_peek(parser->lexer);
    token = lexer_pop(parser->lexer);
    struct list *condition = parse_compound_list(parser);
    token = lexer_peek(parser->lexer);
    if (condition == NULL || token->type != TOKEN_THEN)
    {
        parser->status = PARSER_UNEXPECTED_TOKEN;
        list_free(condition);
        return NULL;
    }
    struct list *body = parse_compound_list(parser);
    struct else_clause *else_clause = else_clause_create(condition, body);
    token = lexer_peek(parser->lexer);
    struct else_clause *tmp = else_clause->next;
    while (token->type == TOKEN_ELIF)
    {
        token = lexer_pop(parser->lexer);
        condition = parse_compound_list(parser);
        token = lexer_peek(parser->lexer);
        if (condition == NULL || token->type != TOKEN_THEN)
        {
            parser->status = PARSER_UNEXPECTED_TOKEN;
            else_clause_free(else_clause);
            return NULL;
        }
        token = lexer_pop(parser->lexer);
        body = parse_compound_list(parser);
        token = lexer_peek(parser->lexer);
        if (body == NULL)
        {
            parser->status = PARSER_UNEXPECTED_TOKEN;
            else_clause_free(else_clause);
            list_free(condition);
            return NULL;
        }
        tmp->next = else_clause_create(condition, body);
        tmp = tmp->next;
    }
    if (token->type == TOKEN_ELSE)
    {
        tmp->next = else_clause_create(NULL, parse_compound_list(parser));
    }
    token = lexer_peek(parser->lexer);
    if (token->type == TOKEN_FI)
    {
        token = lexer_pop(parser->lexer);
        return else_clause;
    }
    parser->status = PARSER_UNEXPECTED_TOKEN;
    else_clause_free(else_clause);
    return NULL;
}

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
        if (token->type != TOKEN_FI)
        {
            parser->status = PARSER_UNEXPECTED_TOKEN;
            else_clause_free(else_clause);
            return NULL;
        }
        return if_clause_create(condition, body, else_clause);
    }
    else if (token->type == TOKEN_ELIF)
    {
        return if_clause_create(condition, body, parse_elif_clause(parser));
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
