#include "ast.h"

#include "simple_cmd"
#include "list.h"
#include "if.h"

#include <stdio.h>



void free_base(struct base *base)
{
    switch (base.type)
    {
        case SIMPLE_CMD:
            free_simple_cmd(base);
            break;
        case LIST:
            free_list(base);
            break;
        case IF_CLAUSE:
            free_if_clause(base);
            break;
        default:
            fprintf(stderr, "Fail to free error type !\n");
            break;
    }
}