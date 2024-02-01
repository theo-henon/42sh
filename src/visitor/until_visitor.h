#ifndef UNTIL_VISITOR_H
#define UNTIL_VISITOR_H

#include "ast/until.h"
#include "visitor.h"

int until_visit(struct visitor *visitor, struct until_clause *until_clause);

#endif /* ! UNTIL_VISITOR_H */
