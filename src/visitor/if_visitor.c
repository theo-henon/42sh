#include "if_visitor.h"

#include <stddef.h>

int if_visit(struct visitor *visitor, struct if_clause *if_clause)
{
    if (visitor->list_visit(visitor, if_clause->condition) == 0)
    {
        return visitor->list_visit(visitor, if_clause->body);
    }
    else
        return 0;
}
