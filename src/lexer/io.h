#ifndef IO_H
#define IO_H

#include <stdio.h>

char *io(int argc, char *argv[]);
char *get_input_from_file(const char *filename);
char *get_input_from_stdin(void);

#endif /* ! IO_H */
