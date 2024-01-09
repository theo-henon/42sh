#include "io.h"

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>



// ./42sh -c "echo hello" 
// ./42sh file.sh
// ./42sh (stdin)


char *io(int argc, char *argv[])
{
    if (argc == 3 && strcmp(argv[1], "-c") == 0)
        return argv[2];
    if (argc == 2)
        return get_input_from_file(argv[1]);
    if (argc == 1)
    {
        printf("stdin mode \n");
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
        fread(buffer, 1, len, fp);
    buffer[len] = '\0';
    fclose(fp);
    return buffer;

}

char *get_input_from_stdin(void)
{
    char *input = NULL;
    size_t len = 0;
    ssize_t read;

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



int main(int argc, char *argv[])
{
    char *res = io(argc, argv);
    printf("command: %s\n", res);
    return 0;
}
