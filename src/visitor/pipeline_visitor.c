#include "pipeline_visitor.h"

int pipeline_visit(struct visitor *visitor, struct pipeline *pipeline)
{
    return visitor->base_visit(visitor, pipeline->cmd);
}
