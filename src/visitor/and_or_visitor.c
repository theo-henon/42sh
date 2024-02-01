#include "and_or_visitor.h"

#include <stddef.h>

int and_or_visit(struct visitor *visitor, struct and_or *and_or)
{
    if (and_or->pipeline != NULL)
        return visitor->pipeline_visit(visitor, and_or->pipeline);
    else if (and_or->op == TOKEN_AND)
        return !(and_or_visit(visitor, and_or->left)
                 && and_or_visit(visitor, and_or->right));
    else
    {
        int code = and_or_visit(visitor, and_or->left);
        if (code == 0)
            return code;
        else
            return !(code || and_or_visit(visitor, and_or->right));
    }
}
