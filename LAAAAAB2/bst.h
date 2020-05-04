/* 32160320@dankook.ac.kr 권혁준 */
#pragma once

#include <stdio.h>
#include <pthread.h>

struct BST
{
    Node* root;
};

struct Node
{
    unsigned int key;
    Node* l_child;
    Node* r_child;
};


//testing testing
