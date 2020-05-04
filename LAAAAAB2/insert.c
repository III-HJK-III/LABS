#include <stdio.h>
#include "BST.h"

bool insert(BST *_Node, int value)
{
	Node *NewNode = (Node *)malloc(sizeof(Node));
	Node *Value;                                 //For value 
	
	if (_Node->root == NULL)                     //if root is empty
	{
		_Node->root = NewNode;
		NewNode->l_child = NULL;
		NewNode->r_child = NULL;
		NewNode->key = value;
		return TRUE;
	}
	
	if (Serch())                                 //what if value is already there?
	{
		return FALSE;
	}
	
	NewNode->l_child = NULL;
	NewNode->r_child = NULL;
	NewNode->key = value;
	
	Value = _Node->root;

	While(1)
	{
		if(Value->key < value)                   //if value is bigger
		{
			if(Value->r_child == NULL)           //if r_child is empty
			{
				Value->r_child = NewNode;
			}
			Value = Value->r_child;              //if r_child is full
		}
		
		else                                     //if value is smaller
		{
			if(Value->l_child == NULL)           //if l_child is empty
			{
				Value->l_child = NewNode; 
			}
			Value = Value->l_child;              //if l_child is full
		}
	}
	return TRUE;
}
