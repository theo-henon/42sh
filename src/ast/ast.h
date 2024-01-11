#ifndef AST_H
#define AST_H



enum ast_type 
{
    SIMPLE_CMD,
    LIST,
    IF
};


struct base
{
    enum ast_type type;
};

struct ast
{
    struct base *root;
};



#endif /* ! AST_H */