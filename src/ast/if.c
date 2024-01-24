#include "if.h"

#include <stdio.h>
#include <stdlib.h>

struct else_clause *else_clause_create(struct list *condition,
                                       struct list *body)
{
    struct else_clause *else_clause = calloc(1, sizeof(struct else_clause));
    if (!else_clause)
        return NULL;
    else_clause->condition = condition;
    else_clause->body = body;
    return else_clause;
}

void else_clause_append(struct else_clause *else_clause, struct list *condition,
                        struct list *body)
{
    struct else_clause *node = calloc(1, sizeof(struct else_clause));
    if (!else_clause)
        return;
    node->condition = condition;
    node->body = body;
    struct else_clause *tmp = else_clause;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = node;
}

void else_clause_print(const struct else_clause *else_clause)
{
    const struct else_clause *tmp = else_clause;
    while (tmp)
    {
        if (tmp->condition)
        {
            printf("elif ");
            list_print(tmp->condition);
        }
        else
            printf("else ");
        printf("\n");
        list_print(else_clause->body);
        tmp = tmp->next;
    }
}

void else_clause_free(struct else_clause *else_clause)
{
    if (!else_clause)
        return;
    while (else_clause != NULL)
    {
        struct else_clause *tmp = else_clause->next;
        list_free(else_clause->body);
        list_free(else_clause->condition);
        free(else_clause);
        else_clause = tmp;
    }
}

struct if_clause *if_clause_create(struct list *condition, struct list *body,
                                   struct else_clause *else_clauses)
{
    struct if_clause *if_clause = calloc(1, sizeof(struct if_clause));
    if (!if_clause)
        return NULL;
    if_clause->base.type = IF_CLAUSE;
    if_clause->condition = condition;
    if_clause->body = body;
    if_clause->else_clauses = else_clauses;

    return if_clause;
}

void if_clause_print(const struct if_clause *if_clause)
{
    printf("if ");
    list_print(if_clause->condition);
    printf("\n");
    list_print(if_clause->body);
    printf("\n");
    else_clause_print(if_clause->else_clauses);
}

void if_clause_free(struct if_clause *if_clause)
{
    if (!if_clause)
        return;
    list_free(if_clause->condition);
    list_free(if_clause->body);
    else_clause_free(if_clause->else_clauses);
    free(if_clause);
}
