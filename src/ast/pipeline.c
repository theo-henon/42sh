#include "pipeline.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct pipeline *pipeline_create(struct base *cmd)
{
    struct pipeline *new_pipeline = calloc(1, sizeof(struct pipeline));
    if (!new_pipeline)
        return NULL;
    new_pipeline->base.type = PIPELINE;
    new_pipeline->cmd = cmd;
    new_pipeline->negate = false;
    return new_pipeline;
}

void pipeline_append(struct pipeline *pipeline, struct base *cmd)
{
    struct pipeline *tmp = pipeline;
    while (tmp->next != NULL)
        tmp = tmp->next;
    struct pipeline *new_pipeline = pipeline_create(cmd);
    tmp->next = new_pipeline;
}

#ifdef PRETTY_PRINT
void pipeline_print(const struct pipeline *pipeline)
{
    const struct pipeline *tmp = pipeline;
    if (tmp->negate)
    {
        printf("! ");
        fflush(stdout);
    }
    while (tmp != NULL)
    {
        base_print(tmp->cmd);
        if (tmp->next != NULL)
        {
            printf(" | ");
            fflush(stdout);
        }
        tmp = tmp->next;
    }
    fflush(stdout);
}
#endif // PRETTY_PRINT

void pipeline_free(struct pipeline *pipeline)
{
    if (pipeline == NULL)
        return;
    else
    {
        pipeline_free(pipeline->next);
        base_free(pipeline->cmd);
        free(pipeline);
    }
}
