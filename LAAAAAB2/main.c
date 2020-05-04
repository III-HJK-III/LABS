/* 32160320@dankook.ac.kr 권혁준 */

#include "bst.h"

int main(int argc, char *argv[])
{
    if(argc != 2 || )
    {
        printf("[=]Usage[=]\n%s 0/1/2\n",argv[0]);
        assert(argc != 2);
    }

    int option = atoi(argv[1]);

    void (*ins_f)();//insert function
    void (*rm_f)();//remove function

    switch(option){
        case 0: 
        //no mutex
            break;

        case 1:
        // w/ coarse
            break;

        case 2:
        // w/ fine
            break;

        default :
            printf("[=]Usage[=]\n%s 0/1/2\n",argv[0]);
            printf("0 : No Mutex\n
                    1 : With Coarse-grained Lock\n
                    2 : With Fine-grained Lock\n");
            assert( (option >= 0) && (option <= 2));
        }

    BST Sephiroth;//our main bst. start point
    init_tree(Sephiroth);
    myArr input_key;
    init_myArr(input_key);

    //making 'MAX_NODE' amount of nodes and insert into bst
    while(1)
    {
        //insert thing happens
    }

    //getting key_vals into input_keys array
    assert( io_trav(Sephiroth, input_keys, MAX_NODE) );

    

}