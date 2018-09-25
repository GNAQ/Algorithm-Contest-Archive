#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<iterator>
#include<queue>
#include<vector>
using namespace std;

int n,opt,typ,fwt[100010]={0},seq[1000010]={0};
int cache1,cache2;

inline void readx(int& x)
{
	x=0; int k=1; register char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

inline void update(int pos,int val)
{
	while (pos<=n)
	{
		fwt[pos]=max(fwt[pos],val);
		for (int w=1;w<(pos&(-pos));w<<=1) fwt[pos]=max(fwt[pos],fwt[pos-w]);
		pos+=(pos&(-pos));
	}
}
inline int query(int lx,int rx)
{
	int ans=0;
	while (rx>=lx)
	{
		ans=max(ans,seq[rx]);
		for (rx--;rx-lx>=(rx&(-rx));rx-=(rx&(-rx))) ans=max(ans,fwt[rx]);
	}
	return ans;
}

int main()
{
	readx(n); readx(opt);
	for (int i=1;i<=n;i++) readx(seq[i]);
	for (int i=1;i<=n;i++) update(i,seq[i]);
	for (int i=1;i<=opt;i++)
	{
		readx(typ);
		if (typ==1)
		{
			readx(cache1); readx(cache2); seq[cache1]=cache2;
			update(cache1,cache2);
		}
		else
		{
			readx(cache1); readx(cache2);
			printf("%d\n",query(cache1,cache2));
		}
	}
	return 0;
}
