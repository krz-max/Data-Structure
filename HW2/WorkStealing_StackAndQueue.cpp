#include "109511028.h"
using namespace std;

int main(int argc, char **argv){
    ifstream f_in(argv[1]);
    ofstream f_out(argv[2]);
    int N;
    f_in >> N;
    CPU MyCPU(N);
    MyCPU.Run(f_in, f_out);
    f_in.close();
    f_out.close();
}
