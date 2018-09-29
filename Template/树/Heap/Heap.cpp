#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<iterator>
#include<cstdlib>
#include<vector>
#include<queue>
using namespace std;

int heap[1000010]={0},hsiz=0;
int n,typ,val;

inline void readx(int& x)
{
	x=0; int k=1; register char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

inline void del()
{
	heap[1]=heap[hsiz--];
	int now=1,p;
	while ((now<<1)<=hsiz)
	{
		p=now<<1;
		if (p<hsiz && heap[p+1]<heap[p]) p++;
		if (heap[p]>heap[now]) break;
		swap(heap[p],heap[now]);
		now=p;
	}
}
inline void ins()
{
	heap[++hsiz]=val;
	int now=hsiz,p;
	while (now>1)
	{
		p=now>>1;
		if (heap[p]<heap[now]) break;
		swap(heap[p],heap[now]);
		now=p;
	}
}

int main()
{
	readx(n);
	for (int i=1;i<=n;i++)
	{
		readx(typ);
		if (typ==1)
		{
			readx(val); ins();
		}
		else if (typ==2) printf("%d\n",heap[1]);
		else del();
	}
}
