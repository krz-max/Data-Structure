#ifndef _109511028_H_
#define _109511028_H_
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
const char AS[] = "ASSIGN";
const char EX[] = "EXEC";
struct Task{
    char Name;
    Task* next;
    Task* prev;
    Task(char N, Task* Next, Task* Prev):Name(N), next(Next), prev(Prev){;};
};

class Processor{
    private:
        int MaxSize = 1000000;
        int size;
        Task* Qhead;
        Task* Qtail;
        Task* Ehead;
        Task* Etail;
    public:
        char front();
        char back();
        void push(char N);
        void pushE(char N);
        void pop_front();
        void pop_back();
        void PrintQ(ofstream& f_out);
        void PrintE(ofstream& f_out);
        bool empty(){ return size == 0; };
        int Size(){ return size; };
        Processor():size(0), Qhead(NULL), Qtail(NULL), Ehead(NULL), Etail(NULL){;};
        ~Processor();
};

class CPU{
    private:
        Processor* Pros;
        int size;
        int total;
    public:
        void Run(ifstream& f_in, ofstream& f_out);
        int findMax();
        void EXEC(int ID);
        void ASSIGN(char Task, int ID);
        void PrintResult(ofstream& f_out);
        CPU(int N);
        ~CPU();
}; 

bool Strcmp(char* A, const char* B){
    int i = 0;
    while(A[i] == B[i]){
        if(A[i] == '\0' && B[i] == '\0') return true;
	else if(A[i] == '\0' || B[i] == '\0') return false;
	i++;
    }
    return false;
}

char Processor::front(){
    if(size == 0){
        cout << "error" << endl;
        return ' ';
    }
    return Qhead->Name;
}

char Processor::back(){
    if(size == 0){
        cout << "error" << endl;
        return ' ';
    }
    return Qtail->Name;
}

void Processor::push(char N){
    if(Qhead == NULL){
        Qhead = Qtail = new Task(N, NULL, NULL);
    }
    else {
        Qtail->next = new Task(N, NULL, Qtail);
        Qtail = Qtail->next;
    }
    size++;
    return ;
}

void Processor::pushE(char N){
    if(Ehead == NULL){
        Ehead = Etail = new Task(N, NULL, NULL);
    }
    else {
        Etail->next = new Task(N, NULL, Etail);
        Etail = Etail->next;
    }
    return ;
}

void Processor::pop_front(){
    Task* old = Qhead;
    if(size == 0){
        cout << "error" << endl;
        return ;
    }
    if(size == 1){
        Qtail = Qhead = NULL;
    }
    else{
        Qhead = Qhead->next;
    }
    delete old;
    size--;
    return ;
}

void Processor::pop_back(){
    Task* old = Qtail;
    if(size == 0){
        cout << "error" << endl;
        return ;
    }
    if(size == 1){
        Qtail = Qhead = NULL;
    }
    else{
       Qtail = Qtail->prev;
       Qtail->next = NULL;
    }
    delete old;
    size--;
    return ;
}

void Processor::PrintQ(ofstream& f_out){
    Task* walkPtr = Qhead;
    while(walkPtr){
        f_out << walkPtr->Name;
        walkPtr = walkPtr->next;
    }
    f_out << endl;
}

void Processor::PrintE(ofstream& f_out){
    Task* walkPtr = Ehead;
    while(walkPtr){
        f_out << walkPtr->Name;
        walkPtr = walkPtr->next;
    }
    f_out << endl;
}

Processor::~Processor(){
    //cout << "Pdes\n";
    Task* walkPtr = Qhead;
    if(walkPtr){
        while(walkPtr->next){
            walkPtr = walkPtr->next;
            delete walkPtr->prev;
        }
        delete walkPtr;
    }
    walkPtr = Ehead;
    if(walkPtr){
        while(walkPtr->next){
            walkPtr = walkPtr->next;
            delete walkPtr->prev;
        }
        delete walkPtr;
    }
}

void CPU::Run(ifstream& f_in, ofstream& f_out){
    //stringstream ss;
    char command[7];
    int ID; char Name;
    f_in.ignore();
    while(f_in >> command){
        cout << 1;
        if(Strcmp(command, EX)){
            f_in >> ID;
            cout << " " << ID << endl;
            EXEC(ID);
        }
        else if(Strcmp(command, AS)){
            f_in >> ID >> Name;
            cout << " " << ID << " " << Name << endl;
            ASSIGN(Name, ID);
        }
        else{
            PrintResult(f_out);
            return ;
        }
        f_in.ignore();
    }
    return ;
}
    
int CPU::findMax(){
    int M = size-1;
    for(int i = size-2; i >= 0; i--){
        if(Pros[i].Size() >= Pros[M].Size()){
            M = i;
        }
    }
    return M;
}
    
void CPU::EXEC(int ID){
    if(total == 0) {
        cout << "EXEC when no tasks" << endl;
        cout << "error" << endl;
        return ;
    }
    if(Pros[ID-1].empty()){
        int M = findMax();
        Pros[ID-1].pushE(Pros[M].back());
        Pros[M].pop_back();
        total--;
        return ;
    }
    Pros[ID-1].pushE(Pros[ID-1].front());
    Pros[ID-1].pop_front();
    total--;
    return ;
}
    
void CPU::ASSIGN(char Task, int ID){
    Pros[ID-1].push(Task);
    total++;
}

void CPU::PrintResult(ofstream& f_out){
    f_out << "Queueing\n";
    for(int i = 0; i < size; i++){
        f_out << i+1 << " ";
        Pros[i].PrintQ(f_out);
    }
    f_out << "Executed\n";
    for(int i = 0; i < size; i++){
        f_out << i+1 << " ";
        Pros[i].PrintE(f_out);
    }
    return ;
}

CPU::CPU(int N){
    size = N;
    total = 0;
    Pros = new Processor [N];
}
    
CPU::~CPU(){
    delete [] Pros;
}
#endif
