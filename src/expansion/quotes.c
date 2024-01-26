#include "quotes.h"

#include <string.h>

#include "utils/strbuilder.h"

char *expand_squote(char *word)
{
    struct string *quoted = string_create();
    while (*word != '\0')
    {
        if (*word != '\'')
            string_catbuf(quoted, word, 1);
        word++;
    }

    char *buf = string_tobuf(quoted);
    string_free(quoted);
    return buf;
}
