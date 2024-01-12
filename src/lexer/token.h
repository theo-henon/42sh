#ifndef TOKEN_H
#define TOKEN_H

enum token_type
{
    TOKEN_EOF,
    TOKEN_EOL,
    TOKEN_SEMICOLON,
    TOKEN_WORD,
    TOKEN_IF,
    TOKEN_FI,
    TOKEN_ELSE,
    TOKEN_THEN,
    TOKEN_ELIF
};

struct token
{
    unsigned row;
    unsigned col;
    char *value;
    enum token_type type;
};

struct token *token_create(enum token_type type, char *value, unsigned row,
                           unsigned col);
void token_free(struct token *token);
void token_print(const struct token *token);

#endif // TOKEN_H
