#include "ErrorObject.h"
#include "CException.h"
#include "avlRemove.h"
#include "Node.h"
#include "Rotation.h"

#include <stdio.h>
#include <stdlib.h>

Node *avlGetReplacer(Node **rootPtr,int *heightChange){
  Node *replaceNode;
  int currentChange=0;

  if(*rootPtr==NULL){
    return NULL;
  }
  else if((*rootPtr)->left==NULL){
    replaceNode=*rootPtr;
    *rootPtr=(*rootPtr)->right;
    *heightChange=1;
    return replaceNode;
  }
  else{
    if((*rootPtr)->left->left!=NULL){
      replaceNode=avlGetReplacer(&((*rootPtr)->left),heightChange);
      if(*heightChange)
        (*rootPtr)->balanceFactor++;
      return replaceNode;
    }
    else{
      if((*rootPtr)->right==NULL){
        *heightChange=1;
      }
      replaceNode=(*rootPtr)->left;
      (*rootPtr)->left=avlGetReplacer(&((*rootPtr)->left->right),heightChange);
      if((*rootPtr)->right!=NULL){
        if((*rootPtr)->right->left!=NULL || (*rootPtr)->right->right!=NULL)
          *heightChange=0;
      }
      (*rootPtr)->balanceFactor++;

      return replaceNode;
    }
  }
}

Node *avlRemove(Node **rootPtr,int data, int *heightChange){
  Node *removeNode,*replaceNode;
  int currentChange=0;

  if(data==(*rootPtr)->data){
    removeNode=*rootPtr;
    if((*rootPtr)->right == NULL && (*rootPtr)->left == NULL)
      *rootPtr=NULL;
    else {
      if((*rootPtr)->right == NULL && (*rootPtr)->left != NULL){
        (*rootPtr)=(*rootPtr)->left;
        (*rootPtr)->balanceFactor++;
        *heightChange=1;
      }
      else if((*rootPtr)->right != NULL && (*rootPtr)->left == NULL){
        (*rootPtr)=(*rootPtr)->right;
        (*rootPtr)->balanceFactor++;
        *heightChange=1;
      }
      else{
        replaceNode=avlGetReplacer(&((*rootPtr)->right),heightChange);
        replaceNode->left=removeNode->left;
        replaceNode->right=removeNode->right;
        replaceNode->balanceFactor=removeNode->balanceFactor;
        *rootPtr=replaceNode;
        if((*rootPtr)->right!=NULL)
          checkForRotation(&((*rootPtr)->right),heightChange);
      }
      checkForRotation(rootPtr,heightChange);
      if(*heightChange)
        (*rootPtr)->balanceFactor--;
    }
    removeNode->left=NULL;
    removeNode->right=NULL;
    return removeNode;
  }
  else{
    if((*rootPtr)->left==NULL && (*rootPtr)->right==NULL)
      return NULL;
    else if(data < (*rootPtr)->data){
      if((*rootPtr)->left->data==data){
        if((*rootPtr)->left->right==NULL && (*rootPtr)->left->left==NULL)
          currentChange=1;
        if((*rootPtr)->right==NULL)
          *heightChange=1;
      }
      removeNode=avlRemove(&((*rootPtr)->left), data,heightChange);
      if(*heightChange||currentChange)
        (*rootPtr)->balanceFactor++;
      //checking whether there are violation
      checkForRotation(rootPtr,heightChange);
      return removeNode;
    }
    else if(data > (*rootPtr)->data){
      if((*rootPtr)->right->data==data){
        if((*rootPtr)->right->right==NULL && (*rootPtr)->right->left==NULL)
          currentChange=1;
        if((*rootPtr)->left==NULL)
          *heightChange=1;
      }
      removeNode=avlRemove(&((*rootPtr)->right), data,heightChange);
      if(*heightChange||currentChange)
        (*rootPtr)->balanceFactor--;
      //checking whether there are violation
      checkForRotation(rootPtr,heightChange);
      return removeNode;
    }
  }
}