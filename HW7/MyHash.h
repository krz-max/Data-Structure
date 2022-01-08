#ifndef _109511028_H_
#define _109511028_H_
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <tr1/unordered_map>
using std::tr1::unordered_map;
using namespace std;

class MyHash{
    private:
        unordered_map<string, vector<string> > Table;
    public:
        MyHash(){;};
        ~MyHash(){;};
        void Insert(string D);
        void Search(string Target, ofstream& f_out);
};

static inline void Sort(string& s)
{
    vector<int> T(26, 0);
    int t = s.length();
    for(int i = 0; i < t; i++)
    {
        T[s[i]-'a']++;
    }
    int j = 0;
    for(int i = 0; i < 26; i++)
    {
        while(T[i]--)
        {
            s[j++] = char('a'+i);
        }
    }
}

void MyHash::Insert(string D)
{
    string temp(D);
    Sort(temp);
    Table[temp].push_back(D);
    return ;
}
void MyHash::Search(string Target, ofstream& f_out)
{
    Sort(Target);
    if(Table[Target].size() == 0)
    {
        f_out << 0 << endl;
        return ;
    }
    for(int i = 0; i < Table[Target].size(); i++)
    {
        f_out << Table[Target][i] << " ";
    }
    f_out << endl;
    return ;
}

#endif
