#ifndef WHILE_H
#define WHILE_H

#include "ast.h"
#include "list.h"

struct while_clause
{
    struct base base;
    struct list *condition;
    struct list *body;
};

struct while_clause *while_clause_create(struct list *condition,
                                         struct list *body);

void while_clause_free(struct while_clause *while_clause);

#endif /* ! WHILE_H */
