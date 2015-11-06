#include "ErrorObject.h"
#include "CException.h"
#include "Avl.h"
#include "Node.h"
#include "Rotation.h"
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
  
  // Rotation Task starts here
  if((*rootPtr)->balanceFactor==2){
    if((*rootPtr)->right->balanceFactor<0){
      *rootPtr=rightLeftRotation(*rootPtr);
      switch((*rootPtr)->balanceFactor){
        case 1:
          (*rootPtr)->balanceFactor=0;
          (*rootPtr)->left->balanceFactor=-1;
          (*rootPtr)->right->balanceFactor=0;break;
        case -1:
          (*rootPtr)->balanceFactor=0;
          (*rootPtr)->left->balanceFactor=0;
          (*rootPtr)->right->balanceFactor=1;break;
        default:
          (*rootPtr)->balanceFactor=0;
          (*rootPtr)->left->balanceFactor=0;
          (*rootPtr)->right->balanceFactor=0;break;
      }
    }
    else{
      *rootPtr=leftRotation(*rootPtr);
      (*rootPtr)->balanceFactor--;
      if((*rootPtr)->balanceFactor=0)
        (*rootPtr)->left->balanceFactor--;
      else
        (*rootPtr)->left->balanceFactor-=2;
    }
  }
  else if((*rootPtr)->balanceFactor==-2){
    if((*rootPtr)->left->balanceFactor>0){
      *rootPtr=leftRightRotation(*rootPtr);
      switch((*rootPtr)->balanceFactor){
        case 1:
          (*rootPtr)->balanceFactor=0;
          (*rootPtr)->left->balanceFactor=0;
          (*rootPtr)->right->balanceFactor=1;break;
        case -1:
          (*rootPtr)->balanceFactor=0;
          (*rootPtr)->left->balanceFactor=-1;
          (*rootPtr)->right->balanceFactor=0;break;
        default:
          (*rootPtr)->balanceFactor=0;
          (*rootPtr)->left->balanceFactor=0;
          (*rootPtr)->right->balanceFactor=0;break;
      }
    }
    else{
      *rootPtr=rightRotation(*rootPtr);
      (*rootPtr)->balanceFactor--;
      if((*rootPtr)->balanceFactor=0)
        (*rootPtr)->right->balanceFactor++;
      else
        (*rootPtr)->right->balanceFactor +=2;
    }
  }
}

int avlRemove(Node **rootPtr,int data){}