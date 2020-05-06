#include "bst.h"

Node* Search(BST *_Node, unsigned int value)
{
	Node *Value = _Node->root;
	
	if(!Value)
		return NULL;
		
	while(1)
	{
		if(Value->key == value)        // if there is same value
			return Value;
			
		if(Value->key < value)         // bigger
		{
			if(Value->r_child == NULL) // not exist
				return NULL;
			Value = Value->r_child;
		}
		
		else                           // smaller
		{
			if(Value->l_child == NULL) // not exist
				return NULL;
			Value = Value->l_child;
		}
	}
}
