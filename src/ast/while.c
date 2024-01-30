#include "while.h"

#include <stdlib.h>

struct while_clause *while_clause_create(struct list *condition,
                                         struct list *body)
{
    struct while_clause *while_clause = calloc(1, sizeof(struct while_clause));
    while_clause->condition = condition;
    while_clause->body = body;
    while_clause->base.type = WHILE_CLAUSE;
    return while_clause;
}

void while_clause_free(struct while_clause *while_clause)
{
    list_free(while_clause->condition);
    list_free(while_clause->body);
    free(while_clause);
}
