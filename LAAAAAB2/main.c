/* 32160320@dankook.ac.kr 권혁준 */

#include "bst.h"

int main(int argc, char *argv[])
{
    if(argc != 2 || )
    {
        printf("[=]Usage[=]\n%s <option_number>\n",argv[0]);
        printf("Options are : \n");
        printf("0 : No Mutex Multi-Thread\n");
        printf("1 : With Coarse-grained Lock Multi-Thread\n");
        printf("2 : With Fine-grained Lock Multi-Thread\n");
        printf("3 : No Mutex Single-Thread\n");
        assert(argc != 2);
    }

    int option = atoi(argv[1]);

    bool (*ins_f)(BST*,unsigned int);//insert function
    bool (*rm_f)(BST*,unsigned int);//remove function

    switch(option){
        case 0: 
            printf("BST by Multi-Thread Without Mutex\n")
            ins_f = insert_Xmutex;
            rm_f = remove_Xmutex;
            break;

        case 1:
            printf("BST by Multi-Thread With Coarse-grained Lock\n")
            ins_f = insert_CoarseLcok;
            rm_f = remove_cg;
            break;

        case 2:
            printf("BST by Multi-Thread With Fine-grained Lock\n")
            ins_f = insert_FineLock;
            rm_f = remove_fg;
            break;

        case 3:
            printf("BST by Single-Thread\n");
            ins_f = insert_Xmutex;
            rm_f = remove_Xmutex;
            break;

        default :
            printf("[=]Usage[=]\n%s <option_number>\n",argv[0]);
            printf("Options are : \n");
            printf("0 : No Mutex Multi-Thread\n");
            printf("1 : With Coarse-grained Lock Multi-Thread\n");
            printf("2 : With Fine-grained Lock Multi-Thread\n");
            printf("3 : No Mutex Single-Thread\n");
            return -1;
        }

    BST Sephiroth;//our main bst. start point
    init_tree(Sephiroth);
    myArr input_key;
    init_myArr(input_key);
    myCounter myCnt;

    unsigned int *data = (unsigned int*)malloc(sizeof(unsigned int)*MAX_NODE);
    assert(data != NULL);
    rand_gen(data, MAX_NODE);

    //making 'MAX_NODE' amount of nodes and insert into bst

    if(option == 3)
    {
        unsigned int i = 0;
        unsigned int test = 0;

        printf("Starting Insert......\n")
        printf("Creating %u nodes.......\n",MAX_NODE);
        for(i = 0; i < MAX_NODE, i++)
        {
            test = ins_f(Sephiroth, data[i]);
            assert(!test);
        }
        printf("Done Insert!\n")

        //getting key_vals into input_keys array by inorder trav. instead of printing it out
        printf("Starting inorder traversal\n")
        io_trav(Sephiroth, input_keys, MAX_NODE);
        printf("Done inorder traversal\n")

        //tree deleting part, felling root
        printf("Starting Deleting BST......\n")


        printf("Done Deleting BST!\n")
    }
    else
    {
        printf("Starting Insert......\n")
        printf("Creating %u nodes.......\n",MAX_NODE);

        printf("Done Insert!\n")

        //getting key_vals into input_keys array by inorder trav. instead of printing it out
        printf("Starting inorder traversal\n")
        io_trav(Sephiroth, input_keys, MAX_NODE);
        printf("Done inorder traversal\n")

        //tree deleting part, felling root
        printf("Starting Deleting BST......\n")
        while(Sephiroth->root)
            rm_f(Sephiroth->root);
        printf("Done Deleting BST!\n")
    }


    return 0;
}