#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#define ll long long
using namespace std;

int n,seq[500010],m;
int fwt[500010];

template<typename int_t>
void readx(int_t& x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

void Upd(int pos,int val)
{
	while (pos<=n)
	{
		fwt[pos]+=val;
		pos+=(pos&(-pos));
	}
}
int Qry(int pos)
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
	readx(n); readx(m); int lx,rx,opt,val;
	for (int i=1;i<=n;i++) readx(seq[i]);
	for (int i=1;i<=n;i++) Upd(i,seq[i]-seq[i-1]);
	
	for (int i=1;i<=m;i++)
	{
		readx(opt); 
		if (opt==1)
		{
			readx(lx); readx(rx); readx(val);
			Upd(lx,val); Upd(rx+1,-val);
		}
		else
		{
			readx(lx);
			printf("%d\n",Qry(lx));
		}
	}
}
