#include "ast.h"

#include <stdio.h>
#include <stdlib.h>

#include "if.h"
#include "list.h"
#include "simple_cmd.h"
#include "while.h"

struct ast *ast_create(struct base *root)
{
    struct ast *ast = calloc(1, sizeof(struct ast));
    if (ast != NULL)
        ast->root = root;
    return ast;
}

void base_free(struct base *base)
{
    switch (base->type)
    {
    case LIST:
        list_free((struct list *)base);
        break;
    case AND_OR:
        and_or_free((struct and_or *)base);
        break;
    case PIPELINE:
        pipeline_free((struct pipeline *)base);
        break;
    case SIMPLE_CMD:
        simple_cmd_free((struct simple_cmd *)base);
        break;
    case IF_CLAUSE:
        if_clause_free((struct if_clause *)base);
        break;
    case WHILE_CLAUSE:
        while_clause_free((struct while_clause *)base);
    default:
        break;
    }
}

void ast_free(struct ast *ast)
{
    if (ast == NULL)
        return;
    base_free(ast->root);
    free(ast);
}

#ifdef PRETTY_PRINT
void base_print(const struct base *base)
{
    switch (base->type)
    {
    case LIST:
        list_print((struct list *)base);
        break;
    case AND_OR:
        and_or_print((struct and_or *)base);
        break;
    case PIPELINE:
        pipeline_print((struct pipeline *)base);
        break;
    case SIMPLE_CMD:
        simple_cmd_print((struct simple_cmd *)base);
        break;
    case IF_CLAUSE:
        if_clause_print((struct if_clause *)base);
    default:
        return;
    }
}
#endif // PRETTY_PRINT
