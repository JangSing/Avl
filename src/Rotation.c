#include "Rotation.h"
#include <stdlib.h>
#include <stdio.h>

// void leftRotation(Tree *tree,Node *pivotNode){
  // Node *tempNode;
  
  // tempNode=pivotNode->right;
  
  // pivotNode->right=tempNode->left;
  // tempNode->left=pivotNode;
  
  // tree->head=tempNode;
  
// }

Node *leftRotation(Node *head){
  Node *tempNode;
  
  tempNode=head->right;
  
  head->right=tempNode->left;
  tempNode->left=head;
  
  head=tempNode;
  
  return head;
}

Node *rightRotation(Node *head){
  Node *tempNode;
  
  tempNode=head->left;
  
  head->left=tempNode->right;
  tempNode->right=head;
  
  head=tempNode;
  
  return head;
}

Node *leftRightRotation(Node *head){  
  Node *tempTree;
  tempTree=head->left;
  tempTree=leftRotation(tempTree);
  head->left=tempTree;
  head=rightRotation(head);
  
  return head;
  free(tempTree);
}

Node *rightLeftRotation(Node *head){  
  Node *tempTree;
  tempTree=head->right;
  tempTree=rightRotation(tempTree);
  head->right=tempTree;
  head=leftRotation(head);
  
  return head;
  free(tempTree);
}


