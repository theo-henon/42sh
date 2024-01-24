/**
** \file simple_cmd.h
** \brief Provide a definition of a 'simple_cmd' struct and functions to create,
*add
** argument in it and print elements, and free it.
** \date 2024-01-21
*/

#ifndef SIMPLE_CMD_H
#define SIMPLE_CMD_H

#include "ast.h"

/**
** \struct simple_cmd
** \brief Represent a 'simple_cmd' node in the AST.
**
** This structure corresponds to our rule (for the moment) of the grammar
** in the SCL :
** \code
** simple_cmd = WORD { WORD } ;
** \endcode
**
** \see SCL grammar rules: http://tinyurl.com/2wc4jera
**
** \var simple_cmd::base
** The base of all AST nodes.
**
** \var simple_cmd::argc
** The number of arguments of the simple command, including the command name.
** Must be greater than 0.
**
** \var simple_cmd::args
** The NULL terminated array that contains all arguments of the command.
** For all argc > 0, args[argc] = NULL.
*/
struct simple_cmd
{
    struct base base;
    int argc;
    char **args;
};

/**
** \brief Init a new 'simple_cmd' node with no arguments (useful for the parser)
**
** \return A pointer to a new 'simple_cmd' node with 'argc' field equals to 1.
** (because 'args' field is a NULL terminated array and args[argc] = NULL)
*/
struct simple_cmd *simple_cmd_init(void);

/**
** \brief Add an argument to an existing 'simple_cmd' node.
**
** \param cmd A pointer to a 'simple_cmd' node. Must not be NULL.
** \param arg A pointer to the string that contains the argument to add.
*/
void simple_cmd_addarg(struct simple_cmd *cmd, char *arg);

/**
** \brief Print a 'simple_cmd' node.
**
** Browse all arguments, and for each argument, print it followed by
** a single whitespace (if the next argument is not NULL).
**
** \param cmd A pointer to a 'simple_cmd' node. Must not be NULL.
*/
void simple_cmd_print(const struct simple_cmd *cmd);

/**
** \brief Release all memory held by a 'simple_cmd' node.
**
** \param cmd A pointer to a 'simple_cmd' node. If it is NULL, do nothing.
*/
void simple_cmd_free(struct simple_cmd *cmd);

#endif /* ! SIMPLE_CMD_H */
