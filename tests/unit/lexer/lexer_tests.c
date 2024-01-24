#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "lexer/lexer.h"

static void lexer_expect(struct lexer *lexer, enum token_type type,
                         const char *value)
{
    cr_expect_not_null(lexer->current);
    if (lexer->current != NULL)
    {
        cr_expect_eq(lexer->status, type == TOKEN_EOF ? LEXER_END : LEXER_OK);
        cr_expect_eq(lexer->current->type, type);
        if (value == NULL)
            cr_expect_null(lexer->current->value);
        else
            cr_expect_str_eq(lexer->current->value, value);
    }
}

Test(lexer_tests, create_null)
{
    struct lexer *lexer = lexer_create(NULL);
    cr_expect_null(lexer);
    lexer_free(lexer);
}

Test(lexer_tests, create_empty)
{
    struct lexer *lexer = lexer_create("");
    cr_assert_not_null(lexer);
    cr_expect_str_empty(lexer->input);
    cr_expect_eq(lexer->status, LEXER_OK);
    cr_expect_null(lexer->current);
    cr_expect_eq(lexer->offset, 0);
    lexer_free(lexer);
}

Test(lexer_tests, create_echo_toto)
{
    struct lexer *lexer = lexer_create("echo toto");
    cr_assert_not_null(lexer);
    cr_expect_str_eq(lexer->input, "echo toto");
    cr_expect_eq(lexer->status, LEXER_OK);
    cr_expect_null(lexer->current);
    cr_expect_eq(lexer->offset, 0);
    lexer_free(lexer);
}

Test(lexer_tests, pop_eof)
{
    struct lexer *lexer = lexer_create("");

    lexer_pop(lexer);
    lexer_expect(lexer, TOKEN_EOF, "");
    cr_expect_eq(lexer->status, LEXER_END);

    lexer_free(lexer);
}

Test(lexer_tests, pop_multiples_eof)
{
    struct lexer *lexer = lexer_create("");

    lexer_pop(lexer);
    lexer_expect(lexer, TOKEN_EOF, "");

    lexer_pop(lexer);
    lexer_expect(lexer, TOKEN_EOF, "");

    lexer_pop(lexer);
    lexer_expect(lexer, TOKEN_EOF, "");

    lexer_free(lexer);
}

Test(lexer_tests, pop_eol)
{
    struct lexer *lexer = lexer_create("\n");

    lexer_pop(lexer);
    lexer_expect(lexer, TOKEN_EOL, "\n");

    lexer_free(lexer);
}

Test(lexer_tests, pop_semicolon)
{
    struct lexer *lexer = lexer_create(";");

    lexer_pop(lexer);
    lexer_expect(lexer, TOKEN_SEMICOLON, ";");

    lexer_free(lexer);
}

Test(lexer_tests, pop_word)
{
    struct lexer *lexer = lexer_create("word");

    lexer_pop(lexer);
    lexer_expect(lexer, TOKEN_WORD, "word");

    lexer_free(lexer);
}

Test(lexer_tests, pop_if)
{
    struct lexer *lexer = lexer_create("if");

    lexer_pop(lexer);
    lexer_expect(lexer, TOKEN_IF, "if");

    lexer_free(lexer);
}

Test(lexer_tests, pop_then)
{
    struct lexer *lexer = lexer_create("then");

    lexer_pop(lexer);
    lexer_expect(lexer, TOKEN_THEN, "then");

    lexer_free(lexer);
}

Test(lexer_tests, pop_else)
{
    struct lexer *lexer = lexer_create("else");

    lexer_pop(lexer);
    lexer_expect(lexer, TOKEN_ELSE, "else");

    lexer_free(lexer);
}

Test(lexer_tests, pop_elif)
{
    struct lexer *lexer = lexer_create("elif");

    lexer_pop(lexer);
    lexer_expect(lexer, TOKEN_ELIF, "elif");

    lexer_free(lexer);
}

Test(lexer_tests, pop_multiple_words)
{
    struct lexer *lexer = lexer_create("word1\tword2       word3");

    lexer_pop(lexer);
    lexer_expect(lexer, TOKEN_WORD, "word1");

    lexer_pop(lexer);
    lexer_expect(lexer, TOKEN_WORD, "word2");

    lexer_pop(lexer);
    lexer_expect(lexer, TOKEN_WORD, "word3");

    lexer_free(lexer);
}

Test(lexer_tests, echo_whitespace)
{
    struct lexer *lexer = lexer_create("echo ");

    lexer_pop(lexer);
    lexer_expect(lexer, TOKEN_WORD, "echo");

    lexer_pop(lexer);
    lexer_expect(lexer, TOKEN_EOF, "");

    lexer_free(lexer);
}

Test(lexer_tests, word_trailing_blanks)
{
    struct lexer *lexer = lexer_create("         \tword");

    lexer_pop(lexer);
    lexer_expect(lexer, TOKEN_WORD, "word");

    lexer_free(lexer);
}

Test(lexer_tests, pop_single_quote)
{
    struct lexer *lexer = lexer_create("'");

    lexer_pop(lexer);
    lexer_expect(lexer, TOKEN_SINGLEQUOTE, "'");

    lexer_free(lexer);
}

Test(lexer_tests, pop_multiple_single_quotes)
{
    struct lexer *lexer = lexer_create("'''");

    lexer_pop(lexer);
    lexer_expect(lexer, TOKEN_SINGLEQUOTE, "'");

    lexer_pop(lexer);
    lexer_expect(lexer, TOKEN_SINGLEQUOTE, "'");

    lexer_pop(lexer);
    lexer_expect(lexer, TOKEN_SINGLEQUOTE, "'");

    lexer_free(lexer);
}
