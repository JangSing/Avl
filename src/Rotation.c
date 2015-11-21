#include "Rotation.h"
#include <stdlib.h>
#include <stdio.h>

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

void checkForRotation(Node **rootPtr,int *heightChange){
  if((*rootPtr)->balanceFactor>1){
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
    if(heightChange!=NULL)
      *heightChange=1;
  }
  else if((*rootPtr)->balanceFactor<-1){
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
    if(heightChange!=NULL)
      *heightChange=1;
  }



}
