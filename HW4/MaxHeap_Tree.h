#ifndef _109511028_H_
#define _109511028_H_
#include <vector>
#include <iostream>
#include <fstream>
#include <stack>
#include <queue>

using namespace std;

class MaxHeap{
    private:
        vector<int> data;

        int left(int index) { return index<<1; };
        int right(int index) { return (index<<1)+1; };
        int parent(int index) { return index>>1; };
    
    public:
        MaxHeap();
        ~MaxHeap(){;};

        void _reHeapDown(int index);
        int getMax();

        void _reHeapUp(int index);
        void insert(int val);

        void Inorder(ofstream& f_out);
        void Preorder(ofstream& f_out);
        void Postorder(ofstream& f_out);
        void Levelorder(ofstream& f_out);
};

MaxHeap::MaxHeap(){
    data = {-999};
}

int MaxHeap::getMax(){
    if(data.size() == 1){
        cout << "The heap is empty\n";
        return -1;
    }
    int temp = data[1];
    data[1] = data[data.size()-1];
    data.pop_back();
    _reHeapDown(1);
    return temp;
}

void MaxHeap::_reHeapDown(int index){
    int swapIndex = index;
    if(left(index) < data.size() && data[left(index)] > data[index])
            swapIndex = left(index);
    

    if(right(index) < data.size() && data[right(index)] > data[swapIndex])
            swapIndex = right(index);
    
    
    if(swapIndex != index){
        swap(data[index], data[swapIndex]);
        _reHeapDown(swapIndex);
    }
    return ;
}

void MaxHeap::insert(int val){
    data.push_back(val);
    _reHeapUp(data.size()-1);
    return ;
}

void MaxHeap::_reHeapUp(int index){
    if(index <= 1) return ;

    if(data[parent(index)] < data[index]){
        swap(data[parent(index)], data[index]);
        _reHeapUp(parent(index));
    }

    return ;
}

void MaxHeap::Inorder(ofstream& f_out){
// ->L : Looking for the leftmost child
// L : leftmost child found
// L->V : The left subtree is visited, display itself
// (V-> (!R) ? parent : R) : (Right subtree unvisited) ? go to Right subtree : go to parent;
    vector<int> visited = vector<int>(data.size(), 0);
    visited[0] = 1;
    stack<int> temp;
    int walk = 1, leftDone = 0;
    temp.push(walk);
    while(!temp.empty()){
        if(walk >= data.size()){ // L
            leftDone = 1;
            walk = temp.top();
            temp.pop();
        }
        else if(leftDone && visited[walk] == 0){ // L->V
            f_out << data[walk] << " ";
            visited[walk] = 1;
        }
        else if(leftDone && visited[walk] == 1){ // V -> (!R) ? parent : R;
            if(right(walk) < data.size()){
                leftDone = 0; // back to ->L
                walk = right(walk);
            }
            else{
                walk = temp.top();
                temp.pop();
            }
        }
        else{ // ->L
            temp.push(walk);
            walk = left(walk);
        }
    }
    f_out << endl;
    return ;
}

void MaxHeap::Preorder(ofstream& f_out){
// V : visit the node
// St : put into stack for further use
// V->L : go to left subtree
// L->R : go to right subtree
    vector<int> visited = vector<int>(data.size(), 0);
    visited[0] = 1;
    stack<int> temp;
    int walk = 1;
    temp.push(walk);
    while(!temp.empty()){
        if(visited[walk] == 0){ // V
            f_out << data[walk] << " ";
            visited[walk] = 1;
        }
        if(left(walk) < data.size() && visited[left(walk)] == 0){ // V->L
            temp.push(left(walk)); // St
            walk = left(walk);
        }
        else if(right(walk) < data.size() && visited[right(walk)] == 0){ // L->R
            temp.push(right(walk));
            walk = right(walk);
        }
        else{ // L visited, go to parent. Since the parent is visited, it will only check for each parent's right subtree
            temp.pop();
            if(!temp.empty()) walk = temp.top();
        }
    }
    f_out << endl;    
    return ;
}

void MaxHeap::Postorder(ofstream& f_out){
    vector<int> visited = vector<int>(data.size(), 0);
    visited[0] = 1;
    stack<int> traverse;
    int walk = 1;
    do
    {
        if(walk >= data.size()){
            walk = traverse.top();
            traverse.pop();
            if(!traverse.empty() && traverse.top() == right(walk) && visited[traverse.top()] == 0){ // hasn't traverse the right side
                int temp = walk;
                walk = traverse.top();
                traverse.pop();
                traverse.push(temp);
            }
            else{
                f_out << data[walk] << " ";
                visited[walk] = 1;
                if(!traverse.empty()) walk = data.size();
            }
        }
        else if(walk < data.size()){
            if(right(walk) < data.size()) traverse.push(right(walk));
            traverse.push(walk);
            walk = left(walk);
        }
    }while(!traverse.empty());
    f_out << endl;    
    return ;
}

void MaxHeap::Levelorder(ofstream& f_out){
    vector<int> visited = vector<int>(data.size(), 0);
    visited[0] = 1;
    queue<int> traverse;
    int walk = 1;
    traverse.push(walk);
    while(!traverse.empty()){
        f_out << data[traverse.front()] << " ";
        if(left(walk) < data.size()) traverse.push(left(walk));
        if(right(walk) < data.size()) traverse.push(right(walk));
        traverse.pop();
        walk = traverse.front();
    }
    f_out << endl;    
    return ;
}
#endif