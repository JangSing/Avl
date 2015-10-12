#include "Node.h"
#include <stdlib.h>

Tree *initiallizeTree(){
  Tree *tree=malloc(sizeof(Tree));
  
  tree->head=NULL;
  tree->length=0;
  
  return tree;
}
  
Node *createNode(Node *leftData,int root,Node *rightData){
  Node *node=malloc(sizeof(Node));
  
  node->left=leftData;
  node->right=rightData;
  node->weight=0;
  node->data=root;
  
  return node;
}

Tree *createTree(Tree *tree){
  
  Node *node_20=createNode(NULL,20,NULL);
  Node *node_30=createNode(node_20,30,NULL);
  Node *node_70=createNode(NULL,70,NULL);
  Node *node_100=createNode(NULL,100,NULL);
  Node *node_90=createNode(NULL,90,node_100);
  Node *node_80=createNode(node_70,80,node_90);
  Node *node_130=createNode(NULL,130,NULL);
  Node *node_150=createNode(node_130,150,NULL);
  Node *node_110=createNode(node_80,110,node_150);
  Node *node_60=createNode(node_30,60,node_110);
    
  tree->head=node_60;
  
  return tree;

}