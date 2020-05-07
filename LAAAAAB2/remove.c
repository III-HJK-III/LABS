/* 32160320@dankook.ac.kr 권혁준 */
#include "bst.h"

//remove without mutex
int remove_Xmutex(BST *tree, unsigned int x)
{
    Node* p = tree -> root;//what 2 erase
    Node* q = NULL;//p's parent
    Node* cont = NULL;

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

    if(p == tree->root)
    {
        if(!p->l_child && !p->r_child)//no child
            tree -> root = NULL;

        else if(!p->r_child)//only 1 child
        {
            tree -> root = p->l_child;
            p->l_child = NULL;
        }
        else if(!p->l_child)
        {
            tree -> root = p->r_child;
            p->r_child = NULL;
        }
        else
        {
            Node* temp = p->l_child;
            Node* p_temp = p;//parent of temp;
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
                p_temp->r_child = NULL;
            }
            else
            {
                p->key = temp->key;
                p_temp->r_child = temp->l_child;
                temp->l_child = NULL;
            }
            cont = temp;//4 delete
        }
    }
    else
    {
        if(!p->l_child && !p->r_child)//no child
        {
            if(p == q->l_child)
                q->l_child = NULL;
            else
                q->r_child = NULL;
        }
        else if(!p->r_child)//only 1 child
        {
            if(p == q->l_child)
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
            if(p == q->l_child)
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
        else
        {
            Node* temp = p->l_child;
            Node* p_temp = p;//parent of temp;
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
                p_temp->r_child = NULL;
            }
            else
            {
                p->key = temp->key;
                p_temp->r_child = temp->l_child;
                temp->l_child = NULL;
            }
            cont = temp;//4 delete
        }
    }

    if(cont)
        p = cont;
    free(p);
    return TRUE;
}


//remove with coarse-grained lock
int remove_cg(BST *tree, unsigned int x)
{
    pthread_mutex_lock(&tree->treeLock);
    Node* p = tree -> root;//what 2 erase
    Node* q = NULL;//p's parent
    Node* cont = NULL;

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
    {
        pthread_mutex_unlock(&tree->treeLock);
        return FALSE;
    }
    if(p == tree->root)
    {
        if(!p->l_child && !p->r_child)//no child
            tree -> root = NULL;
        else if(!p->r_child)//only 1 child
        {
            tree -> root = p->l_child;
            p->l_child = NULL;
        }
        else if(!p->l_child)
        {
            tree -> root = p->r_child;
            p->r_child = NULL;
        }
        else
        {
            Node* temp = p->l_child;
            Node* p_temp = p;//parent of temp;
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
                p_temp->r_child = NULL;
            }
            else
            {
                p->key = temp->key;
                p_temp->r_child = temp->l_child;
                temp->l_child = NULL;
            }
            cont = temp;//4 delete
        }
    }
    else
    {
        if(!p->l_child && !p->r_child)//no child
        {
            if(p == q->l_child)
                q->l_child = NULL;
            else
                q->r_child = NULL;
        }
        else if(!p->r_child)//only 1 child
        {
            if(p == q->l_child)
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
            if(p == q->l_child)
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
        else
        {
            Node* temp = p->l_child;
            Node* p_temp = p;//parent of temp;
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
                p_temp->r_child = NULL;
            }
            else
            {
                p->key = temp->key;
                p_temp->r_child = temp->l_child;
                temp->l_child = NULL;
            }
            cont = temp;//4 delete
        }
    }

    if(cont)
        p = cont;
    free(p);
    pthread_mutex_unlock(&tree->treeLock);
    return TRUE;
}


