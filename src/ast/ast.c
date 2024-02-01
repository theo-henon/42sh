#include "ast.h"

#include <stdio.h>
#include <stdlib.h>

#include "if.h"
#include "list.h"
#include "simple_cmd.h"
#include "until.h"
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
        break;
    case UNTIL_CLAUSE:
        until_clause_free((struct until_clause *)base);
        break;
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
