#include "until.h"

#include <stdlib.h>

struct until_clause *until_clause_create(struct list *condition,
                                         struct list *body)
{
    struct until_clause *while_clause = calloc(1, sizeof(struct until_clause));
    while_clause->condition = condition;
    while_clause->body = body;
    while_clause->base.type = UNTIL_CLAUSE;
    return while_clause;
}

void until_clause_free(struct until_clause *while_clause)
{
    list_free(while_clause->condition);
    list_free(while_clause->body);
    free(while_clause);
}
