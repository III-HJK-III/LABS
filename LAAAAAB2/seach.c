#include "bst.h"

Node* Search(BST *_Node, unsigned int value)
{
	Node *Value = _Node->root;
	
	if(Value == NULL)
		return NULL;

	while(Value)
	{
		if(Value->key == value)        // if there is same value
			break;
			
		else if(Value->key < value)         // bigger
		{
			Value = Value->r_child;
		}
		else                           // smaller
		{
			Value = Value->l_child;
		}
	}
	return Value;
}
