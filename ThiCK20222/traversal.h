#ifndef __TRAVERSAL_H__
#define __TRAVERSAL_H__
#include "tree.h"
// #include "queue.h"

void inorderprint(tree_t tree);
void postorderprint(tree_t tree);
void preorderprint(tree_t tree);
void f_inorderprint(tree_t tree, FILE *file);
void check_inorderprint(tree_t tree, char name[]);
// void breadth_first (tree_t tree);

#endif