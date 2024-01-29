#ifndef PIPELINE_VISITOR_H
#define PIPELINE_VISITOR_H

#include "ast/pipeline.h"
#include "visitor.h"

int pipeline_visit(struct visitor *visitor, struct pipeline *pipeline);

#endif // PIPELINE_VISITOR_H
