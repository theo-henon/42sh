#ifndef TOKEN_H
#define TOKEN_H

enum token_type 
{
    TOKEN_EOF,
    TOKEN_EOL,
    TOKEN_SEMICOLON
};

struct token 
{
    unsigned row;
    unsigned col;
    char *value;
    enum token_type type;
};

struct token *token_create(enum token_type type, char *value);
void token_free(struct token *token);
void token_print(struct token *token);

#endif // TOKEN_H