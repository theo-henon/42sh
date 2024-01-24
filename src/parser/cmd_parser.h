/**
 * @file cmd_parser.h
 * @brief Provide parsers for 'command' rule.
 * @date 2024-01-22
 */

#ifndef CMD_PARSER_H
#define CMD_PARSER_H

#include "ast/ast.h"
#include "parser.h"

/**
** @brief Parse input to create a 'simple_cmd' node using provided parser.
**
** The first token must be a TOKEN_WORD and should be peek using 'lexer_peek',
** All other tokens are considered as TOKEN_WORD and represents arguments to
** add, using 'simple_cmd_addarg', until one of those token is encountered :
** - TOKEN_SEMICOLON
** - TOKEN_EOL
** - TOKEN_EOF
** - TOKEN_PIPE
** - TOKEN_AMPERSAND
** - Logical operators: TOKEN_AND, TOKEN_OR
** - All redirections tokens
** - Parentheses & braces
**
** \see How to create a 'simple_cmd' node: simple_cmd.h.
**
** @param parser A pointer to the parser to use to parse input.
** @return A pointer to a new 'simple_cmd' node parsed in the input, or NULL
** if an unexpected token is encountered or any other error occurs.
*/
struct simple_cmd *parse_simple_cmd(struct parser *parser);

/**
** @brief Parse the 'command' rule of the SCL.
**
** Parse inputs that derives from thoses rules :
** \code
** command = simple_cmd
**      | shell_command { redirection }
**      | funcdec { redirection }
**      ;
**
** shell_command = '{' compound_list '}'
**      | '(' compound_list ')'
**      | rule_for
**      | rule_while
**      | rule_until
**      | rule_case
**      | rule_if
**      ;
** \endcode
** Must peek a token using 'lexer_peek' and call the corresponding 'command' node parser.
**
** \see SCL grammar rules: http://tinyurl.com/2wc4jera
**
** @param parser A pointer to the parser to use to parse input.
** @return A pointer to the new node, NULL if an unexpected token is
** encountered.
*/
struct base *parse_cmd(struct parser *parser);

#endif // / CMD_PARSER_H
