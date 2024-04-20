#include "rbtree.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

rbtree *new_rbtree(void) {
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  // TODO: initialize struct if needed
  p->nil = (node_t*)calloc(1, sizeof(node_t));
  p->root = p->nil;
  p->nil->color = RBTREE_BLACK;

  return p;
}

void postOrderDeletion(rbtree *t, node_t *cur) {
  if (cur == t->nil) {
    return;
  }
  
  postOrderDeletion(t, cur->left );
  postOrderDeletion(t, cur->right);
  free(cur);
}

void delete_rbtree(rbtree *t) {
  // TODO: reclaim the tree nodes's memory
  postOrderDeletion(t, t->root);
  free(t->nil);
  free(t);
}

void left_rotate(rbtree *t, node_t *x) {
  node_t *y = x->right;
  
  x->right = y->left;
  if (x->right != t->nil) 
    y->left->parent = x;
  else if (x == x->parent->left)
    x->parent->left = y;
  else
    x->parent->right = y;
  y->left = x;
  x->parent = y;
}

void right_rotate(rbtree *t, node_t *x) {
  node_t *y = x->parent;
  
  y->left = x->right;
  if (y->left != t->nil)
    x->right->parent = y;
  else if (y == y->parent->left)
    y->parent->left = x;
  else
    y->parent->right = x;
  x->right = y;
  y->parent = x;
}

void insert_fixup(rbtree *t, node_t *z) {
  node_t *uncle;
  while (z->parent->color == RBTREE_RED)
  {
    // if z's parent is grand parent's left node,
    if (z->parent == z->parent->parent->left) {
      uncle = z->parent->parent->right;

      if (uncle->color == RBTREE_RED) {
        z->parent->color = RBTREE_BLACK;
        uncle->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        z = z->parent->parent;
      }
      // if z is parent's right node,
      else if (z == z->parent->right) {
        z = z->parent;
        // LEFT-ROTATE
        // ***********
        left_rotate(t, z);
      }
      z->parent->color = RBTREE_BLACK;
      z->parent->parent->color = RBTREE_RED;
      right_rotate(t, z);
    }
    // if z's parent is grand parent's right node,
    else {
      uncle = z->parent->parent->left;

      if (uncle->color == RBTREE_RED) {
        z->parent->color = RBTREE_BLACK;
        uncle->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        z = z->parent->parent;
      }
      // if z is parent's left node,
      else if (z == z->parent->left) {
        z = z->parent;
        // LEFT-ROTATE
        // ***********
        right_rotate(t, z);
      }
      z->parent->color = RBTREE_BLACK;
      z->parent->parent->color = RBTREE_RED;
      right_rotate(t, z);
    }
  }

  t->root->color = RBTREE_BLACK;
}

node_t *rbtree_insert(rbtree *t, const key_t key) {
  // TODO: implement insert
  node_t* newNode = (node_t*)calloc(1, sizeof(node_t));
  newNode->key = key;
  newNode->color = RBTREE_RED;

  // if root is not NULL
  // find a node to insert key.

  node_t *y = t->nil;
  node_t *x = t->root;

  while (x != t->nil)
  {
    y = x;
    if (key < x->key)       // to right subtree
      x = x->left;
    else                     // to left subtree
      x = x->right;
  }

  // p is null
  newNode->parent = y;

  if (y == t->nil)
    t->root = newNode;
  else if (newNode->key < y->key)
    y->left = newNode;
  else
    y->right = newNode;
  
  newNode->parent = t->nil;
  newNode->left = t->nil;
  newNode->right = t->nil;

  insert_fixup(t, newNode);

  return t->root;
}

node_t *rbtree_insert_wasMine(rbtree *t, const key_t key) {
  // TODO: implement insert
  node_t* newNode = (node_t*)calloc(1, sizeof(node_t));
  newNode->key = key;
  newNode->color = RBTREE_RED;
  newNode->parent = t->nil;
  newNode->left = t->nil;
  newNode->right = t->nil;

  // if root is NULL
  if (t->root == t->nil) {
    t->root = newNode;
    newNode->color = RBTREE_BLACK;
    newNode->parent = t->nil;
    newNode->left = t->nil;
    newNode->right = t->nil;
  } else {
    // if root is not NULL
    // find a node to insert key.

    node_t *y = t->nil;
    node_t *x = t->root;

    while (x != t->nil)
    {
      y = x;
      if (key < x->key)       // to right subtree
        x = x->left;
      else                     // to left subtree
        x = x->right;
    }

    // p is null
    newNode->parent = y;

    if (y == t->nil)
      t->root = newNode;
    else if (newNode->key < y->key)
      y->left = newNode;
    else
      y->right = newNode;
  }

  insert_fixup(t, newNode);

  return t->root;
}

