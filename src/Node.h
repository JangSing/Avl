#ifndef Node_H
#define Node_H

typedef struct Node_t Node;
struct Node_t{
  Node *left;
  Node *right;
  int balanceFactor;
  int data;
};

Node *createNode(Node *leftData,int root,Node *rightData);

Node *createTree();

#endif // Node_H
