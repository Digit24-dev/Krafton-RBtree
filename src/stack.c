#include <stdlib.h>
#include <stdio.h>
#include "stack.h"
#include "rbtree.h"

/*
스택을 어디에서 생성할 것인가?

1. malloc으로 할당한 STACK을 가리키는 STACK*를 전역변수로 선언. -> 매개변수로 계속해서 포인터 전달해야 함.
2. 호출 시마다 새로 생성 -> malloc 계속해서 호출해야 함.
*/

/// @brief init STACK returning it's pointer.
/// @return STACK* (pointer)
STACK* init_stack() {
    STACK *ret = (STACK*)malloc(sizeof(STACK));
    ret->top = NULL;
    return ret;
}

void postOrderTraversal(rbtree *t) {
    if (t->root == NULL) return;

    node_t *p = t->root;
    STACK *stack = (STACK*)malloc(sizeof(STACK));
    stack->top = NULL;

    int flag = 0;

    while (!flag)
    {
        if (p != NULL) {
            push(stack, p);
            p = p->left;
        }
        else {
            if(!isEmpty(stack)) {
                printf("%d ", peek(stack)->item.key);
                p = pop(stack);
                p = p->right;
            }
            else {
                flag = 1;
            }
        }
    }
    
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
