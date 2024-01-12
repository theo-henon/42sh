#include "parser.h"


#include <stdlib.h>
#include <string.h>






struct simple_cmd *parse_simple_cmd(struct lexer *lexer)
{
    int i = 0;
    char **args = calloc(1, strlen(lexer->current->value));
    strcpy(args[i], lexer->current->value);
    lexer_pop(lexer);
    while (lexer->current->type == TOKEN_WORD)
    {
        args = realloc(args, sizeof(args) + strlen(lexer->current->value));
        i++;
        strcpy(args[i], lexer->current->value);
        lexer_pop(lexer);
    }
    return create_simple_cmd(args);
}

struct list *parse_list(struct lexer lexer);


struct ast *parse_input(struct lexer *lexer)
{
    if (lexer->current->type == SIMPLE_CMD)
    {
        struct simple_cmd *cmd = parse_simple_cmd(lexer);

    }
    else if (lexer->current->type == IF_CLAUSE)
    {
        
    }
    else if (lexer->current->type == LIST)
    {

    }
    else
    {
        
    }

    /*
    switch (lexer->current->type)
    {
        case SIMPLE_CMD:
            char **args = calloc(1, strlen(lexer->current->value));
            strcpy(args[0], lexer->current->value);

            struct token *tmp = lexer_pop(lexer);
            if (tmp)
            create_simple_cmd(char **args)
            break;
        case TOKEN_IF:
            create_if_clause(struct base *condition, struct base *then_body, struct base *else_body)
            break;
        case 

    }
    */

}

struct simple_cmd *parse_simple_cmd(struct lexer lexer);
struct list *parse_list(struct lexer lexer);
struct if_clause *parse_if_clause(struct lexer lexer);
