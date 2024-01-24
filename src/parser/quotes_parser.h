#ifndef QUOTES_PARSER_H
#define QUOTES_PARSER_H

#include "parser.h"

struct token *parse_single_quotes(struct parser *parser);
struct token *single_quotes_value(struct parser *parser);

#endif // QUOTES_PARSER_H
