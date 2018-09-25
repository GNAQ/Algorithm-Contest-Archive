#include<cstdio>
#include<iostream>
#include<string>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<iterator>
#include<queue>
#include<vector>
using namespace std;

int n,seq[500010]={0},opt,typ,val,lx,rx,fwt[500010]={0};

inline void readx(int& x)
{
	x=0; int k=1; register char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

inline void update(int pos)
{
	while (pos<=n)
	{
		fwt[pos]+=val;
		pos+=(pos&(-pos));
	}
}
inline int queryx(int pos)
{
	int ret=0;
	while (pos)
	{
		ret+=fwt[pos];
		pos-=(pos&(-pos));
	}
	return ret;
}

int main()
{
	readx(n); readx(opt);
	for (int i=1;i<=n;i++) readx(seq[i]);
	for (int i=1;i<=opt;i++)
	{
		readx(typ);
		if (typ==1)
		{
			readx(lx); readx(rx); readx(val);
			update(lx); val=-val; update(rx+1);
		}
		else
		{
			readx(lx);
			printf("%d\n",seq[lx]+queryx(lx));
		}
	}
	return 0;
}
