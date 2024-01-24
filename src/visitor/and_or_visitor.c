#include "and_or_visitor.h"

int and_or_visit(struct visitor *visitor, struct and_or *and_or)
{
    return visitor->pipeline_visit(visitor, and_or->pipeline);
}
