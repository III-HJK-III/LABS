/* 32160320@dankook.ac.kr 권혁준 */

#include "bst.h"

int main(int argc, char *argv[])
{
    if(argc != 2 || )
    {
        printf("[=]Usage[=]\n%s <option_number>\n",argv[0]);
        printf("Options are : \n");
        printf("0 : No Mutex\n");
        printf("1 : With Coarse-grained Lock\n");
        printf("2 : With Fine-grained Lock\n");
        assert(argc != 2);
    }

    int option = atoi(argv[1]);

    void (*ins_f)();//insert function
    void (*rm_f)();//remove function

    switch(option){
        case 0: 
        //no mutex
            printf("Without Mutex\n")
            ins_f = insert;
            rm_f = remove_Xmutex;
            break;

        case 1:
        // w/ coarse
            printf("With Coarse-grained Lock\n")
            break;

        case 2:
        // w/ fine
            printf("With Fine-grained Lock\n")
            break;

        default :
            printf("[=]Usage[=]\n%s <option_number>\n",argv[0]);
            printf("Options are : \n");
            printf("0 : No Mutex\n");
            printf("1 : With Coarse-grained Lock\n");
            printf("2 : With Fine-grained Lock\n");
            assert( (option >= 0) && (option <= 2));
        }

    BST Sephiroth;//our main bst. start point
    init_tree(Sephiroth);
    myArr input_key;
    init_myArr(input_key);

    unsigned int cnt = 0;
    unsigned int ran = 0;
    srand((unsigned)time(NULL);)
    //making 'MAX_NODE' amount of nodes and insert into bst
    printf("Starting Insert......\n")
    printf("Creating %u nodes.......\n",MAX_NODE);
    while(1)
    {
        ran = (((unsigned int)rand()<<15)|rand()) % (unsigned int)(MAX_NODE*4);
        if( ins_f(&Sephiroth, ran) )
            cnt++;
        if(cnt >= MAX_NODE)
            break;
    }
    printf("Done Insert!\n")

    //getting key_vals into input_keys array by inorder trav.
    printf("Starting inorder traversal\n")
    io_trav(Sephiroth, input_keys, MAX_NODE);
    printf("Done inorder traversal\n")

    //tree deleting part, felling root
    printf("Starting Deleting BST......\n")
    while(Sephiroth->root)
        rm_f(Sephiroth->root);
    free(Sephiroth);
    printf("Done Deleting BST!\n")

    return 0;
}