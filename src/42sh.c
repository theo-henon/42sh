#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "ast/ast.h"
#include "builtins/builtins.h"
#include "lexer/io.h"
#include "lexer/lexer.h"
#include "parser/parser.h"
#include "utils/options.h"
#include "visitor/visitor.h"

int main(int argc, char *argv[])
{

    char *cwd = getcwd(NULL, 0);
    setenv("PWD", cwd, 1);
    free(cwd);
    struct options options = { 0 };
    if (options_parse(argc, argv, &options) == -1)
        return 2;

    struct lexer *lexer = lexer_create(options.input);
    struct parser *parser = parser_create(lexer);
    struct visitor *visitor = visitor_init();
    struct ast *ast = parse_input(parser);

    int code = 0;
    while (ast)
    {
#ifdef PRETTY_PRINT
        if (options.pretty_print)
        {
            base_print(ast->root);
            putchar('\n');
            fflush(stdout);
        }
        else
            code = base_visit(visitor, ast->root);
#else
        code = base_visit(visitor, ast->root);
#endif // PRETTY_PRINT
        ast_free(ast);
        ast = parse_input(parser);
    }

    if (parser->status == PARSER_UNEXPECTED_TOKEN)
        code = 2;

    input_free(options.input);
    lexer_free(lexer);
    free(parser);
    visitor_free(visitor);
    return code;
}
