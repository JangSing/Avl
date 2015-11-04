#include "ErrorObject.h"
#include "CException.h"
#include "Avl.h"
#include "Node.h"
#include <stdlib.h>

int avlAdd(Node **rootPtr,Node *newNode){
  int change=0;
  if(newNode->data > (*rootPtr)->data){
    if((*rootPtr)->right!=NULL){
      change=avlAdd(&((*rootPtr)->right) , newNode);
      if(change)
        (*rootPtr)->balanceFactor++;
    }
    else{
      (*rootPtr)->right=newNode;
      (*rootPtr)->balanceFactor++;
      if((*rootPtr)->left==NULL)
        return 1;
      else
        return 0;
    }
  }
  else if (newNode->data < (*rootPtr)->data){
    if((*rootPtr)->left!=NULL){
      change=avlAdd(&((*rootPtr)->left) , newNode);
      if(change)
        (*rootPtr)->balanceFactor--;
    }
    else{
      (*rootPtr)->left=newNode;
      (*rootPtr)->balanceFactor--;
      if((*rootPtr)->right==NULL)
        return 1;
      else
        return 0;
    }
  }
  else
    throwError(ERR_REPEATED_NODE,"The node added has already in the avl tree");

}



int avlRemove(Node **rootPtr,int data){}