#ifndef PARSER_H
#define PARSER_H


#include "../ast/ast.h"
#include "../ast/simple_cmd.h"
#include "../ast/list.h"
#include "../ast/if.h"
#include "../lexer/lexer.h"

enum parser_status 
{
    PARSER_OK,
    PARSER_END
};


struct parser 
{
    enum parser_status status;
    struct lexer *lexer;
};

struct ast *parse_input(struct lexer *lexer);
struct simple_cmd *parse_simple_cmd(struct lexer *lexer);
struct list *parse_list(struct lexer *lexer);
struct if_clause *parse_if_clause(struct lexer *lexer);



/*
    faire une fonction de parse par feature:
        parse_simple_cmd
        parse_list 
        parse_if 
*/

#endif /* ! PARSER_H */