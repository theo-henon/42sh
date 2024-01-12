#ifndef BUILTINS_H
#define BUILTINS_H


typedef int (*builtin_t)(char **argv);

struct builtin
{
    const char *name;
    builtin_t func;
};

int builtin_echo(char **argv);
int builtin_true(char **argv);
int builtin_false(char **argv);
struct builtin **builtins_load(void);
void builtins_free(struct builtin **builtins);

#endif // BUILTINS_H
