#ifndef WHILE_VISITOR_H
#define WHILE_VISITOR_H

#include "ast/while.h"
#include "visitor.h"

int while_visit(struct visitor *visitor, struct while_clause *while_clause);

#endif /* ! WHILE_VISITOR_H */
