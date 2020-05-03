#include <stdio.h>
#include "BST.h"

bool Search(BST *_Node, int value)
{
	Node *Value = _Node->root;
	
	while(1)
	{
		if(Value->key == value)        // if there is same value
			return true;
			
		if(Value->key < value)         // bigger
		{
			if(Value->r_child == NULL) // not exist
				return false;
			Value = Value->r_child;
		}
		
		else                           // smaller
		{
			if(Value->l_child == NULL) // not exist
				return false;
			Value = Value->l_child;
		}
	}
}
