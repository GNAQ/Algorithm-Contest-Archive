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

int n,opt,lx,rx;
int seq[100010]={0},f[100010][20]={0},logtwo[100010]={0};

inline void readx(int& x)
{
	x=0; int k=1; register char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

inline void init1()
{
	logtwo[1]=0; logtwo[2]=1; for (int i=3;i<=n;i++) logtwo[i]=logtwo[(i>>1)]+1;
	for (int i=1;i<=n;i++) f[i][0]=seq[i];
	for (int w=1;w<=20;w++)
		for (int i=n;i;i--) if (i+(1<<w)-1<=n)
			f[i][w]=max(f[i][w-1],f[i+(1<<(w-1))][w-1]);
}

int main()
{
	readx(n); readx(opt);
	for (int i=1;i<=n;i++) readx(seq[i]);
	init1();
	for (int i=1;i<=opt;i++)
	{
		readx(lx); readx(rx);
		int poww=logtwo[rx-lx+1];
		printf("%d\n",max(f[lx][poww],f[rx-(1<<poww)+1][poww]));
	}
	return 0;
}
