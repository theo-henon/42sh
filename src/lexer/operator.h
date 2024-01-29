#ifndef OPERATOR_H
#define OPERATOR_H

#include "lexer.h"
#include "utils/strbuilder.h"

struct string *operator_lex(struct lexer *lexer, char first,
                            enum token_type *type);

#endif // OPERATOR_H

