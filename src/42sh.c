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
    struct input *input = input_get(argc, argv);
    if (input == NULL)
        return 2;

    struct lexer *lexer = lexer_create(input);
    struct parser *parser = parser_create(lexer);
    struct visitor *visitor = visitor_init();
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

    input_free(input);
    lexer_free(lexer);
    free(parser);
    visitor_free(visitor);
    return code;
}
