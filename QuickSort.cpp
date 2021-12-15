#include "QuickSort.h"


int main(int argc, char** argv)
{
    ifstream f_in(argv[1]);
    MyQuickSort Test;
    int num;
    while(f_in >> num)
    {
        Test.insert(num);
    }
    Test.printList();
    Test.Run();
    Test.printList();
    return 0;
}