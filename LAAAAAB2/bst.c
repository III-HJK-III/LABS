/* 32160320@dankook.ac.kr 권혁준 */
#include "bst.h"

extern unsigned int counter;//for inorder trav.

//for initializing stuffs
void init_tree(BST *tree)
{
    tree -> root = NULL;
    pthread_mutex_init (&tree->treeLock, NULL);
}

void init_node(Node *nd, unsigned int inval)
{
    nd -> key = inval;
    nd -> l_child = NULL;
    nd -> r_child = NULL;
    pthread_mutex_init (&nd -> nodeLock, NULL);
}


//for inorder traversal
void io_trav(BST *tree)
{
        if(tree -> root == NULL)
    {
        printf("Empty!!\n");
        return;
    }
    counter = 0;
    ioP(tree -> root, cnt);
    return;
}

void ioP(Node *go)
{
    if(go)
    {
        ioP(go->l_child);
        counter++;
        ioP(go->r_child);
    }
}

//for random key val. generating
void rand_gen(unsigned int* arr, unsigned int max)
{
    unsigned int i = 0;
    unsigned int rand_i = 0;
    unsigned int tmp = 0;

    for(i=0; i < max; i++)
        arr[i] = i+1;
    
    srand((unsigned)time(NULL));
    for(i=0; i < max; i++)
    {
        rand_i = ((((unsigned int)rand()<<15)|rand())%max) + 1;
        tmp = arr[i];
        arr[i] = arr[rand_i];
        arr[rand_i] = tmp;
    }
}

//functions for thread run
void* seedling(void *arg)//create tree
{

    thread_arg *th_arg = (thread_arg *)arg;
    BST *tree = th_arg->tree;
    unsigned int *data = th_arg->arr;
    unsigned int start = th_arg->start, end = th_arg->end;
    int (*insert)(BST*,unsigned int) = th_arg->func;
    unsigned int i;
    unsigned int test;

    for (i=start ; i < end ; i++) {               
        test = insert(tree, data[i]);
        assert(!test); //fail to insert one node
    }
}

void* lumberjack(void *arg)//destrory tree
{

    thread_arg *th_arg = (thread_arg *)arg;
    BST *tree = th_arg->tree;
    unsigned int *data = th_arg->arr;
    unsigned int start = th_arg->start, end = th_arg->end;
    int (*remove)(BST*,unsigned int) = th_arg->func;
    unsigned int i;
    unsigned int test;
    for(i=start ; i < end; i++ ){
        test = remove(tree, data[i]);
        assert(!test); // fail to remove one node -no node matching the input key-
    }
}
