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






//test
int remove_fg(BST *tree, unsigned int x)
{
    Node* p = tree -> root;//what 2 erase
    pthread_mutex_lock(&p->nodeLock);
    Node* q = NULL;//p's parent
    //Node* cont = NULL;

    while(p)
    {
        if(x == p->key)
            break;
        else if(p->key > x)
        {
            if(q)
                pthread_mutex_unlock(&q->nodeLock);
            q = p;
            p = p->l_child;
            pthread_mutex_lock(&p->nodeLock);
        }
        else
        {
            if(q)
                pthread_mutex_unlock(&q->nodeLock);
            q = p;
            p = p->r_child;
            pthread_mutex_lock(&p->nodeLock);
        }
    }
    
    if(!p)
    {
        if(p)
            pthread_mutex_unlock(&p->nodeLock);
        if(q)
            pthread_mutex_unlock(&q->nodeLock);
        return FALSE;
    }
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
            p->l_child = NULL;
        }
        else if(!p->l_child)
        {
            pthread_mutex_lock(&tree->treeLock);
            tree -> root = p->r_child;
            pthread_mutex_unlock(&tree->treeLock);
            p->r_child = NULL;
        }
        else
        {
            Node* temp = p->l_child;
            pthread_mutex_lock(&temp->nodeLock);
            Node* p_temp = p;//parent of temp;
            while(temp->r_child)
            {
                if(p_temp != p)
                    pthread_mutex_unlock(&p_temp->nodeLock);
                p_temp = temp;
                temp = temp ->r_child;
                pthread_mutex_lock(&temp->nodeLock);
            }
        
            if(p_temp == p)//no r_child 4 1st temp
            {
                p->key = temp->key;
                p->l_child = temp->l_child;
                pthread_mutex_unlock(&p->nodeLock);
                p = temp;
            }
            else if(!temp->l_child)
            {
                p->key = temp->key;
                pthread_mutex_unlock(&p->nodeLock);
                p_temp->r_child = NULL;
                pthread_mutex_unlock(&p_temp->nodeLock);
                p = temp;
            }
            else
            {
                p->key = temp->key;
                pthread_mutex_unlock(&p->nodeLock);
                p_temp->r_child = temp->l_child;
                pthread_mutex_unlock(&p_temp->nodeLock);
                temp->l_child = NULL;
                p = temp;
            }
            //cont = temp;//4 delete
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
            pthread_mutex_unlock(&q->nodeLock);
        }
        else if(!p->r_child)//only 1 child
        {
            if(p == q->l_child)
            {
                q->l_child = p->l_child;
                pthread_mutex_unlock(&q->nodeLock);
                p->l_child = NULL;
            }
            else
            {
                q->r_child = p->l_child;
                pthread_mutex_unlock(&q->nodeLock);
                p->l_child = NULL;
            }
        }
        else if(!p->l_child)
        {
            if(p == q->l_child)
            {
                q->l_child = p->r_child;
                pthread_mutex_unlock(&q->nodeLock);
                p->r_child = NULL;
            }
            else
            {
                q->r_child = p->r_child;
                pthread_mutex_unlock(&q->nodeLock);
                p->r_child = NULL;
            }
        }
        else
        {
            pthread_mutex_unlock(&q->nodeLock);
            Node* temp = p->l_child;
            Node* p_temp = p;//parent of temp;
            while(temp->r_child)
            {
                if(p_temp != p)
                    pthread_mutex_unlock(&p_temp->nodeLock);
                p_temp = temp;
                temp = temp ->r_child;
                pthread_mutex_lock(&temp->nodeLock);
                
            }
        
            if(p_temp == p)//no r_child 4 1st temp
            {
                p->key = temp->key;
                p->l_child = temp->l_child;
                pthread_mutex_unlock(&p->nodeLock);
                p = temp;
            }
            else if(!temp->l_child)
            {
                p->key = temp->key;
                pthread_mutex_unlock(&p->nodeLock);
                p_temp->r_child = NULL;
                pthread_mutex_unlock(&p_temp->nodeLock);
                p = temp;
            }
            else
            {
                p->key = temp->key;
                pthread_mutex_unlock(&p->nodeLock);
                p_temp->r_child = temp->l_child;
                pthread_mutex_unlock(&p_temp->nodeLock);
                temp->l_child = NULL;
                p = temp;
            }
            //cont = temp;//4 delete
        }
    }

    //if(cont)
        //p = cont;
    pthread_mutex_unlock(&p->nodeLock);
    free(p);
    return TRUE;
}







