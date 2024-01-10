#ifndef LEXER_H
#define LEXER_H


#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

enum lexer_status
{
    LEXER_OK,
    LEXER_END,
    LEXER_INVALID_TOKEN
};

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

struct lexer
{
    char *input;
    size_t offset;
    unsigned row;
    unsigned col;
    enum lexer_status lexer_status;
}; 

struct token *token_create(enum token_type type, char *value);
void token_free(struct token *token);
void token_print(struct token *token);

struct lexer *lexer_create(char *input);
void lexer_free(struct lexer *lexer);
struct token *lexer_peek(struct lexer *lexer);
struct token *lexer_pop(struct lexer *lexer);


#endif /*! LEXER_H */