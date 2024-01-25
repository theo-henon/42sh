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
        fputs("Cannot read input\n", stderr);
        return ferror(input->stream) != 0 ? -1 : 1;
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
    if (input != NULL)
        return;
    if (input->stream != NULL)
        fclose(input->stream);
    free(input);
}

char *io(int argc, char *argv[])
{
    if (argc == 3 && strcmp(argv[1], "-c") == 0)
        return strdup(argv[2]);
    if (argc == 2)
        return get_input_from_file(argv[1]);
    if (argc == 1)
        return get_input_from_stdin();
    else
        fprintf(stderr, "Invalid Arguments\n");
    return NULL;
}

char *get_input_from_file(const char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        fprintf(stderr, "Fail to open file !\n");
        return NULL;
    }
    fseek(fp, 0, SEEK_END);
    int len = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char *buffer = malloc(sizeof(char) * len + 1);

    if (buffer)
    {
        if (fread(buffer, 1, len, fp) == 0)
            buffer[0] = '\0';
        else
            buffer[len] = '\0';
    }
    else
    {
        fprintf(stderr, "Fail allocation !\n");
        return NULL;
    }
    fclose(fp);
    return buffer;
}

char *get_input_from_stdin(void)
{
    char buf[BUF_SIZE];
    size_t size = 0;
    char *input = NULL;
    size_t readed = 0;
    size_t cur = 0;
    while ((readed = fread(buf, sizeof(char), BUF_SIZE, stdin)) > 0)
    {
        size += readed;
        input = realloc(input, (size + 1) * sizeof(char));
        input[size] = '\0';
        strncpy(input + cur, buf, readed);
        cur += readed;
    }

    if (input == NULL && feof(stdin))
        return calloc(1, sizeof(char));
    return input;
}
