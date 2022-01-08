#include "109511028.h"
using namespace std;

int main(int argc, char** argv){
    ifstream f_in(argv[1]);
    ofstream f_out(argv[2]);
    int command;
    PolynomialList MyPL;
    while(f_in >> command){
        if(command == 0){
            int terms;
            f_in >> terms;
            Polynomial temp;
            while(terms--){
                int co, x, y, z;
                f_in >> co >> x >> y >> z;
                temp.insert(Term(co, x, y, z));
            }
            MyPL.Append(temp);
        }
        else if(command == 4){
            int index;
            f_in >> index;
            MyPL.Del(index);
        }
        else{
            int index1, index2;
            f_in >> index1 >> index2;
            if(command == 1){
                MyPL.Add(index1, index2);
            }
            if(command == 2){
                MyPL.Sub(index1, index2);
            }
            if(command == 3){
                MyPL.Mul(index1, index2);
            }
        }
    }
    MyPL.printResult(f_out);
    f_in.close();
    f_out.close();
    return 0;
}
