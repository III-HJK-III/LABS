/* 32160320@dankook.ac.kr 권혁준 */

#include "bst.h"

void remove_Xmutex(const Node &x)
{
    Node* p = root;//what 2 erase
    Node* q = NULL;//p's parent

    while(p)
    {
        //find place for x
        if(p->key == x.key)
            break; 

        if(p->key < x.key)
        {
            q = p;
            p = p->r_child;
        }
        else
        {
            q = p;
            p = p->l_child;
        }
    }

    if(!p)//not found
    {
        printf("Not Found!!\n");
        return;
    }

    if(!p->l_child && !p->r_child)//no child
    {
        if(p == root)//if 'what 2 erase' is root
            root = NULL;
        else if(p == q->l_child)
            q->l_child = NULL;
        else
            q->r_child = NULL;
    }
    else if(!p->r_child)//only 1 child
    {
        if(p == root)//if 'what 2 erase' is root
        {
            root = p->l_child;
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
        if(p == root)//if 'what 2 erase' is root
        {
            root = p->r_child;
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
            p = temp;//4 delete
        }
        else
        {
            p->key = temp->key;
            q->r_child = NULL;
            p = temp;//4 delete
        }

    }
    free(p);
    return;
}