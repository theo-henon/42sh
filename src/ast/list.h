/**
** \file list.h
** \brief Provide a definition of a 'list' struct and functions to create, add
** and print elements, and free it.
** \date 2024-01-21
*/

#ifndef LIST_H
#define LIST_H

#include "and_or.h"
#include "ast.h"
#include "lexer/token.h"

/**
** \struct list
** \brief Represent a 'list' node in the AST.
**
** This structure corresponds to this rule of the grammar in the SCL :
** \code
** list = and_or { ( ';' | '&' ) and_or } [ ';' | '&' ] ;
** \endcode
**
** \note An empty 'list' (if it is NULL or 'first' field is NULL ) is invalid.
**
** \see SCL grammar rules: http://tinyurl.com/2wc4jera
**
** \var list::base
** The base of all AST nodes.
**
** \var list::and_or
** The 'and_or' node stored in the 'list' node. Can be NULL.
**
** \var list::separator
** The separator between two 'list' nodes in the input.
** Its value can be TOKEN_SEMICOLON or TOKEN_AMPERSAND (or TOKEN_EOL for
** compound lists only).
**
** \var list::next
** The next list node. Can be NULL
*/
struct list
{
    struct base base;
    struct and_or *and_or;
    enum token_type separator;
    struct list *next;
};

/**
** \brief Create a new 'list' node with provided first 'and_or' node.
**
** \param and_or A pointer to the 'and_or' node to put in the 'list' node. Must
** not be NULL.
** \return A new 'list' node with its 'and_or' field filled by the 'and_or'
*argument.
*/
struct list *list_create(struct and_or *and_or);

/**
** \brief Add an element at the end of the provided list with a specified
** separator token between the last 'and_or' node and the new 'and_or' node.
**
** \param list A pointer to the list where you want to append an element in it.
** Must not be NULL.
** \param and_or A pointer to the 'and_or' node to put in the new 'list' node.
** Must not be NULL.
** \param separator The separator between the last 'and_or' node and the new
** 'and_or' node. Must be TOKEN_SEMICOLON or TOKEN_AMPERSAND (or TOKEN_EOL for
** compound lists only).
*/
void list_append(struct list *list, struct and_or *and_or,
                 enum token_type separator);

/**
** \brief Print the whole list
**
** Browse the list, and for each node, calls 'and_or_print' with its 'and_or'
** field, then print
** the separator (if 'next' field is not NULL).
**
** \param list A pointer to the list you want to print. Must not be NULL.
*/
void list_print(const struct list *list);

/**
** \brief Release all memory held by the list
**
** \param list A pointer to the list you want to free. If 'list' is NULL, do
** nothing.
*/
void list_free(struct list *list);

#endif /* ! LIST_H */
