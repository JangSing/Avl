#ifndef avlRemove_H
#define avlRemove_H
#include "Node.h"

Node *avlRemove(Node **rootPtr,int data,int *heightChange);

Node *avlGetReplacer(Node **rootPtr,int *heightChange);


#endif // avlRemove_H
