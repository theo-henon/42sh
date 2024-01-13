#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "lexer/token.h"

Test(token_tests, create_null_value)
{
    struct token *t = token_create(TOKEN_EOL, NULL, 0, 0);
    cr_assert_not_null(t);
    cr_expect_eq(t->col, 0);
    cr_expect_eq(t->row, 0);
    cr_expect_null(t->value);
    cr_expect_eq(t->type, TOKEN_EOL);
    token_free(t);
}

Test(token_tests, create_not_null_value)
{
    char *echo = calloc(5, sizeof(char));
    strcpy(echo, "echo");
    struct token *t = token_create(TOKEN_EOL, echo, 0, 0);
    cr_assert_not_null(t);
    cr_expect_eq(t->col, 0);
    cr_expect_eq(t->row, 0);
    cr_expect_str_eq(t->value, echo);
    cr_expect_eq(t->type, TOKEN_EOL);
    token_free(t);
}

Test(token_tests, print_eof, .init = cr_redirect_stdout)
{
    struct token *eof = token_create(TOKEN_EOF, NULL, 0, 0);
    token_print(eof);
    fflush(stdout);
    cr_expect_stdout_eq_str("EOF\n");
    token_free(eof);
}

Test(token_tests, print_eol, .init = cr_redirect_stdout)
{
    struct token *eol = token_create(TOKEN_EOL, NULL, 0, 0);
    token_print(eol);
    fflush(stdout);
    cr_expect_stdout_eq_str("EOL\n");
    token_free(eol);
}

Test(token_tests, print_semicolon, .init = cr_redirect_stdout)
{
    struct token *semicolon = token_create(TOKEN_SEMICOLON, NULL, 0, 0);
    token_print(semicolon);
    fflush(stdout);
    cr_expect_stdout_eq_str(";\n");
    token_free(semicolon);
}

Test(token_tests, print_word, .init = cr_redirect_stdout)
{
    char *echo = calloc(5, sizeof(char));
    strcpy(echo, "echo");
    struct token *word = token_create(TOKEN_WORD, echo, 0, 0);
    token_print(word);
    fflush(stdout);
    cr_expect_stdout_eq_str("echo\n");
    token_free(word);
}

Test(token_tests, print_if, .init = cr_redirect_stdout)
{
    struct token *if_tok = token_create(TOKEN_IF, NULL, 0, 0);
    token_print(if_tok);
    fflush(stdout);
    cr_expect_stdout_eq_str("if\n");
    token_free(if_tok);
}

Test(token_tests, print_then, .init = cr_redirect_stdout)
{
    struct token *if_tok = token_create(TOKEN_THEN, NULL, 0, 0);
    token_print(if_tok);
    fflush(stdout);
    cr_expect_stdout_eq_str("then\n");
    token_free(if_tok);
}

Test(token_tests, print_else, .init = cr_redirect_stdout)
{
    struct token *fi = token_create(TOKEN_ELSE, NULL, 0, 0);
    token_print(fi);
    fflush(stdout);
    cr_expect_stdout_eq_str("else\n");
    token_free(fi);
}