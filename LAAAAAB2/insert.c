/********************************************************/
/**********Made by 박경녕 from DKU, 32161553**********/
/********************************************************/ 
#include "bst.h"

bool insert_Xmutex(BST *_Tree, unsigned int value)
{
	Node *NewNode = (Node *)malloc(sizeof(Node));

	if(NewNode == NULL)                                //Exception
		return FALSE;        
					
	init_node(NewNode, value);                         //make NewNode
	
	if (_Tree->root == NULL)                           //if root is empty
	{
		_Tree->root = NewNode;
		return TRUE;
	}
	
	if (Serch(value) == NULL)                          //what if value is already there?
		return FALSE;


	Node *Value = _Tree->root;                         //declare Value for value

	While(1)
	{
		if(Value->key < value)                         //if value is bigger
		{
			if(Value->r_child == NULL)                 //if r_child is empty
			{
				Value->r_child = NewNode;
			}
			Value = Value->r_child;                    //if r_child is full
		}
		
		else                                           //if value is smaller
		{
			if(Value->l_child == NULL)                 //if l_child is empty
			{
				Value->l_child = NewNode; 
			}
			Value = Value->l_child;                    //if l_child is full
		}
	}
	return TRUE;
}


bool insert_CoarseLock(BST *_Tree, unsigned int value)
{
	Node *NewNode = (Node *)malloc(sizeof(Node));

	if(NewNode == NULL)                                 //Exception
		return FALSE;        
					
	init_node(NewNode, value);                          //make NewNode
	
	if (_Tree->root == NULL)                            //if root is empty
	{
		pthread_mutex_lock(&_Tree->treeLock);           //Lock _Tree
		_Tree->root = NewNode;
		pthread_mutex_unlock(&_Tree->treeLock);         //Unlock
		return TRUE;
	}
	
	if (Serch(value) == NULL)                           //what if value is already there?
		return FALSE;

	Node *Value = _Tree->root;                          //declare Value for value
	Node *Temp = NULL;                                  //Temp for Lock
 
	While(1)
	{
		pthread_mutex_lock(&Temp->nodeLock);            //Lock Temp
		if(Value->key < value)                          //if value is bigger
		{
			if(Value->r_child == NULL)                  //if r_child is empty
			{
				Value->r_child = NewNode;
			}
			Temp = Value->r_child;                      //if r_child is full
		}
		
		else                                            //if value is smaller
		{
			if(Value->l_child == NULL)                  //if l_child is empty
			{
				Value->l_child = NewNode; 
			}
			Value = Value->l_child;                     //if l_child is full
		}
		pthread_mutex_unlock(&Temp->nodeLock);          //Unlock
		Value = Temp;
	}
	return TRUE;
}


bool insert_FineLock(BST *_Tree, unsigned int value)
{
	Node *NewNode = (Node *)malloc(sizeof(Node));

	if(NewNode == NULL)                                  //Exception
		return FALSE;        
					
	init_node(NewNode, value);                           //make NewNode
	
	if (_Tree->root == NULL)                             //if root is empty
	{
		pthread_mutex_lock(&_Tree->treeLock);            //Lock _Tree
		_Tree->root = NewNode;
		pthread_mutex_unlock(&_Tree->treeLock);          //Unlock
		return TRUE;
	}
	
	if (Serch(value) == NULL)                            //what if value is already there?
		return FALSE;

	Node *Value = _Tree->root;                           //declare Value for value

	While(1)
	{
		if(Value->key < value)                           //if value is bigger
		{
			if(Value->r_child == NULL)                   //if r_child is empty
			{
				pthread_mutex_lock(&Value->nodeLock);    //Lock Value
				Value->r_child = NewNode;
				pthread_mutex_unlock(&Value->nodeLock);  //Unlock
			}
			Value = Value->r_child;                      //if r_child is full
		}
		
		else                                             //if value is smaller
		{
			if(Value->l_child == NULL)                   //if l_child is empty
			{
				pthread_mutex_lock(&Value->nodeLock);    //Lock Value
				Value->l_child = NewNode; 
				pthread_mutex_unlock(&Value->nodeLock);  //Unlock
			}
			Value = Value->l_child;                      //if l_child is full
		}
	}
	return TRUE;
}
