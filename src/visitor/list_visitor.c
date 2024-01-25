#include "list_visitor.h"

#include <stddef.h>

#include "and_or_visitor.h"

int list_visit(struct visitor *visitor, struct list *list)
{
    int rtn_code = 0;
    while (list != NULL)
    {
        rtn_code = and_or_visit(visitor, list->and_or);
        list = list->next;
    }
    return rtn_code;
}
