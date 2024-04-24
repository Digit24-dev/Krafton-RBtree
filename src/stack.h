#pragma once

#ifndef _STACK_H_
#define _STACK_H_

#include <stddef.h>
#include "rbtree.h"

typedef struct _node
{
    node_t item;
    struct _node *next;
} treeNode;

typedef struct _stackNode
{
    treeNode *data;
    struct _stackNode *next;
} StackNode;

typedef struct _Stack
{
    StackNode *top;
} STACK;

int push(STACK *stack, node_t *node);
treeNode *pop(STACK *s);
treeNode *peek(STACK *s);
int isEmpty(STACK *s);
STACK* init_stack();
// void delete_tree(STACK *st);
void postOrderTraversal(rbtree *t);

#endif  // _STACK_H_