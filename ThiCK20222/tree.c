#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

int compare(elmType a, elmType b)
{
  return strcmp(a.maYeuCau, b.maYeuCau);
}

void makeNullTree(tree_t T) { T = NULL; }
int isEmptyTree(tree_t T) { return T == NULL; }

void freeTree(tree_t Tree)
{
  if (Tree == NULL)
    return;
  freeTree(LeftChild(Tree));
  freeTree(RightChild(Tree));
  free(Tree);
  return;
}

node_t *create_node(elmType NewData)
{
  node_t *N = (node_t *)malloc(sizeof(node_t));
  if (N != NULL)
  {
    N->left = NULL;
    N->right = NULL;
    N->element = NewData;
    // N->element.count = 1;
  }
  return N;
}

// InsertNode(x,&tree);
void InsertNode(elmType x, tree_t *root)
{
  if (*root == NULL)
  { /* Create a new node for element x */
    // printf("insert %d\n", x);
    *root = create_node(x);
  }
  else if (compare(x, (*root)->element) < 0)
    InsertNode(x, &((*root)->left));
  else if (compare(x, (*root)->element) > 0)
    InsertNode(x, &((*root)->right));
}

void InsertandCount(elmType x, tree_t *root)
{
  if (*root == NULL)
  {
    *root = create_node(x);
  }
  else if (compare(x, (*root)->element) < 0)
    InsertandCount(x, &((*root)->left));
  else if (compare(x, (*root)->element) > 0)
    InsertandCount(x, &((*root)->right));
  // else if (compare(x,(*root)->element) == 0) ((*root)->element.count)++;
}

int countLeftChildren(tree_t Tree)
{
  if (isEmptyTree(Tree))
    return 0;
  int leftChildRight = countLeftChildren(RightChild(Tree));
  int leftChildLeft = isEmptyTree(LeftChild(Tree)) ? 0 : (1 + countLeftChildren(LeftChild(Tree)));
  // if(LeftChild(Tree) == NULL) return 0;
  return leftChildRight + leftChildLeft;
}

int countRightChildren(tree_t Tree)
{
  if (isEmptyTree(Tree))
    return 0;
  int rightChildRight = isEmptyTree(RightChild(Tree)) ? 0 : (1 + countRightChildren(RightChild(Tree)));
  int rightChildLeft = countRightChildren(LeftChild(Tree));
  // if(LeftChild(Tree) == NULL) return 0;
  return rightChildRight + rightChildLeft;
}

int countInternalNodes(tree_t Tree)
{
  if (Tree == NULL)
    return 0;
  int count = nb_nodes(Tree) - countLeaves(Tree) - 1;
  return ((count > 0) ? count : 0);
}

int countLeaves(tree_t Tree)
{
  if (Tree == NULL)
    return 0;
  if (IsLeaf(Tree))
    return 1;
  int leaves = countLeaves(LeftChild(Tree)) + countLeaves(RightChild(Tree));
  return leaves;
}

int treeHeight(tree_t Tree)
{
  if (Tree == NULL)
    return 0;
  int leftHeight = treeHeight(LeftChild(Tree));
  int rightHeight = treeHeight(RightChild(Tree));
  int childHeight = (leftHeight > rightHeight) ? leftHeight : rightHeight;
  return (childHeight + 1);
}

tree_t LeftChild(tree_t n)
{
  if (n != NULL)
    return n->left;
  else
    return NULL;
}

tree_t RightChild(tree_t n)
{
  if (n != NULL)
    return n->right;
  else
    return NULL;
}

int IsLeaf(tree_t n)
{
  if (n != NULL)
    return (LeftChild(n) == NULL) && (RightChild(n) == NULL);
  else
    return -1;
}

int nb_nodes(tree_t T)
{
  if (isEmptyTree(T))
    return 0;
  else
    return 1 + nb_nodes(LeftChild(T)) + nb_nodes(RightChild(T));
}

tree_t createfrom2(elmType v, tree_t l, tree_t r)
{
  node_t *N = (node_t *)malloc(sizeof(node_t));
  N->element = v;
  N->left = l;
  N->right = r;
  return N;
}

tree_t Add_Left(tree_t Tree, elmType NewData)
{
  node_t *NewNode = create_node(NewData);
  if (NewNode == NULL)
    return (NewNode);
  if (Tree == NULL)
    Tree = NewNode;
  else
  {
    node_t *Lnode = Tree;
    while (Lnode->left != NULL)
      Lnode = Lnode->left;
    Lnode->left = NewNode;
  }
  return (NewNode);
}

tree_t Add_Right(tree_t Tree, elmType NewData)
{
  node_t *NewNode = create_node(NewData);
  if (NewNode == NULL)
    return (NewNode);
  if (Tree == NULL)
    Tree = NewNode;
  else
  {
    node_t *Rnode = Tree;
    while (Rnode->right != NULL)
      Rnode = Rnode->right;
    Rnode->right = NewNode;
  }
  return (NewNode);
}

void prettyPrint(tree_t tree)
{
  static char prefix[200] = "    ";
  char *prefixend = prefix + strlen(prefix);
  if (tree != NULL)
  {
    printf("%s", tree->element.maYeuCau);
    if (tree->left != NULL)
      if (tree->right == NULL)
      {
        printf("\304");
        strcat(prefix, "     ");
      }
      else
      {
        printf("\302");
        strcat(prefix, "\263    ");
      }
    prettyPrint(tree->left);
    *prefixend = '\0';
    if (tree->right != NULL)
      if (tree->left != NULL)
      {
        printf("\n%s", prefix);
        printf("\300");
      }
      else
        printf("\304");
    strcat(prefix, "     ");
    prettyPrint(tree->right);
  }
}

elmType deleteMin(tree_t *root)
{
  if ((*root)->left == NULL)
  {
    elmType k = (*root)->element;
    (*root) = (*root)->right;
    return k;
  }
  else
    return deleteMin(&(*root)->left);
}

// deleteNode(x,&tree);
void deleteNode(elmType x, tree_t *root)
{
  if (*root != NULL)
    if (compare(x, (*root)->element) < 0)
      deleteNode(x, &(*root)->left);
    else if (compare(x, (*root)->element) > 0)
      deleteNode(x, &(*root)->right);
    else if (((*root)->left == NULL) && ((*root)->right == NULL))
      *root = NULL;
    else if ((*root)->left == NULL)
      *root = (*root)->right;
    else if ((*root)->right == NULL)
      *root = (*root)->left;
    else
      (*root)->element = deleteMin(&(*root)->right);
}

tree_t search(elmType x, tree_t root)
{
  if (root == NULL)
    return NULL;                           // not found
  else if (compare(x, root->element) == 0) /* found x */
    return root;
  else if (compare(x, root->element) > 0)
    // continue searching in the right sub tree
    return search(x, root->right);
  else
  {
    // continue searching in the left sub tree
    return search(x, root->left);
  }
}

// char delimiter[]=" !\"#$%&\'()*+,-./:;<=>?@[\\]^_`{|}~\n";
//     char *token;
//     char buffer[1000];

//     while (fgets(buffer,sizeof(buffer),file1)!=NULL) {
//         token = strtok(buffer,delimiter);
//         while (token != NULL) {
//             fprintf(file2,"%s\n",token);
//             token = strtok(NULL,delimiter);
//         }
//     }