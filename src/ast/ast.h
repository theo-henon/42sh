/**
** @file ast.h
** @brief Provide a definition of the base of each node of the AST,
** and functions to create AST, pretty print it, and free it.
** @date 2024-01-23
*/

#ifndef AST_H
#define AST_H

/**
** \enum ast_type
** @brief Enumerate all types of AST.
**
*/
enum ast_type
{
    LIST = 0,
    AND_OR,
    PIPELINE,
    SIMPLE_CMD,
    IF_CLAUSE
};

/**
** \struct base
** \brief Represents the base of all AST node.
**
** \var base::body
** The type of the AST node.
**
** It's useful to cast any types of AST nodes in this structure.
** Must be the first field of each AST nodes structure.
*/
struct base
{
    enum ast_type type;
};

/**
** @brief Represents the whole AST.
**
** ** \var ast::root
** The root of the AST.
*/
struct ast
{
    struct base *root;
};

/**
** @brief Create a new AST with provided root.
**
** @param root A pointer to the root node of the AST. Must not be NULL.
** @return A pointer to a new AST with its field 'root' filled by 'root' arg, or
** NULL if allocation failed.
*/
struct ast *ast_create(struct base *root);

/**
** @brief Release all memory held by any node of the AST.
**
** Must check the 'type' field and call the corresponding function to free the
** node.
**
** @param base A pointer to a node of the AST. If NULL, do nothing.
*/
void base_free(struct base *base);

/**
** @brief Release all memory held by the AST.
**
** Call 'base_free' with the root of the AST. and free the 'ast' structure.
**
** @param ast A pointer to the AST. If NULL, do nothing.
*/
void ast_free(struct ast *ast);

/**
** @brief Print any types of node of the AST.
**
** Must check the node type and call the appropriate function to print it.
**
** @param base A pointer to a node of the AST. Must not be NULL.
*/
void base_print(const struct base *base);

#endif /* ! AST_H */
