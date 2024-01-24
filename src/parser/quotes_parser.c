#include "quotes_parser.h"

#include <stdlib.h>
#include <string.h>

struct token *parse_single_quotes(struct parser *parser)
{
    char *quotes = NULL;
    size_t size = 0;
    parser->lexer->single_quote = true;
    struct token *token = lexer_pop(parser->lexer);
    while (token->type != TOKEN_EOF && token->type != TOKEN_SINGLEQUOTE)
    {
        size_t tmp = size;
        size_t len = strlen(token->value);
        size += len + 1;
        quotes = realloc(quotes, size * sizeof(char));
        strncpy(quotes + tmp, token->value, len + 1);
        token = lexer_pop(parser->lexer);
    }

    if (token->type == TOKEN_EOF)
    {
        free(quotes);
        parser->status = PARSER_UNEXPECTED_TOKEN;
        return NULL;
    }

    parser->lexer->single_quote = false;
    return token_create(TOKEN_WORD,
                        size == 0 ? calloc(1, sizeof(char)) : quotes);
}

struct token *single_quotes_value(struct parser *parser)
{
    struct token *quoted = parse_single_quotes(parser);
    if (quoted != NULL)
    {
        token_free(parser->lexer->current);
        parser->lexer->current = quoted;
    }
    return quoted;
}
