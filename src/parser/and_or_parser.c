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
    struct and_or *node = NULL;
    while (token_isand_or(token))
    {
        struct pipeline *r_pipeline = parse_pipeline(parser);
        if (!r_pipeline)
        {
            pipeline_free(l_pipeline);
            return NULL;
        }

        if (root == NULL)
        {
            root = and_or_create_operator(token->type, l_pipeline, r_pipeline);
            node = root;
        }
        else
        {
            node =
                and_or_create_operator(token->type, node->pipeline, r_pipeline);
            free(node);
        }

        token = lexer_peek(parser->lexer);
    }

    return root == NULL ? and_or_create_pipeline(l_pipeline) : root;
}
