#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include "SparseMatrix.h"

using namespace std;


int main(int argc, char** argv){
    ifstream f_in(argv[1]);
    ofstream f_out(argv[2]);
    string line;
    stringstream ss;
    getline(f_in, line); //A ;
    vector<MatrixTerm> a;
    int Ra{}, Ca{};
    while(getline(f_in, line)){
        int j{};
        ss.str(line);
        int num;
        ss >> num;
        if(!ss) break;
        do{
            if(num != 0){
                a.push_back(MatrixTerm(Ra, j, num));
            }
            j++;
        }while(ss >> num && ss);
        Ra++;
        Ca = max(Ca, j);
        ss.str("");
        ss.clear();
    }
    ss.str("");
    ss.clear();
    vector<MatrixTerm> b;
    int Rb{}, Cb{};
    while(getline(f_in, line)){
        int j{};
        ss.str(line);
        int num;
        ss >> num;
        if(!ss) break;
        do{
            if(num != 0){
                b.push_back(MatrixTerm(Rb, j, num));
            }
            j++;
        }while(ss >> num && ss);
        Rb++;
        Cb = max(Cb, j);
        ss.str("");
        ss.clear();
    }
    Matrix A(Ra, Ca, a);
    Matrix B(Rb, Cb, b);
	if(Ca == Rb){
        B = B.Transpose();
        Matrix C = A.Mul(B);
        C.PrintMatrix(f_out);
    }
    else if(Ra == Rb){
        A = A.Transpose();
        B = B.Transpose();
        Matrix C = A.Mul(B);
        C.PrintMatrix(f_out);
    }
    else if(Ca == Cb){
        Matrix C = A.Mul(B);
        C.PrintMatrix(f_out);
    }
    else {
        A = A.Transpose();
        Matrix C = A.Mul(B);
        C.PrintMatrix(f_out);
    }
    
    return 0;
}
