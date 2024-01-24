#ifndef IF_PARSER_H
#define IF_PARSER_H

#include "ast/if.h"
#include "parser/parser.h"

struct if_clause *parse_if_clause(struct parser *parser);

#endif // IF_PARSER_H
