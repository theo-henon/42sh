#include "and_or.h"

#include <stdio.h>
#include <stdlib.h>

struct and_or *and_or_create_pipeline(struct pipeline *pipeline)
{
    struct and_or *new_and_or = calloc(1, sizeof(struct and_or));
    if (!new_and_or)
        return NULL;
    new_and_or->pipeline = pipeline;
    new_and_or->base.type = AND_OR;
    return new_and_or;
}

struct and_or *and_or_create_operator(enum token_type operator)
{
    struct and_or *new_and_or = calloc(1, sizeof(struct and_or));
    if (!new_and_or)
        return NULL;
    new_and_or->operator= operator;
    return new_and_or;
}

void and_or_print(const struct and_or *and_or)
{
    if (and_or == NULL)
        return;
    and_or_print(and_or->left);
    pipeline_print(and_or->pipeline);
    printf(" & ");
    and_or_print(and_or->right);
}

void and_or_free(struct and_or *and_or)
{
    if (and_or != NULL)
    {
        and_or_free(and_or->right);
        and_or_free(and_or->left);
        pipeline_free(and_or->pipeline);
        free(and_or);
    }
}
