#include "io.h"

#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 128

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
