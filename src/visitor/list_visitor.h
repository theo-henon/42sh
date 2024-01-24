#ifndef LIST_VISITOR_H
#define LIST_VISITOR_H

#include "ast/list.h"
#include "visitor.h"

int list_visit(struct visitor *visitor, struct list *list);

#endif // LIST_VISITOR_H
