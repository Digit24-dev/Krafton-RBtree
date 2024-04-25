#include "rbtree.h"

#include <stdlib.h>
#include <stdio.h>
// #include "stack.h"

// #define SUCCESSOR // not define for PREDECESSOR 

#ifdef __USE_STACK__
// if use STACK, allocate one static STACK pointer;
extern static STACK *stack;
#endif

rbtree *new_rbtree(void) {
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  // TODO: initialize struct if needed
  p->nil = (node_t*)calloc(1, sizeof(node_t));
  p->root = p->nil;
  p->nil->color = RBTREE_BLACK;
  p->nil->left = p->nil->right;
  p->nil->right = p->nil->left;

#ifdef __USE_STACK__
  stack = init_stack();
#endif

  return p;
}

#ifdef __USE_STACK__
void delete_rbtree_using_stack(rbtree *t) {
  delete_tree(t);
  free(t->nil);
  free(t);
}
#else
void postOrderDeletion(rbtree *t, node_t *cur) {
  if (cur == t->nil)
    return;
  
  postOrderDeletion(t, cur->left );
  postOrderDeletion(t, cur->right);
  free(cur);
}
#endif

void delete_rbtree(rbtree *t) {
  // TODO: reclaim the tree nodes's memory

#ifdef __USE_STACK__
  delete_rbtree_using_stack(t);
#else
  postOrderDeletion(t, t->root);
#endif

  free(t->nil);
  free(t);
}

void left_rotate(rbtree *t, node_t *x) {
  node_t *y = x->right;
  
  x->right = y->left;
  if (y->left != t->nil)
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
  
  node_t *p = t->root;
  
  while (p != t->nil)
  {
    if (p->key == key)
      break;
    else if (p->key < key)
      {p = p->right;}
    else
      {p = p->left;}
  }

  if (p == t->nil)
    p = NULL;
  
  return p;
}

node_t *rbtree_min(const rbtree *t) {
  // TODO: implement find
  node_t *p = t->root;
  while (p->left != t->nil)
    p = p->left;
  
  return p;
}

node_t *rbtree_max(const rbtree *t) {
  // TODO: implement find
  node_t *p = t->root;
  while(p->right != t->nil)
    p = p->right;

  return p;
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
}

// predecssor
node_t* tree_maximum(rbtree *t, node_t *z) {
  if (z == t->nil) return z;
  node_t *p = z;
  while (p->right != t->nil)
    p = p->right;
  
  return p;
}

// successor
node_t* tree_minimum(rbtree *t, node_t *z) {
  if (z == t->nil) return z;
  node_t *p = z;
  while (p->left != t->nil)
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
      else {
        if (w->right->color == RBTREE_BLACK) {
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
      else {
        if (w->left->color == RBTREE_BLACK) {
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
  }
  x->color = RBTREE_BLACK;
}

int rbtree_erase(rbtree *t, node_t *z) {
  // TODO: implement erase
  // y is a node that might violate the rb-tree rules.
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
  // if node z has two child,
  else {
    
#ifdef SUCCESSOR
    y = tree_minimum(t, z->right);
    x = y->right;

    y_original_color = y->color;

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
#else // PREDECESSOR
    y = tree_maximum(t, z->left);
    x = y->left;

    y_original_color = y->color;

    // if z is child of y
    if (y->parent == z)
      x->parent = y;
    else {
      transplant(t, y, y->left);
      y->left = z->left;
      y->left->parent = y;
    }

    transplant(t, z, y);
    y->right = z->right;
    y->right->parent = y;
    y->color = z->color;
#endif

  }

  if (y_original_color == RBTREE_BLACK)
    delete_fixup(t, x);

  free(z);
  return 0;
}

#ifdef __USE_STACK__
#else
void inOrderTraversal(const rbtree *t, node_t *p, key_t *arr, size_t *idx) {
  if (p == t->nil) return; // O(logN + 1) vs two more compare instructions?

  inOrderTraversal(t, p->left, arr, idx);
  arr[(*idx)++] = p->key;
  inOrderTraversal(t, p->right, arr, idx);
}
#endif

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array
  size_t idx = 0;

#ifdef __USE_STACK__
#else
  inOrderTraversal(t, t->root, arr, &idx);
#endif

  return 0;
}