//remove with fine-grained lock
int remove_fg(BST *tree, unsigned int x)
{
    Node* p = tree -> root;//what 2 erase
    Node* q = NULL;//p's parent
    Node* cont = NULL;

    pthread_mutex_lock(&tree->treeLock);
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
    pthread_mutex_unlock(&tree->treeLock);
    
    if(!p)
        return FALSE;
    if(p == tree->root)
    {
        if(!p->l_child && !p->r_child)//no child
        {
            pthread_mutex_lock(&tree->treeLock);
            tree -> root = NULL;
            pthread_mutex_unlock(&tree->treeLock);
        }
        else if(!p->r_child)//only 1 child
        {
            pthread_mutex_lock(&tree->treeLock);
            tree -> root = p->l_child;
            pthread_mutex_unlock(&tree->treeLock);
        }
        else if(!p->l_child)
        {
            pthread_mutex_lock(&tree->treeLock);
            tree -> root = p->r_child;
            pthread_mutex_unlock(&tree->treeLock);
        }
        else
        {
            Node* temp = p->l_child;
            Node* p_temp = p;//parent of temp;
            pthread_mutex_lock(&tree->treeLock);
            while(temp->r_child)
            {
                p_temp = temp;
                temp = temp ->r_child;
            }
            pthread_mutex_unlock(&tree->treeLock);
        
            if(p_temp == p)//no r_child 4 1st temp
            {
                pthread_mutex_lock(&tree->treeLock);
                //pthread_mutex_lock(&p->nodeLock);
                p->key = temp->key;
                p->l_child = temp->l_child;
                //pthread_mutex_unlock(&p->nodeLock);
                pthread_mutex_unlock(&tree->treeLock);
            }
            else if(!temp->l_child)
            {
                pthread_mutex_lock(&tree->treeLock);
                //pthread_mutex_lock(&p->nodeLock);
                //pthread_mutex_lock(&p_temp->nodeLock);
                p->key = temp->key;
                p_temp->r_child = NULL;
                //pthread_mutex_unlock(&p_temp->nodeLock);
                //pthread_mutex_unlock(&p->nodeLock);
                pthread_mutex_unlock(&tree->treeLock);
            }
            else
            {
            	pthread_mutex_lock(&tree->treeLock);
            	//pthread_mutex_lock(&p->nodeLock);
            	//pthread_mutex_lock(&p_temp->nodeLock);
                p->key = temp->key;
                p_temp->r_child = temp->l_child;
            	//pthread_mutex_unlock(&p_temp->nodeLock);
            	//pthread_mutex_unlock(&p->nodeLock);
            	pthread_mutex_unlock(&tree->treeLock);
            }
            cont = temp;//4 delete
        }
    }
    else
    {
        if(!p->l_child && !p->r_child)//no child
        {
            if(p == q->l_child)
            {
                pthread_mutex_lock(&tree->treeLock);
                //pthread_mutex_lock(&q->nodeLock);
                q->l_child = NULL;
                //pthread_mutex_unlock(&q->nodeLock);
                pthread_mutex_unlock(&tree->treeLock);
            }
            else
            {
                pthread_mutex_lock(&tree->treeLock);
                //pthread_mutex_lock(&q->nodeLock);
                q->r_child = NULL;
                //pthread_mutex_unlock(&q->nodeLock);
                pthread_mutex_unlock(&tree->treeLock);
            }
        }
        else if(!p->r_child)//only 1 child
        {
            if(p == q->l_child)
            {
                q->l_child = p->l_child;
                p->l_child = NULL;
            }
            else
            {
                pthread_mutex_lock(&tree->treeLock);
                //pthread_mutex_lock(&q->nodeLock);
                //pthread_mutex_lock(&p->nodeLock);
                q->r_child = p->l_child;
                p->l_child = NULL;
                //pthread_mutex_unlock(&p->nodeLock);
                //pthread_mutex_unlock(&q->nodeLock);
                pthread_mutex_unlock(&tree->treeLock);
            }
        }
        else if(!p->l_child)
        {
            if(p == q->l_child)
            {
                pthread_mutex_lock(&tree->treeLock);
                //pthread_mutex_lock(&q->nodeLock);
                //pthread_mutex_lock(&p->nodeLock);
                q->l_child = p->r_child;
                p->r_child = NULL;
                //pthread_mutex_unlock(&p->nodeLock);
                //pthread_mutex_unlock(&q->nodeLock);
                pthread_mutex_unlock(&tree->treeLock);
            }
            else
            {
                pthread_mutex_lock(&tree->treeLock);
                //pthread_mutex_lock(&q->nodeLock);
                //pthread_mutex_lock(&p->nodeLock);
                q->r_child = p->r_child;
                p->r_child = NULL;
                //pthread_mutex_unlock(&p->nodeLock);
                //pthread_mutex_unlock(&q->nodeLock);
                pthread_mutex_unlock(&tree->treeLock);
            }
        }
        else
        {
            Node* temp = p->l_child;
            Node* p_temp = p;//parent of temp;
            pthread_mutex_lock(&tree->treeLock);
            while(temp->r_child)
            {
                p_temp = temp;
                temp = temp ->r_child;
            }
            pthread_mutex_unlock(&tree->treeLock);
        
            if(p_temp == p)//no r_child 4 1st temp
            {
                pthread_mutex_lock(&tree->treeLock);
                //pthread_mutex_lock(&p->nodeLock);
                p->key = temp->key;
                p->l_child = temp->l_child;
                //pthread_mutex_unlock(&p->nodeLock);
                pthread_mutex_unlock(&tree->treeLock);
            }
            else if(!temp->l_child)
            {
                pthread_mutex_lock(&tree->treeLock);
                //pthread_mutex_lock(&p->nodeLock);
                //pthread_mutex_lock(&p_temp->nodeLock);
                p->key = temp->key;
                p_temp->r_child = NULL;
                //pthread_mutex_unlock(&p_temp->nodeLock);
                //pthread_mutex_unlock(&p->nodeLock);
                pthread_mutex_unlock(&tree->treeLock);
            }
            else
            {
                pthread_mutex_lock(&tree->treeLock);
                //pthread_mutex_lock(&p->nodeLock);
                //pthread_mutex_lock(&p_temp->nodeLock);
                p->key = temp->key;
                p_temp->r_child = temp->l_child;
                //pthread_mutex_unlock(&p_temp->nodeLock);
                //pthread_mutex_unlock(&p->nodeLock);
                pthread_mutex_unlock(&tree->treeLock);
            }
            cont = temp;//4 delete
        }
    }
    if(cont)
        p = cont;
    free(p);
    return TRUE;
}