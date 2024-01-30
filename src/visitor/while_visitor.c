#include "while_visitor.h"

int while_visit(struct visitor *visitor, struct while_clause *while_clause)
{
    int rtn_code = 0;
    while (visitor->list_visit(visitor, while_clause->condition) == 0)
        rtn_code = visitor->list_visit(visitor, while_clause->body);
    return rtn_code;
}
