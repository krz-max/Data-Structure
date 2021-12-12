#include "109511028.h"
#include <sstream>
using namespace std;

int main(int argc, char** argv){
    ifstream f_in(argv[1]);
    ofstream f_out(argv[2]);
    vector<vector<int> > input;
    string test;
    stringstream ss;
    while(getline(f_in, test)){
        ss.str(test);
        int adj;
        vector<int> temp;
        while(ss >> adj){
            temp.push_back(adj);
        }
        input.push_back(temp);
        ss.str("");
        ss.clear();
    }
    GRAPH_BF MyBF(input.size(), input);
//    cout << 1;
//    MyBF.test();
    MyBF.BellmanFord(f_out);
    MyBF.printResult(f_out);
    return 0;
}
