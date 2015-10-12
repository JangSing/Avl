#include "Rotation.h"
#include <stdlib.h>
#include <stdio.h>

void leftRotation(Tree *tree,Node *pivotNode){
  Node *tempNode;
  
  tempNode=pivotNode->right;
  
  pivotNode->right=tempNode->left;
  tempNode->left=pivotNode;
  
  tree->head=tempNode;
  
}

void rightRotation(Tree *tree,Node *pivotNode){
  Node *tempNode;
  
  tempNode=pivotNode->left;
  
  pivotNode->left=tempNode->right;
  tempNode->right=pivotNode;
  
  tree->head=tempNode;
}

void leftRightRotation(Tree *tree,Node *pivotNode1,Node *pivotNode2){
  Tree *tempTree;
  tempTree->head=pivotNode2;
  leftRotation(tempTree,pivotNode2);
  tree->head->left=tempTree->head;
  rightRotation(tree,pivotNode1);
  
  free(tempTree);
}

void rightLeftRotation(Tree *tree,Node *pivotNode1,Node *pivotNode2){  
  Tree *tempTree;
  tempTree->head=pivotNode2;
  rightRotation(tempTree,pivotNode2);
  tree->head->right=tempTree->head;
  leftRotation(tree,pivotNode1);
  
  free(tempTree);
}
