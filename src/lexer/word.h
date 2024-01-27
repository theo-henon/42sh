#ifndef WORD_H
#define WORD_H

#include "lexer.h"
#include "utils/strbuilder.h"

struct string *single_quote_lex(struct lexer *lexer, char quote);
int word_append(struct lexer *lexer, struct string *word, char c);
struct string *word_lex(struct lexer *lexer, char first);

#endif // WORD_H
