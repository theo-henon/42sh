/**
** \file pipeline.h
** \brief Provide a definition of a 'pipeline' struct and functions to create,
** add element in it, print and free it
** \date 2024-01-21
*/

#ifndef PIPELINE_H
#define PIPELINE_H

#include <stdbool.h>

#include "ast.h"

/**
** \struct pipeline
** \brief Represent a 'pipeline' node in the AST.
**
** This structure corresponds to this rule of the grammar in the SCL :
** \code
** pipeline = ['!'] command { '|' {'\n'} command } ;
** \endcode
**
** \see SCL grammar rules: http://tinyurl.com/2wc4jera
**
** \var pipeline::base
** The base of all AST nodes.
**
** \var pipeline::negate
** A boolean that represents if the pipeline is negate or not (if TOKEN_NOT is
** present before the first 'pipeline' node). Must be equals to 'false' from the
** second 'pipeline' node.
**
** \var pipeline::cmd
** The 'command' node to store in the pipeline node. Must not be null.
** Its 'type' field must be one of those :
** - SIMPLE_CMD
** - IF_CLAUSE
** - WHILE
** - UNTIL
** - CASE
** - FOR
** - FUNCDEC
**
** \var pipeline::next
** The next pipeline node. Can be NULL
*/
struct pipeline
{
    struct base base;
    bool negate;
    struct base *cmd;
    struct pipeline *next;
};

/**
** \brief Create a new 'pipeline' node with the provided 'command' node
**
** \param cmd A pointer to the 'command' node you want to put in the new
** 'pipeline' node. Must not be NULL.
** The 'command' node stores in the pipeline node. Must not be null.
** Its 'type' field must be one of those :
** - SIMPLE_CMD
** - IF_CLAUSE
** - WHILE
** - UNTIL
** - CASE
** - FOR
** - FUNCDEC
** \return A pointer to a new 'pipeline' node witch its 'cmd' field
** filled by 'cmd' argument.
*/
struct pipeline *pipeline_create(struct base *cmd);

/**
** \brief Add a new 'pipeline' node that contains then provided 'command'
** node at the end of the provided pipeline.
**
** \param pipeline A pointer to the pipeline you want to add a new node in.
** \param cmd A pointer to the 'command' node to put in the new
** 'pipeline' node.
*/
void pipeline_append(struct pipeline *pipeline, struct base *cmd);

/**
** \brief Release all memory held by the provided pipeline
**
** \param list A pointer to the pipeline you want to free.
** If 'pipeline' argument is NULL, do
** nothing.
*/
void pipeline_free(struct pipeline *pipeline);

#endif // PIPELINE_H