/*
//remove with fine-grained lock
int remove_fg(BST *tree, unsigned int x)
{
    Node* q = NULL;//p's parent
    pthread_mutex_lock(&tree->treeLock);
    Node* p = tree -> root;//what 2 erase
    pthread_mutex_unlock(&tree->treeLock);
    //Node* cont = NULL;

    if(!p)
        return FALSE;

    pthread_mutex_lock(&p->nodeLock);
    
    //it was root!
    if(p->key == x)
    {
        printf("    IM HERE 1 !!\n");
        if(p->l_child && p->r_child)
        {
            Node* p_temp = p;//parent
            Node* c_temp = p->l_child;//child
            pthread_mutex_lock(&c_temp->nodeLock);

            while(c_temp->r_child)
            {
                if(p_temp->key != x)
                    pthread_mutex_unlock(&p_temp->nodeLock);
                p_temp = c_temp;
                c_temp = c_temp ->r_child;
                pthread_mutex_lock(&c_temp->nodeLock);
            }
            p->key = c_temp->key;
            pthread_mutex_unlock(&p->nodeLock);
            p_temp->r_child = NULL;
            pthread_mutex_unlock(&p_temp->nodeLock);
            p = c_temp;
        }
        else if(p->l_child)
        {
            pthread_mutex_lock(&tree->treeLock);
            tree->root = p->l_child;
            pthread_mutex_unlock(&tree->treeLock);
        }
        else if(p->r_child)
        {
            pthread_mutex_lock(&tree->treeLock);
            tree->root = p->r_child;
            pthread_mutex_unlock(&tree->treeLock);
        }
        else
        {
            pthread_mutex_lock(&tree->treeLock);
            tree->root = NULL;
            pthread_mutex_unlock(&tree->treeLock);
        }
        printf("    IM GONE 1 !!\n");
    }
    //only one node left && it IS not x
    else if(!p->l_child && !p->r_child)
    {
        pthread_mutex_unlock(&p->nodeLock);
        return FALSE;
    }
    else
    {
        printf("    IM HERE 2 !!\n");
        //setting q & p
        q = p;
        if(q->l_child && q->r_child)
        {
            if(x < q->key)
                p = q->l_child;
            else if(x > q->key)
                p = q->r_child;
            else
                assert(!x);
            printf("RLRL Dobble\n");
        }
        else if(q->l_child && !q->r_child)
        {
            p = q->l_child;
            printf("LLLLLLLLLLLL\n");
        }
        else if(!q->l_child && q->r_child)
        {
            p = q->r_child;
            printf("RRRRRRRRRRRR\n");
        }
        else
        {
            printf("Ummmm now what?\n");
            pthread_mutex_unlock(&p->nodeLock);
            return FALSE;
        }
        pthread_mutex_lock(&p->nodeLock);

        //finding the right p
        while(p)
        {
            printf("        x : %d ,p : %d\n",x,p->key);
            if(x == p->key)
            {
                printf("p is TRUE_OUT!!\n");
                break;
            }
            else if(x < p->key)
            {
                pthread_mutex_unlock(&q->nodeLock);
                q = p;
                p = q->l_child;
                if(p)
                    pthread_mutex_lock(&p->nodeLock);
            }
            else
            {
                pthread_mutex_unlock(&q->nodeLock);
                q = p;
                p = q->r_child;
                if(p)
                    pthread_mutex_lock(&p->nodeLock);
            }
            if(p)
                printf("p is TRUE!!\n");
        }
        printf("        OUT!!!!!!!\n");
        //there is no x!!
        if(!p)
        {
            printf("p is FALSE...\n");
            pthread_mutex_unlock(&q->nodeLock);
            return FALSE;
        }

        if(p->l_child && p->r_child)
        {
            pthread_mutex_unlock(&q->nodeLock);
            Node* p_temp = p;//parent
            Node* c_temp = p->l_child;//child
            pthread_mutex_lock(&c_temp->nodeLock);

            while(c_temp->r_child)
            {
                printf("        IN@@@@@@@@\n");
                if(p_temp->key != x)
                    pthread_mutex_unlock(&p_temp->nodeLock);
                p_temp = c_temp;
                c_temp = c_temp ->r_child;
                pthread_mutex_lock(&c_temp->nodeLock);
            }
            printf("        OUT@@@@@@@@\n");
            p->key = c_temp->key;
            pthread_mutex_unlock(&p->nodeLock);
            p_temp->r_child = NULL;
            pthread_mutex_unlock(&p_temp->nodeLock);
            p = c_temp;
        }
        else if(p->l_child)
        {
            if(q->l_child == p)
                q->l_child = p->l_child;
            else
                q->r_child = p->l_child;
            pthread_mutex_unlock(&q->nodeLock);
        }
        else
        {
            if(q->l_child == p)
                q->l_child = p->r_child;
            else
                q->r_child = p->r_child;
            pthread_mutex_unlock(&q->nodeLock);
        }
        printf("    IM GONE 2 !!\n");
    }

    pthread_mutex_unlock(&p->nodeLock);
    free(p);
    return TRUE;
}
*/