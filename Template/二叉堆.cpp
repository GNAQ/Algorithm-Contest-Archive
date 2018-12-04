#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#define ll long long
using namespace std;

int n,m,opt;
int heap[1000010],hsiz;

template<typename int_t>
void readx(int_t& x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

void Add(int val)
{
	heap[++hsiz]=val;
	int pos=hsiz;
	while (pos>1)
	{
		if (heap[pos>>1]<heap[pos]) break;
		swap(heap[pos>>1],heap[pos]);
		pos>>=1;
	}
}
void Del()
{
	heap[1]=heap[hsiz--];
	int pos=1,ch=pos<<1;
	while (ch<=hsiz)
	{
		if (ch<hsiz && heap[ch+1]<heap[ch]) ch++;
		if (heap[ch]>heap[pos]) break;
		swap(heap[ch],heap[pos]);
		pos=ch; ch=pos<<1;
	}
}

int main()
{
	readx(n); int tmp;
	for (int i=1;i<=n;i++)
	{
		readx(opt);
		if (opt==1)
		{
			readx(tmp);
			Add(tmp);
		}
		else if (opt==2) printf("%d\n",heap[1]);
		else Del();
	}
}
