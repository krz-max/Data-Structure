#include "QuickSort.h"


int main(int argc, char** argv)
{
    ifstream f_in(argv[1]);
    ofstream f_out(argv[2]);
    MyQuickSort Test;
    int num;
    while(f_in >> num)
    {
        Test.insert(num);
    }
    //Test.printList();
    Test.Run(f_out);
    //Test.printList(f_out);
    f_out.close();
    f_in.close();
    return 0;
}
