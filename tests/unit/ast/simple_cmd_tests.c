#define _POSIX_C_SOURCE 200809L

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <signal.h>

#include "ast/simple_cmd.h"

Test(simple_cmd_tests, print_null, .signal = SIGSEGV)
{
    simple_cmd_print(NULL);
}

Test(simple_cmd_tests, print_args, .init = cr_redirect_stdout)
{
    struct simple_cmd *tmp = simple_cmd_init();
    simple_cmd_addarg(tmp, strdup("test1"));
    simple_cmd_addarg(tmp, strdup("test2"));
    simple_cmd_free(tmp);
    fflush(stdout);
    cr_expect_stdout_eq_str("test1 test2\n");
    simple_cmd_free(tmp);
}

Test(simple_cmd_tests, init_simple_cmd)
{
    struct simple_cmd *tmp = simple_cmd_init();
    cr_assert_not_null(tmp);
}

Test(simple_cmd_free, add_arg_and_free_simple_cmd)
{
    struct simple_cmd *tmp = simple_cmd_init();
    simple_cmd_addarg(tmp, strdup("test"));
    cr_expect_str_eq(tmp->args[0], "test");
    cr_expect_eq(tmp->argc, 2);
    simple_cmd_free(tmp);
}
