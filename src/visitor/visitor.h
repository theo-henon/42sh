#ifndef VISITOR_H
#define VISITOR_H

#include "ast/and_or.h"
#include "ast/ast.h"
#include "ast/if.h"
#include "ast/list.h"
#include "ast/pipeline.h"
#include "ast/simple_cmd.h"
#include "ast/until.h"
#include "ast/while.h"

struct visitor
{
    int (*base_visit)(struct visitor *visitor, struct base *base);
    int (*list_visit)(struct visitor *visitor, struct list *list);
    int (*and_or_visit)(struct visitor *visitor, struct and_or *and_or);
    int (*pipeline_visit)(struct visitor *visitor, struct pipeline *pipeline);
    int (*simple_cmd_visit)(struct visitor *visitor, struct simple_cmd *cmd);
    int (*if_visit)(struct visitor *visitor, struct if_clause *if_clause);
    int (*while_visit)(struct visitor *visitor,
                       struct while_clause *while_clause);
    int (*until_visit)(struct visitor *visitor,
                       struct until_clause *until_clause);
};

struct visitor *visitor_init(void);
void visitor_free(struct visitor *visitor);
int base_visit(struct visitor *visitor, struct base *base);

#endif // VISITOR_H
