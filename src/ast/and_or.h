/**
** \file and_or.h
** \brief Provide a definition of an 'and_or' struct and functions to create,
** print and free it
** \date 2024-01-21
*/

#ifndef AND_OR_H
#define AND_OR_H

#include "ast.h"
#include "lexer/token.h"
#include "pipeline.h"

/**
** \struct and_or
** \brief Represent an 'and_or' node in the AST, which is a binary tree.
**
** This structure corresponds to this rule of the grammar in the SCL :
** \code
** and_or = pipeline { ( '&&' | '||' ) {'\n'} pipeline } ;
** \endcode
**
** \note An 'and_or' node can contains either a 'pipeline or an operator.
** An 'and_or' node with a NULL 'pipeline' field represents an operator.
** If the 'pipeline' field is not NULL, the 'and_or' node is considered as a
** pipeline.
**
** \see SCL grammar rules: http://tinyurl.com/2wc4jera
**
** \var and_or::base
** The base of all AST nodes.
**
** \var and_or::pipeline
** The pipeline contained in the node. Can be NULL
**
** \var and_or::operator
** The operator between two 'pipeline' nodes in the input.
** Its value can be TOKEN_AND or TOKEN_OR.
**
** \var and_or::left
** The left child 'and_or' node. Can be NULL.
**
** \var and_or::right
** The right child 'and_or' node. Can be NULL.
*/
struct and_or
{
    struct base base;
    struct pipeline *pipeline;
    enum token_type operator;
    struct and_or *left;
    struct and_or *right;
};

/**
** \brief Create an 'and_or' node that stores a 'pipeline' node
**
** \param pipeline A pointer to the pipeline you want to put in the new node.
** \return A pointer to a new 'and_or' node with its 'pipeline' field filled
** with 'pipeline' argument.
*/
struct and_or *and_or_create_pipeline(struct pipeline *pipeline);

/**
** \brief Create an 'and_or' node that stores an operator
**
** \param operator The type of the operator you want to put in the new node.
** Must be either equals to TOKEN_OR or TOKEN_AND.
** \return A pointer to a new 'and_or' node with its 'operator' field filled
** with 'operator' argument.
*/
struct and_or *and_or_create_operator(enum token_type operator);

#ifdef PRETTY_PRINT
/**
** \brief Print the entire 'and_or' binary tree using an in-order traversal.
**
** Browse the 'and_or' binary tree using an in-order traversal and for each
** node :
** - If 'pipeline' field is not NULL, call 'pipeline_print'
** - Else print the 'operator' field ('&&' for TOKEN_AND, '||' for TOKEN_OR).
**
** \param and_or A pointer to the 'and_or' node you want to print
*/
void and_or_print(const struct and_or *and_or);
#endif // PRETTY_PRINT

/**
** \brief Release all memory held by the 'and_or' binary tree.
**
** Browse the entire tree, and for each node, call 'pipeline_free' and free
*it.
**
** \param and_or A pointer to the 'and_or' root node you want to free. If
** 'and_or' argument is NULL, do nothing.
*/
void and_or_free(struct and_or *and_or);

#endif /* ! AND_OR_H */
