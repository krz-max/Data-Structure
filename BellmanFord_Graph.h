#include <fstream>
#include <vector>
#include <stack>
#include <iostream>
using namespace std;

struct edge{
    int start;
    int Dest;
    int weight;
    edge(int a, int b, int c):start(a), Dest(b), weight(c){;};
};

class GRAPH_BF{
    private:
        int numOfVertex;
        vector<vector<int> > AdjMatrix;
        vector<int> Dist;
        vector<int> pred;
        vector<edge> Edges;
        bool NegCycle;
    public:
        GRAPH_BF(int n, vector<vector<int> >& adjMat);
        void BellmanFord(ofstream& f_out);
        void printResult(ofstream& f_out);
        void test();
};
GRAPH_BF::GRAPH_BF(int n, vector<vector<int> >& adjMat){
    numOfVertex = n;
    AdjMatrix.resize(n);
    for(int i = 0; i < n; i++){
        AdjMatrix[i].resize(n);
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            AdjMatrix[i][j] = adjMat[i][j];
            if(AdjMatrix[i][j] != 0){
                Edges.push_back(edge(i, j, AdjMatrix[i][j]));
            }
        }
    }
    Dist.resize(n);
    pred.resize(n);
    Dist[0] = 0;
    pred[0] = -1;
    for(int i = 1; i < n; i++){
        Dist[i] = (AdjMatrix[0][i] == 0) ? 2000000000 : AdjMatrix[0][i]; // set initial distance to source vertex
        pred[i] = (AdjMatrix[0][i] == 0) ? -1 : 0;
    }
    NegCycle = false;
}

void GRAPH_BF::BellmanFord(ofstream& f_out){
    for(int i = 2; i < numOfVertex; i++){
        vector<int> dup(Dist.begin(), Dist.end());
        for(int j = 0; j < Edges.size(); j++){
            //if(Dist[Edges[j].start] < INT32_MAX && Edges[j].Dest != i-1){ // if the vertex is reachable
            if(Dist[Edges[j].start] < 2000000000 && Dist[Edges[j].start] + Edges[j].weight < Dist[Edges[j].Dest]){
                Dist[Edges[j].Dest] = Dist[Edges[j].start]+Edges[j].weight;
                pred[Edges[j].Dest] = Edges[j].start;
            }
            //}
        }
        bool check = false;
        for(int i = 0; i < dup.size(); i++){
            if(dup[i] != Dist[i]){
                check = true;
            }
        }
        if(check) break;
    }
    for(int j = 0; j < Edges.size(); j++){
        if(Dist[Edges[j].start] + Edges[j].weight < Dist[Edges[j].Dest]){
            pred[Edges[j].Dest] = Edges[j].start;
            NegCycle = true;
            
            stack<int> rev;
            rev.push(Edges[j].start);
            int walk = pred[Edges[j].start];
            while(walk != Edges[j].start){
                rev.push(walk);
                //cout << walk << "-";
                walk = pred[walk];
            }
            rev.push(Edges[j].start);
            while(rev.size() != 1){
                f_out << rev.top() << "-";
                rev.pop();
            }
            f_out << rev.top() << endl;
            return ;
        }
    }
}

void GRAPH_BF::printResult(ofstream& f_out){
    if(NegCycle) return ;
    for(int i = 0; i < numOfVertex; i++){
        stack<int> rev;
        if(pred[i] != -1){
            int j = i;
            while(pred[j] != -1){
                rev.push(j);
                //cout << j << "-";
                j = pred[j];
            }
            rev.push(j);
            //cout << j << " " << Dist[i] << endl;
            while(rev.size() != 1){
                f_out << rev.top() << "-";
                rev.pop();
            }
            f_out << rev.top() << " " << Dist[i] << endl;
        }
    }
    return ;
}

void GRAPH_BF::test(){ //OK
    cout << "numOfVertex: " << numOfVertex << endl;
    cout << "AdjMatrix: " << endl;
    for(int i = 0; i < numOfVertex; i++){
        for(int j = 0; j < numOfVertex; j++){
            cout << AdjMatrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << "Dist: " << endl;
    for(int i = 0; i < numOfVertex; i++){
        cout << Dist[i] << " ";
    }
        cout << endl;
    cout << "pred: " << endl;
    for(int i = 0; i < numOfVertex; i++){
        cout << pred[i] << " ";
    }
        cout << endl;
    cout << "Edge: " << endl;
    for(int i = 0; i < Edges.size(); i++){
        cout << Edges[i].start << " " << Edges[i].Dest << " " << Edges[i].weight << endl;
    }
        cout << endl;
}
