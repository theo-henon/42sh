#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <signal.h>

#include "lexer/io.h"

Test(io_tests, input_from_file_null, .init = cr_redirect_stderr)
{
    cr_assert_null(input_from_file(NULL));
}

Test(io_tests, input_from_file_non_existent, .init = cr_redirect_stderr)
{
    cr_assert_null(input_from_file("fgwgwgwgw"));
}

Test(io_tests, input_from_file_existent)
{
    struct input *input = input_from_file("Makefile.am");
    cr_assert_not_null(input);
    cr_expect_not_null(input->stream);
    cr_expect_str_empty(input->buf);
    cr_expect_eq(input->readed, 0);
    cr_expect_eq(input->offset, 0);
    input_free(input);
}

Test(io_tests, input_from_stdin_)
{
    struct input *input = input_from_stdin();
    cr_assert_not_null(input);
    cr_expect_eq(input->stream, stdin);
    cr_expect_str_empty(input->buf);
    cr_expect_eq(input->readed, 0);
    cr_expect_eq(input->offset, 0);
    input_free(input);
}

Test(io_tests, input_from_string_not_null)
{
    char str[] = "Hello World!";
    struct input *input = input_from_string(str);
    cr_assert_not_null(input);
    cr_expect_not_null(input->stream);
    cr_expect_str_empty(input->buf);
    cr_expect_eq(input->readed, 0);
    cr_expect_eq(input->offset, 0);
    input_free(input);
}
