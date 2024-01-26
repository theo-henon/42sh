#include "io.h"

#include <errno.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 128

struct input *input_from_file(const char *filename)
{
    errno = 0;
    FILE *file = fopen(filename, "r");
    struct input *in = NULL;
    if (file != NULL)
    {
        errno = 0;
        in = calloc(1, sizeof(struct input));
        if (in != NULL)
            in->stream = file;
        else
            perror("Cannot allocate input");
    }
    else
        perror("Failed to open file");
    return in;
}

struct input *input_from_stdin(void)
{
    errno = 0;
    struct input *in = calloc(1, sizeof(struct input));
    if (in != NULL)
        in->stream = stdin;
    else
        perror("Cannot allocate input");
    return in;
}

struct input *input_from_string(char *input)
{
    errno = 0;
    FILE *file = fmemopen(input, strlen(input), "r");
    struct input *in = NULL;
    if (file != NULL)
    {
        errno = 0;
        in = calloc(1, sizeof(struct input));
        if (in != NULL)
            in->stream = file;
        else
            perror("Cannot allocate input");
    }
    else
        perror("Failed to open file");
    return in;
}

int input_read(struct input *input)
{
    input->readed =
        fread(input->buf, sizeof(char), INPUT_BUF_SIZE, input->stream);
    if (input->readed == 0)
    {
        if (ferror(input->stream))
        {
            fputs("Cannot read input\n", stderr);
            return -1;
        }
        return 1;
    }
    input->offset = 0;
    return 0;
}

char input_readchar(struct input *input)
{
    if (input->offset >= input->readed)
    {
        int status = input_read(input);
        if (status != 0)
            return status == 1 ? '\0' : -1;
    }
    return input->buf[input->offset++];
}

void input_free(struct input *input)
{
    if (input == NULL)
        return;

    if (input->stream != NULL)
        fclose(input->stream);
    free(input);
}

struct input *input_get(int argc, char *argv[])
{
    if (argc == 3 && strcmp(argv[1], "-c") == 0)
        return input_from_string(argv[2]);
    if (argc == 2)
        return input_from_file(argv[1]);
    if (argc == 1)
        return input_from_stdin();
    else
        fprintf(stderr, "Invalid Arguments\n");
    return NULL;
}
