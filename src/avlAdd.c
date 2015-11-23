#include "ErrorObject.h"
#include "CException.h"
#include "avlAdd.h"
#include "Node.h"
#include "Rotation.h"
#include <stdlib.h>

int avlAdd(Node **rootPtr,Node *newNode){
  int change=0;
  int balanceBefore;
  if(newNode->data > (*rootPtr)->data){
    if((*rootPtr)->right!=NULL){
      balanceBefore=(*rootPtr)->right->balanceFactor;
      change=avlAdd(&((*rootPtr)->right) , newNode);
      if(change && (*rootPtr)->right->balanceFactor!=balanceBefore)
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
      balanceBefore=(*rootPtr)->left->balanceFactor;
      change=avlAdd(&((*rootPtr)->left) , newNode);
      if(change && (*rootPtr)->left->balanceFactor!=balanceBefore)
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
  
  // Rotation Task starts here
  checkForRotation(rootPtr,NULL);
  
  return (*rootPtr)->balanceFactor;
}



