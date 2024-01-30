#include "visitor.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "and_or_visitor.h"
#include "if_visitor.h"
#include "list_visitor.h"
#include "pipeline_visitor.h"
#include "simple_cmd_visitor.h"
#include "until_visitor.h"
#include "while_visitor.h"

struct visitor *visitor_init(void)
{
    errno = 0;
    struct visitor *visitor = calloc(1, sizeof(struct visitor));
    if (visitor != NULL)
    {
        visitor->base_visit = base_visit;
        visitor->list_visit = list_visit;
        visitor->and_or_visit = and_or_visit;
        visitor->pipeline_visit = pipeline_visit;
        visitor->simple_cmd_visit = simple_cmd_visit;
        visitor->if_visit = if_visit;
        visitor->while_visit = while_visit;
        visitor->until_visit = until_visit;
    }
    else
        perror("Cannot create visitor");
    return visitor;
}

void visitor_free(struct visitor *visitor)
{
    if (visitor != NULL)
        free(visitor);
}

int base_visit(struct visitor *visitor, struct base *base)
{
    switch (base->type)
    {
    case LIST:
        return visitor->list_visit(visitor, (struct list *)base);
    case AND_OR:
        return visitor->and_or_visit(visitor, (struct and_or *)base);
    case PIPELINE:
        return visitor->pipeline_visit(visitor, (struct pipeline *)base);
    case SIMPLE_CMD:
        return visitor->simple_cmd_visit(visitor, (struct simple_cmd *)base);
    case IF_CLAUSE:
        return visitor->if_visit(visitor, (struct if_clause *)base);
    case WHILE_CLAUSE:
        return visitor->while_visit(visitor, (struct while_clause *)base);
    case UNTIL_CLAUSE:
        return visitor->until_visit(visitor, (struct until_clause *)base);
    default:
        return 2;
    }
}
