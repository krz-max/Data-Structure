#include <fstream>
#include <iostream>
using namespace std;

class MyQuickSort
{
private:
    int* data;
    int size;
    int capacity;
    int stepcount;
public:
    MyQuickSort();
    ~MyQuickSort();
    void insert(int num);
    void printList();
    void QuickSort();
    void swap(int *a, int *b);
    int Partition(int front, int end);
    void QuickSort(int front, int end);
    void Run();
};

MyQuickSort::MyQuickSort()
{
    stepcount = size = 0;
    capacity = 4;
    data = new int [capacity];
}

MyQuickSort::~MyQuickSort()
{
    delete [] data;
}

void MyQuickSort::insert(int num)
{
    if(size == capacity)
    {
        int* copy = new int [2*capacity];
        for(int i = 0; i < capacity; i++)
        {
            copy[i] = data[i];
        }
        delete [] data;
        data = copy;
    }
    data[size++] = num;
    return ;
}

void MyQuickSort::printList()
{
    for(int i = 0; i < size; i++)
    {
        cout << data[i] << " " ;
    }
    cout << endl;
    return ;
}

int MyQuickSort::Partition(int front, int end)
{
    int pivot = data[front];
    int i = front;
    for(int j = front+1; j <= end; j++)
    {
        if(data[j] < pivot){
            int temp = data[j-1];
            data[j-1] = data[j];
            data[j] = temp;
            stepcount++;
            i++;
        }
    }
    if(data[i] != pivot){
        int temp = data[i];
        data[i] = pivot;
        data[front] = temp;
        stepcount++;
    }
    return i;
}

void MyQuickSort::QuickSort(int front, int end)
{
    if(front < end && end < size)
    {
        int pivot = Partition(front, end);
        QuickSort(front, pivot-1);
        QuickSort(pivot+1, end);
    }
}

void MyQuickSort::Run(){
    QuickSort(0, size-1);
    cout << stepcount << endl;
}