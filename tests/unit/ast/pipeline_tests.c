#define _POSIX_C_SOURCE 200809L

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <signal.h>

#include "ast/pipeline.h"
#include "ast/simple_cmd.h"

Test(pipeline_tests, print_null, .signal = SIGSEGV)
{
    pipeline_print(NULL);
}

Test(pipeline_tests, print_args, .init = cr_redirect_stdout)
{
    struct simple_cmd *cmd1 = simple_cmd_init();
    struct simple_cmd *cmd2 = simple_cmd_init();
    simple_cmd_addarg(cmd1, strdup("test1"));
    simple_cmd_addarg(cmd2, strdup("test2"));
    struct pipeline *pipe = pipeline_create((struct base *)cmd1);
    pipeline_append(pipe, (struct base *)cmd2);
    pipe->negate = true;
    pipeline_print(pipe);
    fflush(stdout);
    cr_expect_stdout_eq_str("! test1 | test2");
    pipeline_free(pipe);
}
