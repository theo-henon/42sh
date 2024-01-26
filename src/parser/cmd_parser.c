#include "cmd_parser.h"

#include <stdlib.h>
#include <string.h>

#include "ast/simple_cmd.h"

struct simple_cmd *parse_simple_cmd(struct parser *parser)
{
    struct token *token = lexer_peek(parser->lexer);
    struct simple_cmd *cmd = simple_cmd_init();
    while (!token_isclist_delim(token))
    {
        simple_cmd_addarg(cmd, strdup(token->value));
        token = lexer_pop(parser->lexer);
    }

    if (cmd->args == NULL)
    {
        free(cmd);
        return NULL;
    }
    return cmd;
}

struct base *parse_cmd(struct parser *parser)
{
    struct token *token = lexer_peek(parser->lexer);
    if (token->type == TOKEN_IF)
        return (struct base *)parse_if_clause(parser);
    return (struct base *)parse_simple_cmd(parser);
}
