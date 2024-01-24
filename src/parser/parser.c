#include "parser.h"

#include <stdlib.h>

#include "list_parser.h"
#include "quotes_parser.h"

struct parser *parser_create(struct lexer *lexer)
{
    struct parser *parser = calloc(1, sizeof(struct parser));
    if (parser != NULL)
        parser->lexer = lexer;
    return parser;
}

struct ast *parse_input(struct parser *parser)
{
    struct token *token = lexer_pop(parser->lexer);
    if (token == NULL)
        return NULL;

    while (token->type == TOKEN_EOL)
        token = lexer_pop(parser->lexer);

    if (token->type == TOKEN_SINGLEQUOTE)
        single_quotes_value(parser);
    
    struct ast *ast = NULL;
    struct list *list = parse_list(parser);
    if (list != NULL)
        ast = ast_create((struct base *)list);

    token = lexer_peek(parser->lexer);
    if (token->type != TOKEN_EOL && token->type != TOKEN_EOF)
    {
        ast_free(ast);
        ast = NULL;
    }
    return ast;
}
