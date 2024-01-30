#ifndef TOKEN_H
#define TOKEN_H

#include <stdbool.h>

enum token_type
{
    TOKEN_EOF = 0,
    TOKEN_EOL,
    TOKEN_SEMICOLON,
    TOKEN_WORD,
    TOKEN_IF,
    TOKEN_FI,
    TOKEN_ELSE,
    TOKEN_THEN,
    TOKEN_ELIF,
    TOKEN_WHILE,
    TOKEN_DO,
    TOKEN_DONE,
    TOKEN_UNTIL
};

struct token
{
    char *value;
    enum token_type type;
};

struct token *token_create(enum token_type type, char *value);
void token_free(struct token *token);
void token_set_type(struct token *token);
bool token_islist_delim(const struct token *token);
bool token_isclist_delim(const struct token *token);
bool istoken(char c);

#endif // TOKEN_H
