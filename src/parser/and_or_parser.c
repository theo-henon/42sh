#include "and_or_parser.h"

#include "pipeline_parser.h"
#include <stddef.h>

struct and_or *parse_and_or(struct parser *parser)
{
    struct pipeline *pipeline = parse_pipeline(parser);
    if (!pipeline)
        return NULL;
    return and_or_create_pipeline(pipeline);
}