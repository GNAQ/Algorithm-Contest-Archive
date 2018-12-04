#include<cstdio>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#define ll long long
using namespace std;

int n,m,seq[100010],lg2[100010];
int st[100010][22];

template<typename int_t>
void readx(int_t& x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

void Init()
{
	lg2[1]=0; lg2[2]=1;
	for (int i=3;i<=n;i++) lg2[i]=lg2[i>>1]+1;
	for (int i=1;i<=n;i++) st[i][0]=seq[i];
	for (int w=1;w<=20;w++)
		for (int i=1;i<=n;i++) if (i+(1<<w)-1<=n)
			st[i][w]=max(st[i][w-1],st[i+(1<<(w-1))][w-1]);
}

int main()
{
	readx(n); readx(m); int lx,rx;
	for (int i=1;i<=n;i++) readx(seq[i]);
	Init();
	for (int i=1;i<=m;i++)
	{
		readx(lx); readx(rx);
		int tmp=lg2[rx-lx+1];
		printf("%d\n",max(st[lx][tmp],st[rx-(1<<tmp)+1][tmp]));
	}
}
