#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<iterator>
#include<cstdlib>
#include<queue>
#include<map>
#define ll long long
using namespace std;

int n,seq[500010];

template<typename int_t>
void readx(int_t& x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}


void QSort(int l,int r,int* seq_)
{
	int i=l,j=r,mid=seq_[(l+r)>>1];
	while (i<=j)
	{
		while (seq_[i]<mid) i++;
		while (seq_[j]>mid) j--;
		if (i<=j)
		{
			swap(seq_[i],seq_[j]);
			i++; j--;
		}
	}
	if (i<r) QSort(i,r,seq_);
	if (j>l) QSort(l,j,seq_);
}


int main()
{
	readx(n); for (int i=1;i<=n;i++) readx(seq[i]);
	QSort(1,n,seq);
	for (int i=1;i<=n;i++) printf("%d%c",seq[i]," \n"[i==n]);
	
}
