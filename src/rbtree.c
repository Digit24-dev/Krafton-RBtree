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
  p->nil->left = p->nil->right;
  p->nil->right = p->nil->left;

  return p;
}

void postOrderDeletion(rbtree *t, node_t *cur) {
  if (cur == t->nil)
    return;
  
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

  y->parent = x->parent;

  if (x->parent == t->nil)
    t->root = y;
  else if (x == x->parent->left)
    x->parent->left = y;
  else
    x->parent->right = y;

  y->left = x;
  x->parent = y;
}

void right_rotate(rbtree *t, node_t *x) {
  node_t *y = x->left;
  
  x->left = y->right;
  if (y->right != t->nil) 
    y->right->parent = x;

  y->parent = x->parent;

  if (x->parent == t->nil)
    t->root = y;
  else if (x == x->parent->right)
    x->parent->right = y;
  else
    x->parent->left = y;

  y->right = x;
  x->parent = y;
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
      else {
        if (z == z->parent->right) {
          z = z->parent;
          // LEFT-ROTATE
          left_rotate(t, z);
        }
        z->parent->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        right_rotate(t, z->parent->parent);
      }
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
      else {
        if (z == z->parent->left) {
          z = z->parent;
          // RIGHT-ROTATE
          right_rotate(t, z);
        }
        z->parent->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        left_rotate(t, z->parent->parent);
      }
    }
  }

  t->root->color = RBTREE_BLACK;
}

node_t *rbtree_insert(rbtree *t, const key_t key) {
  // TODO: implement insert

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

  node_t* newNode = (node_t*)calloc(1, sizeof(node_t));

  newNode->parent = y;
  newNode->color = RBTREE_RED;

  if (y == t->nil) {
    t->root = newNode;
    newNode->color = RBTREE_BLACK;
  }
  else if (key < y->key)
    y->left = newNode;
  else
    y->right = newNode;
  
  newNode->key = key;
  newNode->left = t->nil;
  newNode->right = t->nil;

  insert_fixup(t, newNode);

  return t->root;
}

node_t *rbtree_find(const rbtree *t, const key_t key) {
  // TODO: implement find
  if (t->root == t->nil) return NULL;
  printf("to find : %d \n", key);
  
  node_t *p = t->root;
  // printf("==== find in ====\n");
  while (p != t->nil)
  {
    printf("current key : %d\n", p->key);

    if (p->key == key)
      break;
    else if (p->key < key)
      {p = p->right; printf("heading to right\n");}
    else
      {p = p->left; printf("heading to left\n");}
  }

  // printf("==== find out ====\n");
  if (p == t->nil) {
    p = NULL;
    printf("nullify \n");
  }
  
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
  printf("==== transplant in ====\n");
  if (u->parent == t->nil)
    t->root = v;
  else if (u == u->parent->left)
    u->parent->left = v;
  else
    u->parent->right = v;
    
  v->parent = u->parent;
  printf("%d ,,\n", u->key);
  free(u);
  printf("==== transplant out ====\n");
}

// successor
node_t* tree_minimum(rbtree *t, node_t *z) {
  printf("==== tree minimum ====\n");
  node_t *p = z;
  while (p->left != t->nil)
    p = p->left;

  return p;
}

void delete_fixup(rbtree *t, node_t *x) {
  printf("==== fixup in ====\n");
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
  printf("==== init erase ==== \n");

  // if node z has only one child,
  if (z->left == t->nil) {
    x = z->right;
    transplant(t, z, z->right);
  }
  else if (z->right == t->nil) {
    x = z->left;
    transplant(t, z, z->left);
  }
  // if node z has two child,
  else {
    y = tree_minimum(t, z->right);
    y_original_color = y->color;
    x = y->right;
    
    // if z is child of y
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

  if (y_original_color == RBTREE_BLACK)
    delete_fixup(t, x);

  return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array
  return 0;
}
