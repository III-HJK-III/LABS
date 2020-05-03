#include <stdio.h>
#include "BST.h"

void Search(BST *_Node, int value)
{
	Node *Value = _Node->root;
	
	while(1)
	{
		if(Value->key == value)      // if there is same value
			return true;
			
		if(Value->key < value)       // bigger
			Value = Value->r_child
		else                         // smaller
			Value = Value->l_child
	}
}
