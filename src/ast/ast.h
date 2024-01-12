#ifndef AST_H
#define AST_H

enum ast_type
{
    SIMPLE_CMD,
    LIST,
    IF_CLAUSE
};

struct base
{
    enum ast_type type;
};

struct ast
{
    struct base *root;
};

void free_base(struct base *base);

#endif /* ! AST_H */