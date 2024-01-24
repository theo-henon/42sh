#include "pipeline_parser.h"

#include "cmd_parser.h"
#include "lexer/lexer.h"
#include "ast/simple_cmd.h"

#include <stddef.h>


struct pipeline *parse_pipeline(struct parser *parser)
{

    struct base *cmd = parse_cmd(parser);
    if (!cmd)
        return NULL;
    struct pipeline *pipe = pipeline_create(cmd);
    return pipe;
}
