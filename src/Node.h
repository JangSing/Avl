#ifndef Node_H
#define Node_H

typedef struct Node_t Node;

struct Node_t{
  Node *left;
  Node *right;
  int weight;
  int data;
};

typedef struct {
  Node *head;
  int length;
}Tree;


Tree *initiallizeTree();

Node *createNode(Node *leftData,int root,Node *rightData);

Tree *createTree();

#endif // Node_H
