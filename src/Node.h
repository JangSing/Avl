#ifndef Node_H
#define Node_H

typedef struct Node_t Node;
struct Node_t{
  Node *left;
  Node *right;
  int balanceFactor;
  int data;
};

#endif // Node_H
