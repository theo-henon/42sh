#ifndef STRING_H
#define STRING_H

#define STRING_INITIAL_CAPACITY 16

#include <stddef.h>

struct string
{
    char *buf;
    size_t size;
    size_t capacity;
};

struct string *string_create(void);
void string_catbuf(struct string *str, const char *buf, size_t n);
char *string_tobuf(const struct string *str);
void string_free(struct string *str);

#endif // STRING_H
