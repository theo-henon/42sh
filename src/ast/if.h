#ifndef IF_H
#define IF_H

#include "ast.h"

struct if_clause 
{
    struct base base;
    struct base *condition;
    struct base *then_body;
    struct base *else_body;
};

#endif /* ! IF_H */