#ifndef AND_OR_PARSER_H
#define AND_OR_PARSER_H

#include "ast/and_or.h"
#include "parser.h"

struct and_or *parse_and_or(struct parser *parser);

#endif // AND_OR_PARSER_H
