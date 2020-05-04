#include "bst.h"


//for initializing stuffs
void init_tree(BST &tree)
{
    tree -> root = NULL;
    pthread_mutex_init (tree->treeLock, NULL);
}

void init_myArr(myArr &arr)
{
    arr -> index = 0;
    pthread_mutex_init (arr -> arrLock, NULL);
}

void init_node(node &nd, unsigned int inval)
{
    nd -> key = inval;
    nd -> l_child = NULL;
    nd -> r_child = NULL;
    pthread_mutex_init (nd -> nodeLock, NULL);
}



//for inorder traversal
void io_trav(BST &tree, myArr &arr)
{
        if(tree -> root)
    {
        printf("Empty!!\n");
        return;
    }
    
    ioP(tree -> root, myArr);
    return;
}

void ioP(Node* go, maArr &arr)
{
    if(go)
    {
        ioP(go->l_child, arr);
        arr->index++;
        arr->keyvals[index-1] = go->key;

        ioP(go->r_child, arr;
    }
}