/* 32160320@dankook.ac.kr 권혁준 */
#include "bst.h"

//remove without mutex
int remove_Xmutex(BST *tree, unsigned int x)
{
    Node* p = tree -> root;//what 2 erase
    Node* q = NULL;//p's parent

    while(p)
    {
        if(x == p->key)
            break;
        else if(p->key > x)
        {
            q = p;
            p = p->l_child;
        }
        else
        {
            q = p;
            p = p->r_child;
        }
    }
    
    if(!p)
        return FALSE;

    if(!p->l_child && !p->r_child)//no child
    {
        if(p == tree->root)//if 'what 2 erase' is root
            tree -> root = NULL;
        else if(p == q->l_child)
            q->l_child = NULL;
        else
            q->r_child = NULL;
    }
    else if(!p->r_child)//only 1 child
    {
        if(p == tree->root)//if 'what 2 erase' is root
        {
            tree -> root = p->l_child;
            p->l_child = NULL;
        }
        else if(p == q->l_child)
        {
            q->l_child = p->l_child;
            p->l_child = NULL;
        }
        else
        {
            q->r_child = p->l_child;
            p->l_child = NULL;
        }
    }
    else if(!p->l_child)
    {
        if(p == tree->root)//if 'what 2 erase' is root
        {
            tree -> root = p->r_child;
            p->r_child = NULL;
        }
        else if(p == q->l_child)
        {
            q->l_child = p->r_child;
            p->r_child = NULL;
        }
        else
        {
            q->r_child = p->r_child;
            p->r_child = NULL;
        }
    }
    else//have 2 child
    {
        Node* temp = p->l_child;
        q = p;//now, q is used as parent of temp;

        while(temp->r_child)
        {
            q = temp;
            temp = temp ->r_child;
        }
        
        if(q == p)//no r_child 4 1st temp
        {
            p->key = temp->key;
            p->l_child = temp->l_child;
        }
        else if(!temp ->l_child)
        {
            p->key = temp->key;
            q->r_child = NULL;
        }
        else
        {
            p->key = temp->key;
            q->r_child = temp->l_child;
            temp->l_child = NULL;
        }
        p = temp;//4 delete
    }
    free(p);
    return TRUE;
}


//remove with coarse-grained lock
int remove_cg(BST *tree, unsigned int x)
{
    Node* p = tree -> root;//what 2 erase
    Node* q = NULL;//p's parent

    while(p)
    {
        if(x == p->key)
            break;
        else if(p->key > x)
        {
            q = p;
            p = p->l_child;
        }
        else
        {
            q = p;
            p = p->r_child;
        }
    }
    
    if(!p)
        return FALSE;

    pthread_mutex_lock(&q->nodeLock);
    pthread_mutex_lock(&p->nodeLock);
    pthread_mutex_lock(&tree->treeLock);

    if(!p->l_child && !p->r_child)//no child
    {
        if(p == tree->root)//if 'what 2 erase' is root
            tree -> root = NULL;
        else if(p == q->l_child)
            q->l_child = NULL;
        else
            q->r_child = NULL;
    }
    else if(!p->r_child)//only 1 child
    {
        if(p == tree->root)//if 'what 2 erase' is root
        {
            tree -> root = p->l_child;
            p->l_child = NULL;
        }
        else if(p == q->l_child)
        {
            q->l_child = p->l_child;
            p->l_child = NULL;
        }
        else
        {
            q->r_child = p->l_child;
            p->l_child = NULL;
        }
    }
    else if(!p->l_child)
    {
        if(p == tree->root)//if 'what 2 erase' is root
        {
            tree -> root = p->r_child;
            p->r_child = NULL;
        }
        else if(p == q->l_child)
        {
            q->l_child = p->r_child;
            p->r_child = NULL;
        }
        else
        {
            q->r_child = p->r_child;
            p->r_child = NULL;
        }
    }
    else//have 2 child
    {
        Node* temp = p->l_child;
        Node* p_temp = p;//now, q is used as parent of temp;
        Node* cont = NULL;//Used for lock

        while(temp->r_child)
        {
            p_temp = temp;
            temp = temp ->r_child;
        }
        
        if(p_temp == p)//no r_child 4 1st temp
        {
            p->key = temp->key;
            p->l_child = temp->l_child;
        }
        else if(!temp->l_child)
        {
            p->key = temp->key;
            pthread_mutex_lock(&p_temp->nodeLock);
            p_temp->r_child = NULL;
            pthread_mutex_unlock(&p_temp->nodeLock);
        }
        else
        {
            p->key = temp->key;
            pthread_mutex_lock(&p_temp->nodeLock);
            pthread_mutex_lock(&temp->nodeLock);
            p_temp->r_child = temp->l_child;
            temp->l_child = NULL;
            pthread_mutex_unlock(&temp->nodeLock);
            pthread_mutex_unlock(&p_temp->nodeLock);
        }
        cont = temp;//4 delete
    }
    pthread_mutex_unlock(&q->nodeLock);
    pthread_mutex_unlock(&p->nodeLock);
    pthread_mutex_unlock(&tree->treeLock);

    if(cont != NULL)
        p = cont;

    free(p);
    return TRUE;
}


