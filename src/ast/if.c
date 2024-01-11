#include "if.h"

#include <stdlib.h>

struct if_clause *create_if_clause(struct base *condition, struct base *then_body, struct base *else_body)
{
    struct if_clause *if_clause = calloc(1, sizeof(struct if_clause));
    if_clause->base.type = IF_CLAUSE;
    if_clause->condition = condition;
    if_clause->then_body = then_body;
    if_clause->else_body = else_body;
    return if_clause;
}

void free_if_clause(struct if_clause *if_clause)
{
    free_base(condition);
    free_base(then_body);
    free_base(else_body);
    free(if_clause);
}