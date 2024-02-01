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
