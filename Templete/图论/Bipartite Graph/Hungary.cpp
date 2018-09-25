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

struct ed { int pre,to; } edge[1500010]={0};
int n1,n2,edgenum,at=0,pointer[100010]={0},fx,tx;

int matchs[100010]={0},vis[100010]={0},ans;

inline void Insert()
{
	at++;
	edge[at].pre=pointer[fx];
	edge[at].to=tx;
	pointer[fx]=at;
}

inline void readx(int& x)
{
	x=0; int k=1; register char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

inline bool findx(int x,int src)
{
	for (int prex=pointer[x];prex;prex=edge[prex].pre) if (vis[edge[prex].to]!=src)
	{
		vis[edge[prex].to]=src;
		if ((!matchs[edge[prex].to]) || findx(matchs[edge[prex].to],src)) { matchs[edge[prex].to]=x; return true; }
	}
	return false;
}


int main()
{
	readx(n1); readx(n2); readx(edgenum);
	for (int i=1;i<=edgenum;i++)
	{
		readx(fx); readx(tx); tx+=n1;
		if (fx<=n1 && tx>n1 && tx<=n1+n2) Insert();
	}
	
	for (int i=1;i<=n1;i++) ans+=findx(i,i);
	printf("%d\n",ans);
	return 0;
}
