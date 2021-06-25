#include <iostream>
#include <list>
#include <map>
#include <vector>
#include <stdbool.h>
#include <iterator>
#include <fstream>


using namespace std;


class Range{
    public:
    unsigned int a;
    int L, R;
    char c;

    Range();
    Range(char, int);
    void PrintRange();
};

static bool comp(Range &l, Range&r){
    return l.a>r.a;    
}

Range::Range(char _c,int _a){
    c=_c;
    a=_a;
}

list<Range> CreateList(map<char,int>&m){
    list<Range> ls;
    for(auto it=m.begin(); it!=m.end(); it++){
        Range p(it->first, it->second);
        ls.push_back(p);
    }
    ls.sort(comp);
    int tmp=0;
    for(auto it=ls.begin();it!=ls.end();it++){
        it->L=tmp;
        it->R=tmp+it->a;
        tmp=it->R;
    }
    return ls;
}

 unsigned long long HeadReader(map<char,int> *MK, ifstream& fin){
    int key, q;
    unsigned long long len=0;
    fin.read((char*)&q,sizeof(q));
    char s;
    for(int i=0;i<q;i++){
        fin.read((char*)&s, sizeof(s)); fin.read((char*)&key,sizeof(key));
        (*MK)[s]=key;
        len+=key;
    }

    return len;
}

void Range::PrintRange(){
    cout<<c<<" : "<<L<<" - "<<R<<endl;
}

void PrintList(list<Range> ls){
    for(auto it=ls.begin();it!=ls.end();it++){
        it->PrintRange();
    }
}

void BitsPlusFollow(ofstream &fout, bool bit, int bits_to_follow, int *count){
    fout.write((char*)&bit, 1);
    for (; bits_to_follow > 0; bits_to_follow-- ){
        fout.write((char*)&bit, 1);
    }
}

const unsigned short l=0, h=-1; 
const unsigned short First_qtr = (h + 1) / 4;
const unsigned short Half = First_qtr * 2;
const unsigned short Thride_qtr = First_qtr * 3;
