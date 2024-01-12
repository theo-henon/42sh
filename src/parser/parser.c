#include "parser.h"


#include <stdlib.h>
#include <string.h>
#include <stdio.h>


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
    args[i++] = NULL;
    return create_simple_cmd(args);
}

struct list *parse_list(struct lexer *lexer)
{
    int j = 0;
    struct simple_cmd *tmp = parse_simple_cmd(lexer);
    struct simple_cmd **cmds = calloc(1, sizeof(*tmp));
    cmds[j] = tmp;
    // add token and, or & during the next step
    while (lexer->current->type == TOKEN_SEMICOLON || lexer->current->type == TOKEN_EOL)
    {
        tmp = parse_simple_cmd(lexer);
        cmds = realloc(cmds, sizeof(cmds) + sizeof(*tmp));
        j++;
        cmds[j] = tmp;
    }
    cmds[j++] = NULL;
    return create_list(cmds);
}

static struct if_clause *rec_if(struct lexer *lexer)
{
    lexer_pop(lexer); //consome if 
    struct list *condition = parse_list(lexer); //if_body
    if (lexer->current->type != TOKEN_THEN)
    {
        fprintf(stderr, "Error parsing: Missing then ! \n");
        return NULL;
    }
    lexer_pop(lexer); // consume then
    struct list *then_body = parse_list(lexer);
    if (lexer->current->type != TOKEN_ELIF && lexer->current->type != TOKEN_ELSE)
    {
        fprintf(stderr, "Error parsing: Missing elif or else! \n");
        return NULL;
    }
    return create_if_clause((struct base *)condition, (struct base *)then_body, NULL);
}

struct if_clause *parse_if_clause(struct lexer *lexer)
{
    struct if_clause *tmp;
    tmp = rec_if(lexer);
    struct if_clause *head = tmp;
    while (lexer->current->type == TOKEN_ELIF)
    {
        tmp->else_body = (struct base*)rec_if(lexer);
        tmp = (struct if_clause*)tmp->else_body;
    }
    if (lexer->current->type == TOKEN_ELSE)
    {
        tmp->else_body = (struct base*)parse_list(lexer);
    }
    return head;
}


