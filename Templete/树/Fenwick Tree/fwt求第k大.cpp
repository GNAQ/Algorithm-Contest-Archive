#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<iterator>
#include<cstdlib>
#include<queue>
#include<vector>
using namespace std;

int n,opt,typ,pos,val;
int fwt[100010]={0},

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
		fwt[pos]+=val;
		pos+=(pos&(-pos));
	}
}

inline void kth_small(int k)
{
	int pos=0;
	for (int w=22;w>=0;w--) if (pos+(1<<w)<=n && fwt[pos+(1<<w)]<k)
	{
		pos+=(1<<i);
		k-=fst[pos];
	}
	return pos+1;
}

int main()
{
		
}
