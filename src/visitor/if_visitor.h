#ifndef IF_VISITOR_H
#define IF_VISITOR_H

#include "ast/if.h"
#include "visitor.h"

int if_visit(struct visitor *visitor, struct if_clause *if_clause);

#endif /* ! IF_VISITOR_H */