node_t *rbtree_find(const rbtree *t, const key_t key) {
  // TODO: implement find
  if (t->root == t->nil) return t->nil;
  
  node_t *p = t->root;

  while (p != t->nil)
  {
    if (p->key < key)
      p = p->right;
    else if (p->key > key)
      p = p->left;
    else
      break;
  }
  
  printf("%d \n", p->key);

  return p;
}

node_t *rbtree_min(const rbtree *t) {
  // TODO: implement find
  return t->root;
}

node_t *rbtree_max(const rbtree *t) {
  // TODO: implement find
  return t->root;
}

// u is to delete, v is where to delete
void transplant(rbtree *t, node_t *u, node_t *v) {
  if (u->parent == t->nil)
    t->root = v;
  else if (u == u->parent->left)
    u->parent->left = v;
  else
    u->parent->right = v;
    
  v->parent = u->parent;
  free(u);
}

// successor
node_t* tree_minimum(rbtree *t, node_t *z) {
  node_t *p = z;
  while (p != t->nil)
    p = p->left;

  return p;
}

void delete_fixup(rbtree *t, node_t *x) {
  node_t *w;
  while (x != t->root && x->color == RBTREE_BLACK)
  {
    // if x is parent's left child
    if (x == x->parent->left) {
      w = x->parent->right;
      if (w->color == RBTREE_RED) {
        w->color = RBTREE_BLACK;
        x->parent->color = RBTREE_RED;
        left_rotate(t, x->parent);
        w = x->parent->right;
      }

      if (w->left->color == RBTREE_BLACK && w->right->color == RBTREE_BLACK) {
        w->color = RBTREE_RED;
        x = x->parent;
      }
      else if (w->right->color == RBTREE_BLACK) {
        w->left->color = RBTREE_BLACK;
        w->color = RBTREE_RED;
        right_rotate(t, w);
        w = x->parent->right;
      }

      w->color = x->parent->color;
      x->parent->color = RBTREE_BLACK;
      w->right->color = RBTREE_BLACK;
      left_rotate(t, x->parent);
      x = t->root;
    }
    // if x is parent's right child
    else {
      w = x->parent->left;
      if (w->color == RBTREE_RED) {
        w->color = RBTREE_BLACK;
        x->parent->color = RBTREE_RED;
        right_rotate(t, x->parent);
        w = x->parent->left;
      }

      if (w->right->color == RBTREE_BLACK && w->left->color == RBTREE_BLACK) {
        w->color = RBTREE_RED;
        x = x->parent;
      }
      else if (w->left->color == RBTREE_BLACK) {
        w->right->color = RBTREE_BLACK;
        w->color = RBTREE_RED;
        left_rotate(t, w);
        w = x->parent->left;
      }

      w->color = x->parent->color;
      x->parent->color = RBTREE_BLACK;
      w->left->color = RBTREE_BLACK;
      right_rotate(t, x->parent);
      x = t->root;
    }
  }
  x->color = RBTREE_BLACK;
}

int rbtree_erase(rbtree *t, node_t *z) {
  // TODO: implement erase
  // y is node that might violate the rb-tree rules.
  node_t *y = z, *x;
  color_t y_original_color = y->color;

  // if node z has only one child,
  if (z->left == t->nil) {
    x = z->right;
    transplant(t, z, z->right);
  }
  else if (z->right == t->nil) {
    x = z->left;
    transplant(t, z, z->left);
  }
  // if node z has both child,
  else {
    y_original_color = y->color;
    x = y->right;
    
    // if z is child of y
    if (y->parent == z)
      x->parent = y;
    else {
      y = tree_minimum(t, z->right);
      y_original_color = y->color;
      x = y->right;

      if (y->parent == z)
        x->parent = y;
      else {
        transplant(t, y, y->right);
        y->right = z->right;
        y->right->parent = y;
      }
      transplant(t, z, y);
      y->left = z->left;
      y->left->parent = y;
      y->color = z->color;
    }
  }

  if (y_original_color == RBTREE_BLACK)
    delete_fixup(t, x);

  return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array
  return 0;
}
