#include "109511028.h"
using namespace std;

int main(int argc, char** argv)
{
    ifstream f_in1(argv[1]), f_in2(argv[2]);
    ofstream f_out(argv[3]);
    MyHash Test;
    string Temp;
    while(f_in1 >> Temp)
    {
        Test.Insert(Temp);
    }
    while(f_in2 >> Temp)
    {
        Test.Search(Temp, f_out);
    }
    f_in1.close();
    f_in2.close();
    f_out.close();
    return 0;
}