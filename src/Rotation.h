#ifndef Rotation_H
#define Rotation_H

#include "Node.h"

Node *leftRotation(Node *head);

Node *rightRotation(Node *head);

Node *leftRightRotation(Node *head);

Node *rightLeftRotation(Node *head);

void checkForRotation(Node **rootPtr,int *heightChange);

#endif // Rotation_H
