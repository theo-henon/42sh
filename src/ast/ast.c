#include "ast.h"

#include <stdio.h>

#include "if.h"
#include "list.h"
#include "simple_cmd.h"

void free_base(struct base *base)
{
    switch (base->type)
    {
    case SIMPLE_CMD:
        free_simple_cmd((struct simple_cmd *)base);
        break;
    case LIST:
        free_list((struct list *)base);
        break;
    case IF_CLAUSE:
        free_if_clause((struct if_clause *)base);
        break;
    default:
        fprintf(stderr, "Fail to free error type !\n");
        break;
    }
}