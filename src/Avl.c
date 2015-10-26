#include "ErrorObject.h"
#include "CException.h"
#include "Avl.h"
#include "Node.h"
#include <stdlib.h>

int balanceFactor=0;

int avlAdd(Node **rootPtr,Node *newNode){
  
  if(newNode->data > (*rootPtr)->data){
    if((*rootPtr)->right!=NULL)
      balanceFactor=avlAdd(&((*rootPtr)->right) , newNode);
    else{
      (*rootPtr)->right=newNode;
      if((*rootPtr)->left==NULL)
        return (balanceFactor+1);
      else 
        return balanceFactor;
    }
  }
  else if (newNode->data < (*rootPtr)->data){
    if((*rootPtr)->left!=NULL)
      balanceFactor=avlAdd(&((*rootPtr)->left) , newNode);
    else{
      (*rootPtr)->left=newNode;
      if((*rootPtr)->right==NULL)
        return (balanceFactor-1);
      else 
        return balanceFactor;
    }
  }
  else 
    throwError(ERR_REPEATED_NODE,"The newNode data has already in the avl tree");
  return balanceFactor;
}

int avlRemove(Node **rootPtr,int data){
}