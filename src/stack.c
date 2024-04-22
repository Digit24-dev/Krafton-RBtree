#pragma once

#include <stdlib.h>
#include <stdio.h>
#include "stack.h"
#include "rbtree.h"

STACK* init_stack() {
    STACK *ret = (STACK*)malloc(sizeof(STACK));
    ret->top = NULL;

    return ret;
}

void delete_tree(STACK *st) {
    if (isEmpty(st)) return;
    while (!isEmpty(st))
    {
        pop(st);
    }
    free(st);
}

int push(STACK *stack, node_t *node){
    // 0 : malloc error
    // 1 : success

    StackNode *temp;
    temp = (StackNode*)malloc(sizeof(StackNode));

    if (temp == NULL) return 0;

    temp->data = node;

    if (stack->top == NULL)
    {
        stack->top = temp;
        temp->next = NULL;
    } 
    else 
    {
        temp->next = stack->top;
        stack->top = temp;
    }
    return 1;
}

treeNode *pop(STACK *s) {
    StackNode *temp, *t;
    treeNode *ptr;
    ptr = NULL;

    t = s->top;
    if (t != NULL)
    {
        temp = t->next;
        ptr = t->data;

        s->top = temp;
        free(t);
        t = NULL;
    }
    return ptr;
}

treeNode *peek(STACK *s) {
    StackNode *p;
    p = s->top;
    if (p != NULL)
        return p->data;
    else
        return NULL;
}

int isEmpty(STACK *s) {
    if (s->top == NULL)
        return 1;
    else
        return 0;
}
