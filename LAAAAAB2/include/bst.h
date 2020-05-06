/* 32160320@dankook.ac.kr 권혁준 */
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>
#include <string.h>
#include <limits.h>
#include "bst.h"

#define MAX_NODE 10000000
#define MAX_THREAD 100
#define TRUE 1
#define FALSE 0

typedef struct _Node
{
    pthread_mutex_t nodeLock;
    unsigned int key;
    struct _Node* l_child;
    struct _Node* r_child;
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
    int (*func)(BST*,unsigned int);
} thread_arg;


/************function prototype*****************/

//initializing tree and node
void init_tree(BST *tree);
void init_node(Node *nd, unsigned int inval);

//getting random number for insert
void rand_gen(unsigned int arr[], unsigned int max);

//functions for thread run
void* seedling(void *arg);//create tree
void* lumberjack(void *arg);//destrory tree

//for inorder trav.
void io_trav(BST *tree);
void ioP(Node* go);

//functions for thread run
void* seedling(void *arg);

//node searching func.
Node* Search(BST *_Node, unsigned int value);

//node inserting func.
int insert_Xmutex(BST *_Tree, unsigned int value);
int insert_CoarseLock(BST *_Tree, unsigned int value);
int insert_FineLock(BST *_Tree, unsigned int value);

//node removing func.
int remove_Xmutex(BST *tree, unsigned int x);
int remove_cg(BST *tree, unsigned int x);
int remove_fg(BST *tree, unsigned int x);
