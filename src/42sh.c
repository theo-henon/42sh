#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ast/ast.h"
#include "builtins/builtins.h"
#include "lexer/io.h"
#include "lexer/lexer.h"
#include "parser/parser.h"
#include "visitor/visitor.h"

int main(int argc, char *argv[])
{
    // Parses arguments and gets input
    char *res = io(argc, argv);
    if (res == NULL)
        return 2;

    // Creates AST and visits it
    struct lexer *lexer = lexer_create(res);
    if (lexer == NULL)
        return 2;

    struct parser *parser = parser_create(lexer);
    if (parser == NULL)
        return 2;

    struct visitor *visitor = visitor_init();
    if (visitor == NULL)
        return 2;

    struct ast *ast = parse_input(parser);

    int code = 0;

    while (ast)
    {
        code = base_visit(visitor, ast->root);
        ast_free(ast);
        ast = parse_input(parser);
    }

    if (parser->status == PARSER_UNEXPECTED_TOKEN)
        return 2;

    // Releases all memory
    free(res);
    lexer_free(lexer);
    free(parser);
    visitor_free(visitor);
    return code;
}
