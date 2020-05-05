/* 32160320@dankook.ac.kr 권혁준 */
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>
#include <string.h>
#include <limits.h>

#define MAX_NODE 1000000
#define TRUE 1
#define FALSE 0

struct BST
{   
    pthread_mutex_t treeLock;
    Node* root;
};

struct Node
{
    pthread_mutex_t nodeLock;
    unsigned int key;
    Node* l_child;
    Node* r_child;
};

struct myArr
{
    pthread_mutex_t arrLock;
    unsigned int keyvals[MAX_NODE];
    unsigned int index;//last val's next index
};

struct myCounter
{
    pthread_mutex_t counterLock;
    unsigned int counter;
}myCnt;

/************function prototype*****************/

//basic func. for bst usage
void init_tree(BST &tree);
void init_myArr(myArr &arr);
void init_node(node &nd, unsigned int inval);
void init_myCounter(myCounter& cnt);

void io_trav(BST &tree, myArr &arr);
void ioP(Node* go, maArr &arr);


//node searching func.
Node* Search(BST *_Node, int value);


//node inserting func.
bool insert(BST *_Tree, unsigned int value);


//node removing func.
void remove_Xmutex(Node &x);