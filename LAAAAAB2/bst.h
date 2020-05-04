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

//testing testing
