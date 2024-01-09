#define _POSIX_C_SOURCE 200809L


#include "io.h"

char *io(int argc, char *argv[])
{
    if (argc == 3 && strcmp(argv[1], "-c") == 0)
        return argv[2];
    if (argc == 2)
        return get_input_from_file(argv[1]);
    if (argc == 1)
    {
        return get_input_from_stdin();
    }
    else 
    {
        fprintf(stderr, "Invalid Arguments\n");
        return NULL;
    }

}

char *get_input_from_file(char *filename)
{
    FILE* fp = fopen(filename, "r");
    if (fp == NULL)
    {
        fprintf(stderr, "File to open file !\n");
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
    char *input = NULL;
    size_t len = 0;
    int read;

    read = getline(&input, &len, stdin);

    if (read == -1)
    {
        fprintf(stderr, "Fail to read stdin !\n");
        free(input);
        return NULL;
    }
    if (input[read - 1] == '\n')
        input[read - 1] = '\0';
    return input;
}
