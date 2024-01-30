#ifndef WHILE_PARSER_H
#define WHILE_PARSER_H

#include "ast/while.h"
#include "parser/parser.h"

struct while_clause *parse_while_clause(struct parser *parser);

#endif /* ! WHILE_PARSER_H */
