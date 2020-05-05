#include "bst.h"

//for initializing stuffs
void init_tree(BST *tree)
{
    tree -> root = NULL;
    pthread_mutex_init (&tree->treeLock, NULL);
}

void init_myArr(myArr *arr)
{
    arr -> index = 0;
    pthread_mutex_init (&arr -> arrLock, NULL);
}

void init_node(node *nd, unsigned int inval)
{
    nd -> key = inval;
    nd -> l_child = NULL;
    nd -> r_child = NULL;
    pthread_mutex_init (&nd -> nodeLock, NULL);
}

void init_myCounter(myCounter *cnt)
{
    cnt -> counter = 0;
    pthread_mutex_init (&cnt -> nodeLock, NULL);
}


//for inorder traversal
void io_trav(BST *tree, myArr *arr)
{
        if(tree -> root)
    {
        printf("Empty!!\n");
        return;
    }
    
    ioP(tree -> root, myArr);
    return;
}

void ioP(Node* go, maArr *arr)
{
    if(go)
    {
        ioP(go->l_child, arr);

        pthread_mutex_lock(arr->arrLock);
        arr->index++;
        arr->keyvals[index-1] = go->key;
        pthread_mutex_unlock(arr->arrLock);

        ioP(go->r_child, arr);
    }
}

//for random key val. generating
void rand_gen(unsigned int* arr, unsigned int max)
{
    unsigned int i = 0;
    unsigned int rand_i = 0;
    unsigned int tmp = 0;

    for(i=0; i < max, i++)
        arr[i] = i+1;
    
    srand((unsigned)time(NULL));
    for(i=0; i < max, i++)
    {
        rand_i = ((((unsigned int)rand()<<15)|rand())%max) + 1;
        temp = arr[i];
        arr[i] = arr[rand_i];
        arr[rand_i] = temp;
    }
}

//functions for thread run
void* seedling(void *arg)//create tree
{

    thread_arg *th_arg = (thread_arg *)arg;
    BST *tree = th_arg->tree;
    unsigned int *data = th_arg->arr;
    unsigned int start = th_arg->start, end = th_arg->end;
    bool (*insert)(BST*,unsigned int) = func;
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
    void (*remove)(BST*,unsigned int) = func;
    unsigned int i;
    unsigned int test;
    for(i=start ; i < end; i++ ){
        test = insert(tree, data[i]);
        assert(!test); // fail to remove one node -no node matching the input key-
    }
}
