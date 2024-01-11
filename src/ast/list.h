#ifndef LIST_H
#define LIST_H

#include "simple_cmd.h"


struct list
{
    struct base base;
    struct simple_cmd **cmds;
};

#endif /* ! LIST_H */