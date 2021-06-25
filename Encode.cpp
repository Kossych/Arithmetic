#include "AC.h"

unsigned short h0=h, l0=l;

int main(){
    ifstream fin("Test.txt", ios::binary);
    if(!fin.is_open()){cout<<"error"; return 0;}
    ofstream fout("Encode.txt", ios::binary);
    if(!fout.is_open()){cout<<"error"; return 0;}

    map<char,int>m;
    list<Range> t;
    char c;
    unsigned long long len=0;
    for(fin.get(c);!fin.eof();fin.get(c)) m[c]++;
    fin.clear();
    fin.seekg(0);

    t=CreateList(m);
    PrintList(t);

    int k=m.size();
    fout.write((char*)&k, sizeof(k));
    for(auto it = m.begin(); it!= m.end(); it++)
    {
        fout.write((char*)&it-> first, sizeof(it-> first)); fout.write((char*)&it -> second,sizeof(it -> second));
    }

    list<Range>::iterator it;
    
    int delitel=t.back().R;
	int bits_to_follow = 0;
	char tmp = 0;
    int count=0;
    char s; 
    while(fin.get(s)){  
        for(it=t.begin(); it->c!=s; it++);  
        int d=h0-l0+1;
        h0 = l0 + it->R * d/delitel-1;
		l0 = l0 + it->L * d/delitel;
        for(;;){
            if(h0<Half){
                count++;
				if (count == 8)
				{
					fout.put(tmp);
					tmp = 0;
					count = 0;
				}
				for (; bits_to_follow > 0; bits_to_follow--)
				{
					tmp = tmp | (1 << (7 - count));
                    count++;
					if (count == 8)
					{
						fout.put(tmp);
						tmp = 0;
						count = 0;
					}
				}
            }
            else if(l0>=Half){
                tmp = tmp | (1 << (7 - count));
				count++;
				if (count == 8)
				{
					fout.put(tmp);
					tmp = 0;
					count = 0;
				}
				for (; bits_to_follow > 0; bits_to_follow--)
				{
                    count++;
					if (count == 8)
					{
						fout.put(tmp);
						tmp = 0;
						count = 0;
					}
				}
                l0-= Half; h0-= Half;

            }
            else if((l0>=First_qtr)&&(h0<Thride_qtr)){
                bits_to_follow++;
				l0 -= First_qtr; h0 -= First_qtr;
            }
            else break;

            l0 <<= 1;
			h0 <<= 1;
            h0++;
           // cout<<it->c<<" : "<<l0<<" - "<<h0<<endl;
        }
    }
    
 
    fin.close();
    fout.close();
}



