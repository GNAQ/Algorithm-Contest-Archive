#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<iterator>
#include<cstdlib>
#define ll long long
using namespace std;

int n,m,opt,ds[100010];

template<typename int_t>
void readx(int_t& x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

int Find(int e_1)
{
	if (e_1!=ds[e_1]) ds[e_1]=Find(ds[e_1]);
	return ds[e_1];
}
void Merge(int e_1,int e_2)
{
	ds[Find(e_2)]=Find(e_1);
}

int main()
{
	readx(n); readx(m); int e_1,e_2;
	for (int i=1;i<=n;i++) ds[i]=i;
	for (int i=1;i<=m;i++)
	{
		readx(opt); readx(e_1); readx(e_2);
		if (opt==1)
			Merge(e_1,e_2);
		else 
		{
			if (Find(e_1)==Find(e_2)) printf("Y\n");
			else printf("N\n");
		}
	}
	return 0;
}
