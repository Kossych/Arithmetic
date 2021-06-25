#include "AC.h"

unsigned short l0=l, h0=h;

int main(){
    ifstream fin("Encode.txt", ios::binary);
    if(!fin.is_open()){cout<<"error"; return 0;}
    ofstream fout("Decode.txt", ios::binary);
    if(!fout.is_open()){cout<<"error"; return 0;}

    map<char,int>m;
    unsigned long long len=HeadReader(&m,fin);


    list<Range> t=CreateList(m);
    PrintList(t);
    list<Range>::iterator it;

	int delitel=t.back().R;
	unsigned short value=(fin.get()<<8)|fin.get();	
	char tmp=fin.get();
	int count = 0;
	int q=0;
    while (len)
	{
		int d=h0-l0+1;
		unsigned int freq =(((((unsigned long long)value - l0 + 1) * delitel)) - 1)/(d);
		for (it = t.begin(); it->R <= freq; it++);
		
        h0 = l0 + it->R * d/delitel-1;
		l0 = l0 + it->L * d/delitel;
		for (;;)
		{								
			if (h0 < Half);
			else if (l0 >= Half)
			{
				value -= Half;
				l0 -= Half;
				h0 -= Half;
			}
			else if ((l0 >= First_qtr) && (h0 < Thride_qtr))
			{
				value -= First_qtr;
				l0 -= First_qtr;
				h0 -= First_qtr;
			}
			else break;
			l0<<=1;
			h0<<=1;
			h0++;
			value<<=1;
			value+=((tmp&(1<<(7-count)))>>(7-count));
			count++;
			//cout<<it->c<<" : "<<l0<<" - "<<h0<<endl;
			if (count == 8)
			{
				tmp = fin.get();
				count = 0;
			}
		}
		fout<<it->c;
		len--;
	}

    fin.close();
    fout.close();
}


