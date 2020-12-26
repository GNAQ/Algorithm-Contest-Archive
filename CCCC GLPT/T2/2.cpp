#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<vector>
#include<map>
#include<set>
using namespace std;

int D,P;
struct Per
{
	int next,sta;
	string id,name;
	
	Per()
	{
		next=-1;
		sta=0;
		id.clear();
		name.clear();
	}
};
Per per[30010];
int cnt=0;

map<string, int> id_to_per;

struct Rec
{
	string id,name,time;
	int sta,tim,stamp;
};
Rec rec[30010]; int cnt2=0;
vector<Per> illed;

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

void gnaqread(char *p)
{
	char ch=0;
	while ((ch=getchar())!='\n')
	{
		*p=ch;
		p++;
	}
}

bool Valid(int i)
{
	if (rec[i].id.length()==18)
	{
		for (int j=0;j<18;j++)
		{
			if (rec[i].id[j]<'0' || rec[i].id[j]>'9') return false;
		}
		return true;
	}
	return false;
}

bool cmp(Rec a, Rec b)
{
	if (a.tim<b.tim) return true;
	if (a.tim==b.tim) return a.stamp<b.stamp;
	return false;
}

int main()
{	
	readx(D); readx(P);
	for (int dd=1;dd<=D;dd++)
	{
		int S,T; 
		readx(T); readx(S);
		for (int i=1;i<=T;i++)
		{
			cin>>rec[i].name>>rec[i].id>>rec[i].sta>>rec[i].time;
			rec[i].tim=(rec[i].time[0]-'0')*1000+
						  (rec[i].time[1]-'0')*100+
						  (rec[i].time[3]-'0')*10+
						  (rec[i].time[4]-'0');
			rec[i].stamp=i;
			
			if (Valid(i) && rec[i].sta)
			{
				int vis=id_to_per[rec[i].id];
				if (!vis)
				{
					vis=id_to_per[rec[i].id]=++cnt;
					per[cnt].id=rec[i].id;
					per[cnt].name=rec[i].name;
					per[cnt].sta=0;
					per[cnt].next=-1;
				}
				if (!per[vis].sta)
				{
					per[vis].sta=1;
					illed.push_back(per[vis]);
				}
			}
		}
		
		sort(rec+1,rec+T+1,cmp);
		for (int i=1;i<=T;i++)
		{
			if (S==0) break;
			if (Valid(i))
			{
				int vis=id_to_per[rec[i].id];
				if (!vis)
				{
					id_to_per[rec[i].id]=++cnt;
					vis=cnt;
					per[vis].id=rec[i].id;
					per[vis].name=rec[i].name;
				}
				if (dd>=per[vis].next)
				{
					per[vis].next=dd+P+1;
					cout<<per[vis].name<<" "<<per[vis].id<<endl;
					S--;
				}
			}
		}
	}
	
	int siz=illed.size(); //cout<<"siz="<<siz<<endl;
	for (int i=0;i<siz;i++) 
	{
		cout<<illed[i].name<<" "<<illed[i].id<<endl;
	}
	return 0;
}
