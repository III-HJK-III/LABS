#include "bst.h"


//for initializing node
void init_node(Node* nd, unsigned int val)
{
    nd -> l_child = NULL;
    nd -> r_child = NULL;
    nd -> key = val;
} 