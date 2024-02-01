#include "and_or_visitor.h"

#include <stddef.h>

int and_or_visit(struct visitor *visitor, struct and_or *and_or)
{
    if (and_or == NULL)
        return 0;
    else if (and_or->pipeline != NULL)
        return visitor->pipeline_visit(visitor, and_or->pipeline);
    else if (and_or->op == TOKEN_AND)
    {
        int first = and_or_visit(visitor, and_or->left);
        if (first != 0)
            return first;

        int second = and_or_visit(visitor, and_or->right);
        if (second != 0)
            return second;
        return 0;
    }
    else
    {
        int first = and_or_visit(visitor, and_or->left);
        if (first == 0)
            return 0;

        int second = and_or_visit(visitor, and_or->right);
        if (second != 0)
            return second;

        return first != 0 && second != 0;
    }
}
