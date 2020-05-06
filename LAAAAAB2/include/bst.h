/* 32160320@dankook.ac.kr 권혁준 */
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>
#include <string.h>
#include <limits.h>
#include "bst.h"

#define MAX_NODE 1000000
#define MAX_THREAD 50
#define TRUE 1
#define FALSE 0

typedef struct _Node
{
    pthread_mutex_t nodeLock;
    unsigned int key;
    struct Node* l_child;
    struct Node* r_child;
} Node;

typedef struct _BST
{   
    //treeLock is used to insure atomicity(acquisition) and tree lock
    pthread_mutex_t treeLock;
    Node* root;
} BST;

//strct arg for thread / got from LAB2 example
typedef struct _thread_arg{
    pthread_t thread;
    BST *tree;
    unsigned int *arr;
    unsigned int start;
    unsigned int end;
    bool (*func)(BST*,unsigned int);
} thread_arg;


/************function prototype*****************/

//initializing tree and node
void init_tree(BST *tree);
void init_node(node *nd, unsigned int inval);

//getting random number for insert
void rand_gen(unsigned int* arr, unsigned int max);

//functions for thread run
void* seedling(void *arg);//create tree
void* lumberjack(void *arg);//destrory tree

//for inorder trav.
void io_trav(BST &tree, myArr &arr);
void ioP(Node* go, maArr &arr);

//functions for thread run
void* seedling(void *arg);

//node searching func.
Node* Search(BST *_Node, int value);
void* lumberjack(void *arg);

//node inserting func.
bool insert_Xmutex(BST *_Tree, unsigned int value);
bool insert_CoarseLock(BST *_Tree, unsigned int value);
bool insert_FineLock(BST *_Tree, unsigned int value);

//node removing func.
bool remove_Xmutex(BST *tree, unsigned int x);
bool remove_cg(BST *tree, unsigned int x);
bool remove_fg(BST *tree, unsigned int x);
