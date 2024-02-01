#ifndef UNTIL_H
#define UNTIL_H

#include "ast.h"
#include "list.h"

struct until_clause
{
    struct base base;
    struct list *condition;
    struct list *body;
};

struct until_clause *until_clause_create(struct list *condition,
                                         struct list *body);

void until_clause_free(struct until_clause *while_clause);

#endif /* ! UNTIL_H */
