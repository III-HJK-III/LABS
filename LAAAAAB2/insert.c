/********************************************************/
/**********Made by 박경녕 from DKU, 32161553**********/
/********************************************************/ 
#include "bst.h"

int insert_Xmutex(BST *_Tree, unsigned int value)
{
	Node *NewNode = (Node *)malloc(sizeof(Node));

	if(NewNode == NULL)                                //Exception
	{
		return FALSE;
	}        

	init_node(NewNode, value);                         //make NewNode
	
	if (Search(_Tree ,value))                          //what if value is already there?
	{
		free(NewNode);
		return FALSE;
	}

	if (_Tree->root == NULL)                           //if root is empty
	{
		_Tree->root = NewNode;
		return TRUE;
	}

	Node *Value = _Tree->root;                         //declare Value for value

	while(1)
	{
		if(Value->key < value)                         //if value is bigger
		{
			if(Value->r_child == NULL)                 //if r_child is empty
			{
				Value->r_child = NewNode;
				break;
			}
			Value = Value->r_child;                    //if r_child is full
		}
		
		else                                           //if value is smaller
		{
			if(Value->l_child == NULL)                 //if l_child is empty
			{
				Value->l_child = NewNode; 
				break;
			}
			Value = Value->l_child;                    //if l_child is full
		}
	}
	return TRUE;
}


int insert_CoarseLock(BST *_Tree, unsigned int value)
{
	Node *NewNode = (Node *)malloc(sizeof(Node));

	if(NewNode == NULL)                                 //Exception
		return FALSE;        
					
	init_node(NewNode, value);                          //make NewNode

	if (Search(_Tree ,value))                           //what if value is already there?
	{
		free(NewNode);
		return FALSE;
	}

	if (_Tree->root == NULL)                            //if root is empty
	{
		pthread_mutex_lock(&_Tree->treeLock);           //Lock _Tree
		_Tree->root = NewNode;
		pthread_mutex_unlock(&_Tree->treeLock);         //Unlock
		return TRUE;
	}

	Node *Value = _Tree->root;                          //declare Value for value
	Node *Temp = NULL;                                  //Temp for Lock
 
	while(1)
	{
		pthread_mutex_lock(&Value->nodeLock);           //Lock Tree
		if(Value->key < value)                          //if value is bigger
		{
			if(Value->r_child == NULL)                  //if r_child is empty
			{
				Value->r_child = NewNode;
				pthread_mutex_unlock(&Value->nodeLock); //Unlock
				break;
			}
			Temp = Value->r_child;                      //if r_child is full
		}
		
		else                                            //if value is smaller
		{
			if(Value->l_child == NULL)                  //if l_child is empty
			{
				Value->l_child = NewNode; 
				pthread_mutex_unlock(&Value->nodeLock); //Unlock
				break;
			}
			Temp = Value->l_child;                      //if l_child is full
		}
		pthread_mutex_unlock(&Value->nodeLock);         //Unlock
		Value = Temp;
	}
	return TRUE;
}


int insert_FineLock(BST *_Tree, unsigned int value)
{
	Node *NewNode = (Node *)malloc(sizeof(Node));
	Node *Value = _Tree->root;                           //declare Value for value

	if(NewNode == NULL)                                  //Exception
		return FALSE;        
					
	init_node(NewNode, value);                           //make NewNode

	if (Search(_Tree ,value))                            //what if value is already there?
	{
		free(NewNode);
		return FALSE;
	}

	int tmp = TRUE;
	while(_Tree->root && tmp )
	{
		pthread_mutex_lock(&Value->nodeLock);    //Lock Value
		if(Value->key < value)                           //if value is bigger
		{
			if(Value->r_child == NULL)                   //if r_child is empty
			{
				Value->r_child = NewNode;
				tmp = FALSE;
			}
			Value = Value->r_child;                      //if r_child is full
		}
		else                                             //if value is smaller
		{
			if(Value->l_child == NULL)                   //if l_child is empty
			{
				Value->l_child = NewNode; 
				tmp = FALSE;
			}
			Value = Value->l_child;                      //if l_child is full
		}
		pthread_mutex_unlock(&Value->nodeLock);  //Unlock
	}

	pthread_mutex_lock(&_Tree->treeLock);            //Lock _Tree
	if (_Tree->root == NULL)                             //if root is empty
	{
		_Tree->root = NewNode;
	}
	pthread_mutex_unlock(&_Tree->treeLock);          //Unlock

	return TRUE;
}
