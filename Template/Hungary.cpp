#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#define ll long long
using namespace std;

int n,m,e;
struct ed
{
	int pre,to;
}edge[1000010];
int at,ptr[10010];

template<typename int_t>
void readx(int_t& x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

void Is(int fx,int tx)
{
	edge[++at].pre=ptr[fx];
	edge[at].to=tx;
	ptr[fx]=at;
}

int mat[100010],vis[100010];
bool Hungary(int now,int src)
{
	for (int v=ptr[now];v;v=edge[v].pre) if (vis[edge[v].to]!=src)
	{
		vis[edge[v].to]=src;
		if (!mat[edge[v].to] || Hungary(mat[edge[v].to],src)) 
		{
			mat[edge[v].to]=now;
			return true;
		}
	}
	return false;
}

int main()
{
	readx(n); readx(m); readx(e); int fx,tx,ans=0;
	for (int i=1;i<=e;i++)
	{
		readx(fx); readx(tx); tx+=n;
		if (fx<=n && tx>n && tx<=n+m) Is(fx,tx);
	}
	for (int i=1;i<=n;i++) ans+=Hungary(i,i);
	printf("%d\n",ans);
}
