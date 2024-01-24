#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "lexer/token.h"

Test(token_tests, create_null_value)
{
    struct token *t = token_create(TOKEN_EOL, NULL);
    cr_assert_not_null(t);
    cr_expect_null(t->value);
    cr_expect_eq(t->type, TOKEN_EOL);
    token_free(t);
}

Test(token_tests, create_not_null_value)
{
    char *echo = calloc(5, sizeof(char));
    strcpy(echo, "echo");
    struct token *t = token_create(TOKEN_EOL, echo);
    cr_assert_not_null(t);
    cr_expect_str_eq(t->value, echo);
    cr_expect_eq(t->type, TOKEN_EOL);
    token_free(t);
}
