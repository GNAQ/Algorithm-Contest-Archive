#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<iterator>
#include<algorithm>
#include<queue>
#include<vector>
using namespace std;

int n,opt,seq[500010]={0},val,pos,typ,fwt[500010]={0};

inline void readx(int& x)
{
	x=0; int k=1; register char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

inline void update()
{
	while (pos<=n)
	{
		fwt[pos]+=val;
		pos+=(pos&(-pos));
	}
}
inline int query(int posx)
{
	int ret=0;
	while (posx)
	{
		ret+=fwt[posx];
		posx-=(posx&(-posx));
	}
	return ret;
}

int main()
{
	readx(n); readx(opt);
	for (int i=1;i<=n;i++) 
	{
		readx(seq[i]);
		pos=i; val=seq[i]; update();
	}
	for (int i=1;i<=opt;i++)
	{
		readx(typ);
		if (typ==1)
		{
			readx(pos); readx(val);
			update();
		}
		else
		{
			readx(pos); readx(val);
			printf("%d\n",query(val)-query(pos-1));
		}
	}
	return 0;
}
