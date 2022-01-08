#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

class MyQuickSort
{
private:
    vector<int> List;
    int stepcount;
public:
    MyQuickSort();
    ~MyQuickSort(){;};
    void insert(int num);
    void printList();
    void printList(ofstream &f_out);
    int Partition(int front, int end);
    void QuickSort(int front, int end);
    void Run(ofstream& f_out);
};

MyQuickSort::MyQuickSort()
{
    stepcount = 0;
    List.push_back(-1);
}


inline void MyQuickSort::insert(int num)
{
    List.push_back(num);
    return ;
}

inline void MyQuickSort::printList()
{
    for(int i = 1; i < List.size(); i++)
    {
        cout << List[i] << " ";
    }
    cout << endl;
    return ;
}

inline void MyQuickSort::printList(ofstream &f_out)
{
    for(int i = 1; i < List.size(); i++)
    {
        f_out << List[i] << " ";
    }
    f_out << endl;
    return ;
}

inline int MyQuickSort::Partition(int front, int end)
{
    int pivot = List[front];
    int i = front;
    int j = end+1;
    do{
        while(i < end && List[++i] < pivot);
        while(List[--j] > pivot);
        if(i < j)
        {
            int temp = List[i];
            List[i] = List[j];
            List[j] = temp;
            stepcount++;
        }
    }while(i < j);
    if(j != front)
    {
        int temp = List[j];
        List[j] = pivot;
        List[front] = temp;
        stepcount++;
    }
    return j;
}

inline void MyQuickSort::QuickSort(int front, int end)
{
    if(front < end && end < List.size())
    {
        int pivot = Partition(front, end);
        QuickSort(front, pivot-1);
        QuickSort(pivot+1, end);
    }
}

inline void MyQuickSort::Run(ofstream& f_out){
    QuickSort(1, List.size()-1);
    f_out << stepcount << endl;
}
