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

    struct ast *ast = parse_input(parser);
    if (ast == NULL)
        return parser->status == PARSER_UNEXPECTED_TOKEN ? 2 : 0;

    struct visitor *visitor = visitor_init();
    if (visitor == NULL)
        return 2;

    int code = base_visit(visitor, ast->root);

    // Releases all memory
    free(res);
    lexer_free(lexer);
    free(parser);
    ast_free(ast);
    visitor_free(visitor);
    return code;
}
