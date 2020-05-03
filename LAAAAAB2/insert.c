#include <stdio.h>
#include "BST.h"

void insert(BST *_Node, int value)
{
	Node *NewNode = (Node *)malloc(sizeof(Node));
	Node *Value;                                 //For value 
	
	if (_Node->root == NULL)                     //if root is empty
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
	
	Value = _Node->root;
	
	While(1)
	{
		if(Value->key < value)                   //if value is bigger
		{
			Value->r_child = NewNode;
			return;
		}
	}
}
