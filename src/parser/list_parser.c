#include "list_parser.h"

#include "and_or_parser.h"

struct list *parse_list(struct parser *parser)
{
    struct and_or *and_or = parse_and_or(parser);
    if (!and_or)
        return NULL;
    return list_create(and_or);
}

struct list *parse_compound_list(struct parser *parser);