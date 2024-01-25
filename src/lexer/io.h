#ifndef IO_H
#define IO_H

#define INPUT_BUF_SIZE 128

#include <stddef.h>
#include <stdio.h>

struct input
{
    FILE *stream;
    char buf[INPUT_BUF_SIZE];
    size_t readed;
    size_t offset;
};

struct input *input_from_file(const char *filename);
struct input *input_from_stdin(void);
struct input *input_from_string(char *input);
int input_read(struct input *input);
char input_getchar(struct input *input);
char input_readchar(struct input *input);
void input_free(struct input *input);
struct input *input_get(int argc, char *argv[]);

#endif /* ! IO_H */
