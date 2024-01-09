#ifndef IO_H
#define IO_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>


char *io(int argc, char *argv[]);
char *get_input_from_file(char *filename);
char *get_input_from_stdin(void);

#endif /* ! IO_H */
