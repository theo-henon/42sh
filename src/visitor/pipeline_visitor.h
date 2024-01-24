#ifndef PIPELINE_VISITOR
#define PIPELINE_VISITOR

#include "ast/pipeline.h"
#include "visitor.h"

int pipeline_visit(struct visitor *visitor, struct pipeline *pipeline);

#endif // PIPELINE_VISITOR
