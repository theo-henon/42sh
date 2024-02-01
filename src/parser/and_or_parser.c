#include "and_or_parser.h"

#include <stdlib.h>

#include "pipeline_parser.h"

struct and_or *parse_and_or(struct parser *parser)
{
    struct pipeline *l_pipeline = parse_pipeline(parser);
    if (!l_pipeline)
        return NULL;

    struct token *token = lexer_peek(parser->lexer);
    struct and_or *root = NULL;
    while (token_isand_or(token))
    {
        enum token_type op = token->type;
        lexer_pop(parser->lexer);
        struct pipeline *r_pipeline = parse_pipeline(parser);
        if (!r_pipeline)
        {
            pipeline_free(l_pipeline);
            return NULL;
        }

        if (root == NULL)
            root =
                and_or_create_operator(op, and_or_create_pipeline(l_pipeline),
                                       and_or_create_pipeline(r_pipeline));
        else
            root = and_or_create_operator(op, root,
                                          and_or_create_pipeline(r_pipeline));

        token = lexer_peek(parser->lexer);
    }

    return root == NULL ? and_or_create_pipeline(l_pipeline) : root;
}
