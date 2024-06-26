// #pragma once

#ifndef _RBTREE_H_
#define _RBTREE_H_

#include <stddef.h>
// #include "stack.h"
// #define __USE_STACK__ // comment when you don't use stack version.

typedef enum { RBTREE_RED, RBTREE_BLACK } color_t;

typedef int key_t;

typedef struct node_t {
  color_t color;
  key_t key;
  struct node_t *parent, *left, *right;
} node_t;

typedef struct {
  node_t *root;
  node_t *nil;  // for sentinel
} rbtree;

rbtree *new_rbtree(void);
void delete_rbtree(rbtree *);

node_t *rbtree_insert(rbtree *, const key_t);
node_t *rbtree_find(const rbtree *, const key_t);
node_t *rbtree_min(const rbtree *);
node_t *rbtree_max(const rbtree *);
int rbtree_erase(rbtree *, node_t *);

void left_rotate(rbtree *t, node_t *x);
void right_rotate(rbtree *t, node_t *x);
void insert_fixup(rbtree *t, node_t *z);
void delete_rbtree(rbtree *t);
void transplant(rbtree *t, node_t *u, node_t *v);
node_t* tree_minimum(rbtree *t, node_t *z);
void delete_fixup(rbtree *t, node_t *x);

int rbtree_to_array(const rbtree *, key_t *, const size_t);

#endif  // _RBTREE_H_
