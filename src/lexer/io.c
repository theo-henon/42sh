#include "io.h"

#include <stdlib.h>
#include <string.h>

char *io(int argc, char *argv[])
{
    if (argc == 3 && strcmp(argv[1], "-c") == 0)
        return strdup(argv[2]);
    if (argc == 2)
        return get_input_from_file(fopen(argv[1], "r"));
    if (argc == 1)
        return get_input_from_file(stdin);
    else
        fprintf(stderr, "Invalid Arguments\n");
    return NULL;
}

char *get_input_from_file(FILE *fp)
{
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
