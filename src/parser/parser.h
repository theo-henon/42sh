#ifndef PARSER_H
#define PARSER_H

#define LIST_SIZE 20

#include "ast/ast.h"
#include "lexer/lexer.h"

enum parser_status
{
    PARSER_OK = 0,
    PARSER_END,
    PARSER_UNEXPECTED_TOKEN
};

struct parser
{
    enum parser_status status;
    struct lexer *lexer;
};

struct parser *parser_create(struct lexer *lexer);
struct ast *parse_input(struct parser *parser);

#endif /* ! PARSER_H */
