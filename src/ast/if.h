#ifndef IF_H
#define IF_H

#include "ast.h"

struct if_clause 
{
    struct base base;
    struct base *condition;
    struct base *then_body;
    struct if_clause **elif_body;
    struct base *else_body;
};


struct if_clause *create_if_clause(struct base *condition, struct base *then_body, struct base *else_body);
void free_if_clause(struct if_clause *if_clause);

#endif /* ! IF_H */