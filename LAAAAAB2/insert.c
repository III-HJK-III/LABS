#include <stdio.h>
#include "BST.h"

void insert(BST *_Node, int value)
{
	Node *NewNode = (Node *)malloc(sizeof(Node));
	
	if (_Node->root == NULL)
	{
		_Node->root = NewNode;
		NewNode->l_child = NULL;
		NewNode->r_child = NULL;
		NewNode->key = value;
		return;
	}
	
	NewNode->l_child = NULL;
	NewNode->r_child = NULL;
	NewNode->key = value;
	
}
