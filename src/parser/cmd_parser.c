#include "cmd_parser.h"

#include <stdlib.h>
#include <string.h>

#include "ast/simple_cmd.h"
#include "if_parser.h"

struct simple_cmd *parse_simple_cmd(struct parser *parser)
{
    struct token *token = lexer_peek(parser->lexer);
    struct simple_cmd *cmd = simple_cmd_init();
    while (!token_isclist_delim(token) && !token_isand_or(token))
    {
        simple_cmd_addarg(cmd, strdup(token->value));
        token = lexer_pop(parser->lexer);
    }

    if (parser->lexer->status == LEXER_UNEXPECTED_EOF)
    {
        parser->status = PARSER_UNEXPECTED_TOKEN;
        simple_cmd_free(cmd);
        cmd = NULL;
    }
    else if (cmd->args == NULL)
    {
        simple_cmd_free(cmd);
        cmd = NULL;
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
