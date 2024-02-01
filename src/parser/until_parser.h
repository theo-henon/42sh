#ifndef UNTIL_PARSER_H
#define UNTIL_PARSER_H

#include "ast/until.h"
#include "parser/parser.h"

struct until_clause *parse_until_clause(struct parser *parser);

#endif /* ! UNTIL_PARSER_H */
