/**
 * @file pipeline_parser.h
 * @brief Provided a parser for 'pipeline' rule.
 * @date 2024-01-22
 */

#ifndef PIPELINE_PARSER_H
#define PIPELINE_PARSER_H

#include "ast/pipeline.h"
#include "parser.h"

/**
** \brief Parse input to create a 'pipeline' node using the provided parser.
**
** First, read the next token using 'lexer_pop'. If it's a TOKEN_NOT, set
** 'negate' field to true and read the next token. Then, call 'parse_cmd'
** to try to create a 'command' node that must not be NULL.
** Then while a TOKEN_PIPE is encountered, skip all TOKEN_EOL, and try
** parsing a new 'cmd' node using 'parse_cmd' that must not be NULL, and
** add it using 'pipeline_append'. It corresponds to this grammar rule.
**
** \note Only the first token can be a TOKEN_NOT. Every TOKEN_NOT encoutered
** after the first token is an unexpected token.
**
** \see How to create a 'pipeline' node: pipeline.h.
**
** \param parser A pointer to the parser to use.
** \return A pointer to a new 'pipeline' node, or NULL if an unexpected token is
** encountered or any other error occurs.
*/
struct pipeline *parse_pipeline(struct parser *parser);

#endif // PIPELINE_PARSER_H
