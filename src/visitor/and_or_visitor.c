#include "and_or_visitor.h"

#include <stddef.h>

int and_or_visit(struct visitor *visitor, struct and_or *and_or)
{
    if (and_or->pipeline != NULL)
        return visitor->pipeline_visit(visitor, and_or->pipeline);
    else if (and_or->op == TOKEN_AND)
        return !(visitor->pipeline_visit(visitor, and_or->left->pipeline)
                 && visitor->pipeline_visit(visitor, and_or->right->pipeline));
    else
    {
        int code = visitor->pipeline_visit(visitor, and_or->left->pipeline);
        if (code == 0)
            return code;
        else
            return !(
                code
                || visitor->pipeline_visit(visitor, and_or->right->pipeline));
    }
}
