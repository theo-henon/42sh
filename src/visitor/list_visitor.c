#include "list_visitor.h"

#include "and_or_visitor.h"

int list_visit(struct visitor *visitor, struct list *list)
{
    return and_or_visit(visitor, list->and_or);
}
