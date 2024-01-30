#include "if_parser.h"

#include "list_parser.h"

struct else_clause *parse_elif_clause(struct parser *parser)
{
    struct list *condition = parse_compound_list(parser);
    struct token *token = lexer_peek(parser->lexer);
    while (token->type == TOKEN_EOL)
        token = lexer_pop(parser->lexer);

    if (condition == NULL || token->type != TOKEN_THEN)
    {
        fprintf(stderr, "conditon null or not then for if\n");
        parser->status = PARSER_UNEXPECTED_TOKEN;
        list_free(condition);
        return NULL;
    }
    struct list *body = parse_compound_list(parser);
    struct else_clause *else_clause = else_clause_create(condition, body);
    token = lexer_peek(parser->lexer);
    while (token->type == TOKEN_EOL)
        token = lexer_pop(parser->lexer);

    while (token->type == TOKEN_ELIF)
    {
        condition = parse_compound_list(parser);
        token = lexer_peek(parser->lexer);
        if (condition == NULL || token->type != TOKEN_THEN)
        {
            fprintf(stderr, "conditon null or not then for if\n");
            parser->status = PARSER_UNEXPECTED_TOKEN;
            else_clause_free(else_clause);
            return NULL;
        }
        body = parse_compound_list(parser);
        token = lexer_peek(parser->lexer);
        if (body == NULL)
        {
            fprintf(stderr, "body null\n");
            parser->status = PARSER_UNEXPECTED_TOKEN;
            else_clause_free(else_clause);
            list_free(condition);
            return NULL;
        }
        else_clause_append(else_clause, condition, body);
    }
    if (token->type == TOKEN_ELSE)
    {
        else_clause_append(else_clause, NULL, parse_compound_list(parser));
    }
    if (parser->lexer->current->type == TOKEN_FI)
    {
        token = lexer_pop(parser->lexer);
        return else_clause;
    }
    fprintf(stderr, "not fi\n");
    parser->status = PARSER_UNEXPECTED_TOKEN;
    else_clause_free(else_clause);
    return NULL;
}

struct if_clause *parse_if_clause(struct parser *parser)
{
    struct list *condition = parse_compound_list(parser);
    struct token *token = lexer_peek(parser->lexer);

    while (token->type == TOKEN_EOL)
        token = lexer_pop(parser->lexer);

    if (token->type != TOKEN_THEN || !condition)
    {
        fprintf(stderr, "condition null or not then\n");
        parser->status = PARSER_UNEXPECTED_TOKEN;
        list_free(condition);
        return NULL;
    }

    lexer_peek(parser->lexer);
    struct list *body = parse_compound_list(parser);
    token = lexer_peek(parser->lexer);

    while (token->type == TOKEN_EOL)
        token = lexer_pop(parser->lexer);

    if (token->type == TOKEN_ELSE && body != NULL)
    {
        struct else_clause *else_clause =
            else_clause_create(NULL, parse_compound_list(parser));
        token = lexer_peek(parser->lexer);
        if (token->type != TOKEN_FI)
        {
            fprintf(stderr, "not fi\n");
            parser->status = PARSER_UNEXPECTED_TOKEN;
            else_clause_free(else_clause);
            return NULL;
        }
        token = lexer_pop(parser->lexer);
        return if_clause_create(condition, body, else_clause);
    }
    else if (token->type == TOKEN_ELIF)
    {
        return if_clause_create(condition, body, parse_elif_clause(parser));
    }
    else if (token->type == TOKEN_FI)
    {
        token = lexer_pop(parser->lexer);
        return if_clause_create(condition, body, NULL);
    }
    else
    {
        fprintf(stderr, "not fi\n");
        parser->status = PARSER_UNEXPECTED_TOKEN;
        list_free(condition);
        list_free(body);
    }
    return NULL;
}
