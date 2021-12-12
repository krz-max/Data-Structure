#include "109511028.h"

int main(int argc, char **argv){
    ifstream f_in(argv[1]);
    ofstream f_out(argv[2]);
    MaxHeap demo;
    int command;
    while(f_in >> command){
        switch (command)
        {
        case 0:
            int val;
            f_in >> val;
            demo.insert(val);
            break;
        case 1:
            demo.getMax();
            break;
        case 2:
            demo.Levelorder(f_out);
            break;
        case 3:
            demo.Preorder(f_out);
            break;
        case 4:
            demo.Inorder(f_out);
            break;
        default:
            demo.Postorder(f_out);
            break;
        }
    }

    return 0;
}