#include "list.h"

#include <stdlib.h>

struct list *create_list(struct simple_cmd **cmds)
{
    struct list *list = calloc(1, sizeof(struct list));
    list->base.type = LIST;
    list->cmds = cmds;

    return list;
}

void free_list(struct list *list)
{
    struct simple_cmd **tmp = list->cmds;
    while (tmp)
    {
        free(*tmp); 
        tmp++;
    }
    free(tmp);
}

