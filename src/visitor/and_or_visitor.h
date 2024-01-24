#ifndef AND_OR_VISITOR_H
#define AND_OR_VISITOR_H

#include "ast/and_or.h"
#include "visitor.h"

int and_visit(struct visitor *visitor, struct and_or *and_or);
int or_visit(struct visitor *visitor, struct and_or *and_or);
int and_or_visit(struct visitor *visitor, struct and_or *and_or);

#endif // AND_OR_VISITOR_H
