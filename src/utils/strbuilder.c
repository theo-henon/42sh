#include "strbuilder.h"

#include <stdlib.h>
#include <string.h>

struct string *string_create(void)
{
    struct string *str = calloc(1, sizeof(struct string));
    if (str != NULL)
    {
        str->buf = calloc(STRING_INITIAL_CAPACITY, sizeof(char));
        if (str->buf != NULL)
            str->capacity = STRING_INITIAL_CAPACITY;
        else
            free(str);
    }
    return str;
}

void string_catbuf(struct string *str, const char *buf, size_t n)
{
    size_t new_size = str->size + n;
    while (new_size >= str->capacity)
    {
        str->capacity += STRING_INITIAL_CAPACITY;
        str->buf = realloc(str->buf, str->capacity * sizeof(char));
    }

    strncpy(str->buf + str->size, buf, n);
}

char *string_tobuf(const struct string *str)
{
    char *buf = calloc(str->size + 1, sizeof(char));
    strncpy(buf, str->buf, str->size);
    return buf;
}

void string_free(struct string *str)
{
    if (str == NULL)
        return;
    free(str->buf);
    free(str);
}
