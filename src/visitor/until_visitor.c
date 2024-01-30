#include "until_visitor.h"

int until_visit(struct visitor *visitor, struct until_clause *until_clause)
{
    int rtn_code;
    while (visitor->list_visit(visitor, until_clause->condition) != 0)
        rtn_code = visitor->list_visit(visitor, until_clause->body);
    return rtn_code;
}
