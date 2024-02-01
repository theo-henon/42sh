#include "list.h"

#include <stdio.h>
#include <stdlib.h>

struct list *list_create(struct and_or *and_or)
{
    struct list *list = calloc(1, sizeof(struct list));
    if (!list)
        return NULL;
    list->base.type = LIST;
    list->and_or = and_or;
    return list;
}

void list_append(struct list *list, struct and_or *and_or,
                 enum token_type separator)
{
    struct list *node = calloc(1, sizeof(struct list));
    if (!node)
        return;
    node->and_or = and_or;
    node->separator = separator;
    struct list *tmp = list;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = node;
}

void list_free(struct list *list)
{
    if (!list)
        return;
    while (list != NULL)
    {
        struct list *tmp = list->next;
        and_or_free(list->and_or);
        free(list);
        list = tmp;
    }
}
