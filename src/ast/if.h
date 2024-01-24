/**
** \file if.h
** \brief Provide a definition of a 'if_clause' struct an 'else_clause' struct
** and functions to create, add clauses, print it, and free it.
** \date 2024-01-21
*/

#ifndef IF_H
#define IF_H

#include "ast.h"
#include "list.h"

/**
** \struct else_clause
** \brief Represent an 'else_clause' node in an 'if_clause' node in the AST.
**
** An 'else_clause' node is a linked list of 'elif' clauses possibily ending
** with a final 'else' clause. This constraint must be handled by the parser.
**
** This structure corresponds to this rule of the grammar in the SCL :
** \code
** else_clause = 'else' compound_list
**      | 'elif' compound_list 'then' compound_list [ else_clause ] ;
** \endcode
**
** \see SCL grammar rules: http://tinyurl.com/2wc4jera
**
**
** \var else_clause::condition
** A pointer to a 'compound_list' node The condition of an 'elif' clause.
** If it is NULL, it represents an 'else' clause.
**
** \var else_clause::body
** The body of the 'else_clause' node. Must not be NULL.
**
** \var else_clause::next
** The next 'else_clause' node. Can be NULL.
*/
struct else_clause
{
    struct list *condition;
    struct list *body;
    struct else_clause *next;
};

/**
** \struct if_clause
** \brief Represent an 'if_clause' node in the AST.
**
** An 'if_clause' node contains a 'condition' node, a 'body' node that is
** evaluated if the condition is 'true', and a list of 'else_clause' nodes
** that are evaluated if the condition is 'false'.
**
** This structure corresponds to this rule of the grammar in the SCL :
** \code
** rule_if = 'if' compound_list 'then' compound_list [ else_clause ] 'fi' ;
** \endcode
**
** \see SCL grammar rules: http://tinyurl.com/2wc4jera
**
** \var if_clause::condition
** A pointer to a 'compound_list' node that represents the condition of the
** 'if_clause' node. Must not be NULL.
**
** \var if_clause::body
** The body of the 'then' node. Must not be NULL.
**
** \var if_clause::else_clauses
** The list of 'else_clause' nodes of the 'if_clause' node. Can be NULL.
*/
struct if_clause
{
    struct base base;
    struct list *condition;
    struct list *body;
    struct else_clause *else_clauses;
};

/**
** \brief Create an 'else_clause' node with provided condition and body.
**
** \param condition A pointer to a 'compound_list' node. If it is NULL it
** creates an 'else' clause, otherwise creates an 'elif' clause with specified
** condition.
** \param body A pointer to a 'compound_list' node that represents the body
** evaluated if 'condition' node is evaluated true. Must not be NULL.
** \return A pointer to a new 'else_clause' node with its field 'condition' and
** 'body' filled by provided arguments.
*/
struct else_clause *else_clause_create(struct list *condition,
                                       struct list *body);

/**
** \brief Add a new 'else_clause' node at the end of the provided list of
** 'else_clause' nodes.
**
** \param else_clause A pointer to a list of 'else_clause' nodes. Must not be
*NULL.
** \param condition A pointer to a 'compound_list' node. If it is NULL it
** creates an 'else' clause, otherwise creates an 'elif' clause with specified
** condition.
** \param body A pointer to a 'compound_list' node that represents the body
** evaluated if 'condition' node is evaluated true. Must not be NULL.
*/
void else_clause_append(struct else_clause *else_clause, struct list *condition,
                        struct list *body);

/**
** \brief Print whole list of 'else_clause' nodes.
**
** Browse all 'else_clause' nodes, and for each prints either 'else' if
** 'condition' field is NULL or 'elif', then calls
** 'list_print' with its 'condition' field, followed by a line feed, then calls
** 'list_print' with its 'body' field, followed by another line feed.
**
** \param else_clause A pointer to a list of 'else_clause' nodes.
** Must not be NULL.
*/
void else_clause_print(const struct else_clause *else_clause);

/**
** \brief Release all memory held by the provided list of 'else_clause' nodes.
**
** Browse all 'else_clause' nodes, and for each, calls 'list_free' with its
** 'condition' and 'body' fields.
**
** \param else_clause A pointer to a list of 'else_clause' nodes.
** Must not be NULL.
*/
void else_clause_free(struct else_clause *else_clause);

/**
** \brief Create an 'if_clause' node with provided condition, body, and list of
** 'else_clause' nodes.
**
** \param condition A pointer to a 'compound_list' node that will be evaluated.
** Must not be NULL.
** \param body A pointer to a 'compound_list' node that will be evaluated only
** if 'condition' is evaluated true. Must not be NULL.
** \param else_clauses A pointer to a list of 'else_clause' nodes. Can be NULL.
** \return A pointer to a new 'if_clause' node with its fields 'condition',
** 'body', 'else_clauses' filled by arguments.
*/
struct if_clause *if_clause_create(struct list *condition, struct list *body,
                                   struct else_clause *else_clauses);

/**
** \brief Print an 'if_clause' node.
**
** Print 'if', followed by a single whitespace, then call 'list_print' with
** 'condition' field, followed by a line feed. Print 'then', followed by a
** linefeed, then call 'list_print' with 'body' field. If 'else_clauses' is not
** NULL, call 'else_clause_print' with 'else_clauses' field.
**
** \param if_clause A pointer to an 'if_clause' node. Must not be NULL.
*/
void if_clause_print(const struct if_clause *if_clause);

/**
 * @brief Release all memory held by an 'if_clause' node.
 *
 * Call 'list_free' with 'condition' and 'body' fields, then call
 * 'else_clause_free' with 'else_clauses' field
 *
 * @param if_clause A pointer to an 'if_clase' node. If NULL, do nothing.
 */
void if_clause_free(struct if_clause *if_clause);

#endif /* ! IF_H */
