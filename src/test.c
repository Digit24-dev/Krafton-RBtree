#include "rbtree.h"
#include <stdio.h>
#include <stdlib.h>

void printTree2(rbtree *t, node_t *node){
    if(node== NULL || node == t->nil) return;
    char *color_str;
    if (node->color == RBTREE_RED) {
        color_str = "R";
    } else {
        color_str = "B";
    }
    printf("%d(%s) ", node->key, color_str);
    printTree2(t,node->left);
    printTree2(t,node->right);
}

void printTree(rbtree *t, node_t *cur, int level, int isLeft) {
    if (cur == t->nil) {
        return;
    }

    // 오른쪽 자식 노드 출력
    printTree(t, cur->right, level + 1, 0);

    // 현재 노드 출력
    for (int i = 0; i < level - 1; i++) {
        printf("    ");
    }
    if (level > 0) {
        printf(isLeft ? " \\_ " : " /⎺ ");  // 왼쪽 자식일 경우 "\\" 출력, 오른쪽 자식일 경우 "/" 출력
    }
    if (cur->color == RBTREE_RED)
    {
      printf("\x1b[31m%d\x1b[0m\n", cur->key);
    }
    else{
      printf("%d\n", cur->key);
    }

    // 왼쪽 자식 노드 출력
    printTree(t, cur->left, level + 1, 1);
}

int main(int argc, char *argv[])
{
    int choice, value, idx = 0;
    char e;
    node_t *res;
    rbtree *t;
    t = new_rbtree();
    choice = 1;

    while(choice != 0){
        printf("-------------------------------------\n");
        printf("Please input your choice(1/2/3/4/5/0)\n");
        printf("-------------------------------------\n");
        printf("1: rbtree insert\n");
        printf("2: rbtree find\n");
        printf("3: rbtree_erase\n");
        printf("4: rbtree min\n");
        printf("5: rbtree max\n");
        printf("0: Quit;\n");
        printf(": ");
        if(scanf("%d", &choice) > 0)
        {
            switch(choice)
            {
            case 1:
                printf("값을 입력하세요:\n");
                if(scanf("%d", &value)==1){
                    rbtree_insert(t, value);
                    printf("The resulting tree is: \n");
                    // printTree(t,t->root);
                    printTree(t,t->root, idx, 0);
                    printf("\n");
                    ++idx;
                } else {
                    printf("다시 입력하세요");
                }
                break;
            case 2:
                printf("찾을 값을 입력하세요:\n");
                if(scanf("%d", &value)==1){
                    res = rbtree_find(t, (key_t)value);
                    if (res != NULL) { // 찾음
                        printf("The resulting node is: \n");
                        printf("%d", res->key);
                        if (res->color == RBTREE_RED) {
                            printf("(RED)");
                        } else {
                            printf("(BLACK)");
                        }
                        printf("\n");
                    }
                    else { // 못찾음
                        printf("찾을 수 없습니다.\n");
                    }
                } else {
                    printf("다시 입력하세요");
                }
                break;
            case 3:
                printf("지울 값을 입력하세요:\n");
                if(scanf("%d", &value)==1){
                    res = rbtree_find(t, (key_t)value);
                    printf("The erased node is: \n");
                    printf("%d", res->key);
                    if (res->color == RBTREE_RED) {
                        printf("(R)");
                    } else {
                        printf("(B)");
                    }
                    printf("\n");
                    rbtree_erase(t,res);
                    printf("The resulting tree is: \n");
                    // printTree(t,t->root);
                    printTree(t,t->root, idx, 0);
                    printf("\n");
                    --idx;
                } else {
                    printf("다시 입력하세요");
                }
                break;
            case 4:
                res = rbtree_min(t);
                if (res != NULL) {
                    printf("Minimum is %d\n", res->key);
                }
                else {
                    printf("최소값을 찾을 수 없습니다.\n");
                }
                break;
            case 5:
                res = rbtree_max(t);
                if (res != NULL) {
                    printf("Maximum is %d\n", res->key);
                }
                else {
                    printf("최대값을 찾을 수 없습니다.\n");
                }
                break;
            case 0:
                break;
            default:
                printf("Choice unknown;\n");
                break;
            }
        }
        else
        {
            scanf("%c",&e);
        }
    }
    return 0;
}