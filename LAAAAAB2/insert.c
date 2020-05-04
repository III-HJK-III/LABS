/*****************************************************/
/**********Made by ¹Ú°æ³ç from DKU, 32161553**********/
/*****************************************************/ 
#include "bst.h"

bool insert(BST *_Tree, unsigned int value)
{
	Node *NewNode = (Node *)malloc(sizeof(Node));
/*
	for(int i = 0; i < sizeof(Node); i++)        //Exception
		if(NewNode[i] == NULL)
			return FALSE;
*/			
	init_node(NewNode, value);                   //make NewNode
	
	if (_Tree->root == NULL)                     //if root is empty
	{
		_Tree->root = NewNode;
		NewNode->l_child = NULL;
		NewNode->r_child = NULL;
		NewNode->key = value;
		return TRUE;
	}
	
	if (Serch(value) == NULL)                    //what if value is already there?
	{
		return FALSE;
	}
	

	Node *Value = _Tree->root;                   //declare Value for value

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
