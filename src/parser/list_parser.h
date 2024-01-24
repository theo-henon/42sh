#ifndef LIST_PARSER_H
#define LIST_PARSER_H

#include "ast/list.h"
#include "parser.h"

struct list *parse_list(struct parser *parser);
struct list *parse_compound_list(struct parser *parser);

#endif // LIST_PARSER_H
