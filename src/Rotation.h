#ifndef Rotation_H
#define Rotation_H

#include "Node.h"

void leftRotation(Tree *tree,Node *pivotNode);

void rightRotation(Tree *tree,Node *pivotNode);

void leftRightRotation(Tree *tree,Node *pivotNode1,Node *pivotNode2);

void rightLeftRotation(Tree *tree,Node *pivotNode1,Node *pivotNode2);

#endif // Rotation_H
