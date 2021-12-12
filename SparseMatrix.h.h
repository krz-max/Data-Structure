#ifndef _SPARSEMATRIX_H_
#define _SPARSEMATRIX_H_
#include <fstream>
#include <vector>
#include <sstream>
#include <iostream>
using namespace std;

struct MatrixTerm{
    int row{};
    int col{};
    int value{};
    MatrixTerm(){};
    MatrixTerm(int R, int C, int V):row(R), col(C), value(V){};
};

class Matrix{
    public:
        int Rows{};
        int Cols{};
        int Terms{};
        vector<MatrixTerm> smArray;
        Matrix(int R, int C):Rows(R), Cols(C), Terms(0){};
        Matrix(int R, int C, int T);
        Matrix(int R, int C, vector<MatrixTerm>& temp);
        Matrix Transpose();
        Matrix Mul(Matrix& B);
        void Insert(int R, int C, int val);
        void PrintMatrix(ofstream& f_out);
        void PrintMatrix();
};
Matrix::Matrix(int R, int C, vector<MatrixTerm>& temp){
    Terms = temp.size();
    Rows = R;
    Cols = C;
    smArray = temp;
}

Matrix::Matrix(int R, int C, int T){
    Rows = R;
    Cols = C;
    Terms = T;
    smArray = vector<MatrixTerm>(T, MatrixTerm(0, 0, 0));
}
void Matrix::Insert(int R, int C, int val){
    smArray.push_back(MatrixTerm(R, C, val));
    Terms++;
}

Matrix Matrix::Transpose(){
    int *RowSize = new int [Cols];
    int *RowStart = new int [Cols];
	if(Terms == 0) return Matrix(Cols, Rows);
    Matrix b(Cols, Rows, Terms);
    
    if(Terms > 0){
        for(int i = 0; i < Cols; i++) RowSize[i] = 0;
        for(int i = 0; i < Terms; i++) RowSize[smArray[i].col]++;
        
        RowStart[0] = 0;
        for(int i = 1; i < Cols; i++){
            RowStart[i] = RowStart[i-1] + RowSize[i-1];
        }
        for(int i = 0; i < Terms; i++){
            int j = RowStart[smArray[i].col];
            b.smArray[j].row = smArray[i].col;
            b.smArray[j].col = smArray[i].row;
            b.smArray[j].value = smArray[i].value;
            RowStart[smArray[i].col]++;
        }
    }
    delete RowSize;
    delete RowStart;
    return b;
}

Matrix Matrix::Mul(Matrix& B){

    Matrix c(Rows, B.Rows);

    int res_R, res_C;
	int i, j;
    for(i = 0; i < Terms;){
        res_R = smArray[i].row;
        for(j = 0; j < B.Terms;){
            res_C = B.smArray[j].row;
            int apos = i;
            int bpos = j;

            int sum = 0;
            while(bpos < B.Terms && apos < Terms
            && smArray[apos].row == res_R && res_C == B.smArray[bpos].row){
                if(smArray[apos].col > B.smArray[bpos].col)
                    bpos++; 
                else if(smArray[apos].col < B.smArray[bpos].col)
                    apos++;
                else
                    sum += smArray[apos++].value*B.smArray[bpos++].value;
            }
            if(sum != 0)
                c.Insert(res_R, res_C, sum);
            
            while(j < B.Terms && B.smArray[j].row == res_C)
                j++;
        }
        while(i < Terms && smArray[i].row == res_R)
            i++;
    }
    return c;
}

void Matrix::PrintMatrix(ofstream& f_out){
    int t = 0;
    for(int i = 0; i < Rows; i++){
        for(int j = 0; j < Cols; j++){
            if(t < Terms && i == smArray[t].row && j == smArray[t].col){
                f_out << smArray[t++].value ;
            }
            else f_out << 0;
            if(j != Cols-1) f_out << " ";
        }
        f_out << " ;" << endl;
    }
}

void Matrix::PrintMatrix(){
    for(int i = 0; i < Terms; i++){
        cout << smArray[i].row << " " << smArray[i].col << " " << smArray[i].value << endl;
    }
}
#endif