//remove with fine-grained lock
int remove_fg(BST *tree, unsigned int x)
{
    Node* p = tree -> root;//what 2 erase
    Node* q = NULL;//p's parent

    while(p)
    {
        if(x == p->key)
            break;
        else if(p->key > x)
        {
            q = p;
            p = p->l_child;
        }
        else
        {
            q = p;
            p = p->r_child;
        }
    }
    
    if(!p)
        return FALSE;

    if(!p->l_child && !p->r_child)//no child
    {
        if(p == tree->root)//if 'what 2 erase' is root
        {
            pthread_mutex_lock(&tree->treeLock);
            tree -> root = NULL;
            pthread_mutex_unlock(&tree->treeLock);
        }
        else if(p == q->l_child)
        {
            pthread_mutex_lock(&tree->treeLock);
            pthread_mutex_lock(&q->nodeLock);
            q->l_child = NULL;
            pthread_mutex_unlock(&q->nodeLock);
            pthread_mutex_unlock(&tree->treeLock);
        }
        else
        {
            pthread_mutex_lock(&tree->treeLock);
            pthread_mutex_lock(&q->nodeLock);
            q->r_child = NULL;
            pthread_mutex_unlock(&q->nodeLock);
            pthread_mutex_unlock(&tree->treeLock);
        }
    }
    else if(!p->r_child)//only 1 child
    {
        if(p == tree->root)//if 'what 2 erase' is root
        {
            pthread_mutex_lock(&tree->treeLock);
            pthread_mutex_lock(&p->nodeLock);
            tree -> root = p->l_child;
            p->l_child = NULL;
            pthread_mutex_unlock(&p->nodeLock);
            pthread_mutex_unlock(&tree->treeLock);
        }
        else if(p == q->l_child)
        {
            pthread_mutex_lock(&tree->treeLock);
            pthread_mutex_lock(&p->nodeLock);
            pthread_mutex_lock(&q->nodeLock);
            q->l_child = p->l_child;
            p->l_child = NULL;
            pthread_mutex_unlock(&q->nodeLock);
            pthread_mutex_unlock(&p->nodeLock);
            pthread_mutex_unlock(&tree->treeLock);
        }
        else
        {
            pthread_mutex_lock(&tree->treeLock);
            pthread_mutex_lock(&p->nodeLock);
            pthread_mutex_lock(&q->nodeLock);
            q->r_child = p->l_child;
            p->l_child = NULL;
            pthread_mutex_unlock(&q->nodeLock);
            pthread_mutex_unlock(&p->nodeLock);
            pthread_mutex_unlock(&tree->treeLock);
        }
    }
    else if(!p->l_child)
    {
        if(p == tree->root)//if 'what 2 erase' is root
        {
            pthread_mutex_lock(&tree->treeLock);
            pthread_mutex_lock(&p->nodeLock);
            tree -> root = p->r_child;
            p->r_child = NULL;
            pthread_mutex_unlock(&p->nodeLock);
            pthread_mutex_unlock(&tree->treeLock);
        }
        else if(p == q->l_child)
        {
            pthread_mutex_lock(&tree->treeLock);
            pthread_mutex_lock(&p->nodeLock);
            pthread_mutex_lock(&q->nodeLock);
            q->l_child = p->r_child;
            p->r_child = NULL;
            pthread_mutex_unlock(&q->nodeLock);
            pthread_mutex_unlock(&p->nodeLock);
            pthread_mutex_unlock(&tree->treeLock);
        }
        else
        {
            pthread_mutex_lock(&tree->treeLock);
            pthread_mutex_lock(&p->nodeLock);
            pthread_mutex_lock(&q->nodeLock);
            q->r_child = p->r_child;
            p->r_child = NULL;
            pthread_mutex_unlock(&q->nodeLock);
            pthread_mutex_unlock(&p->nodeLock);
            pthread_mutex_unlock(&tree->treeLock);
        }
    }
    else//have 2 child
    {
        Node* temp = p->l_child;
        q = p;//now, q is used as parent of temp;

        while(temp->r_child)
        {
            q = temp;
            temp = temp ->r_child;
        }
        
        if(q == p)//no r_child 4 1st temp
        {
            pthread_mutex_lock(&tree->treeLock);
            pthread_mutex_lock(&p->nodeLock);
            p->key = temp->key;
            p->l_child = temp->l_child;
            pthread_mutex_unlock(&p->nodeLock);
            pthread_mutex_unlock(&tree->treeLock);
        }
        else if(!temp->l_child)
        {
            pthread_mutex_lock(&tree->treeLock);
            pthread_mutex_lock(&p->nodeLock);
            pthread_mutex_lock(&q->nodeLock);
            p->key = temp->key;
            q->r_child = NULL;
            pthread_mutex_unlock(&q->nodeLock);
            pthread_mutex_unlock(&p->nodeLock);
            pthread_mutex_unlock(&tree->treeLock);
        }
        else
        {
            pthread_mutex_lock(&tree->treeLock);
            pthread_mutex_lock(&p->nodeLock);
            pthread_mutex_lock(&q->nodeLock);
            p->key = temp->key;
            q->r_child = temp->l_child;
            pthread_mutex_lock(&temp->nodeLock);
            temp->l_child = NULL;
            pthread_mutex_unlock(&temp->nodeLock);
            pthread_mutex_unlock(&q->nodeLock);
            pthread_mutex_unlock(&p->nodeLock);
            pthread_mutex_unlock(&tree->treeLock);
        }
        p = temp;//4 delete

    }
    free(p);
    return TRUE;
}
