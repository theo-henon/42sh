#ifndef LIST_H
#define LIST_H

#include "simple_cmd.h"

struct list
{
    struct base base;
    struct simple_cmd **cmds;
};

struct list *create_list(struct simple_cmd **cmds);
void free_list(struct list *list);

#endif /* ! LIST_H */