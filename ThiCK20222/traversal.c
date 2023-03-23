#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "traversal.h"

void inorderprint(tree_t tree)
{
    if (tree != NULL)
    {
        inorderprint(tree->left);
        printf("%s\n", tree->element.maYeuCau);
        inorderprint(tree->right);
    }
}

void postorderprint(tree_t tree)
{
    if (tree != NULL)
    {
        postorderprint(tree->left);
        postorderprint(tree->right);
        printf("%s ", tree->element.maYeuCau);
    }
}

void preorderprint(tree_t tree)
{
    if (tree != NULL)
    {
        printf("%s ", tree->element.maYeuCau);
        preorderprint(tree->left);
        preorderprint(tree->right);
    }
}

void f_inorderprint(tree_t tree, FILE *file)
{
    if (tree != NULL)
    {
        f_inorderprint(tree->left, file);
        elmType temp = tree->element;
        fprintf(file, "%s %d %d %s %d-%d-%d %d\n", temp.maYeuCau, temp.soNguoi, temp.soPhong, temp.maKhachSan, temp.DD, temp.MM, temp.YYYY, temp.kids);
        f_inorderprint(tree->right, file);
    }
}

void check_inorderprint(tree_t tree, char maYeuCau[])
{
    if (tree != NULL)
    {
        check_inorderprint(tree->left, maYeuCau);
        if (strcmp(maYeuCau, tree->element.maYeuCau) == 0)
            printf("%s\n", tree->element.maYeuCau);
        check_inorderprint(tree->right, maYeuCau);
    }
}

// Pseudo Algorithm
//  void breadth_first (tree_t tree) {
//      Queue *queue;
//      if (tree!=NULL) {
//          EnQueue(tree,queue);
//          while (!Empty_Queue(*queue)) {
//              tree = DeQueue(queue);
//              printf("%s",tree->element.maYeuCau);
//              if (tree->left!=NULL)
//                  EnQueue(tree->left,queue);
//              if (tree->right!=NULL)
//                  EnQueue(tree->right,queue);
//          }
//      }
//  }