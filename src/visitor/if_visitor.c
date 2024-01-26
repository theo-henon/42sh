#include "if_visitor.h"

#include <stddef.h>

int if_visit(struct visitor *visitor, struct if_clause *if_clause)
{
    if (visitor->list_visit(visitor, if_clause->condition) == 0)
    {
        return visitor->list_visit(visitor, if_clause->body);
    }
    else
    {
        struct else_clause *tmp = if_clause->else_clauses;
        while (tmp != NULL)
        {
            if (tmp->condition == NULL)
                return visitor->list_visit(visitor, tmp->body);
            else if (visitor->list_visit(visitor, tmp->condition) == 0)
                return visitor->list_visit(visitor, tmp->body);
            else
                tmp = tmp->next;
        }
    }
    return 0;
}
