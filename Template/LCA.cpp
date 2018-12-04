#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#define ll long long
using namespace std;

struct ed
{
	int pre,to;
}edge[1000010];
int at,ptr[500010],n,m,rot;

int l[500010][22],dep[5000120];

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
	edge[++at].pre=ptr[tx];
	edge[at].to=fx;
	ptr[tx]=at;
}

void LCA_DFS(int now,int ndep,int fa)
{
	dep[now]=ndep; l[now][0]=fa;
	for (int i=1;i<=20;i++) l[now][i]=l[l[now][i-1]][i-1];
	for (int prex=ptr[now];prex;prex=edge[prex].pre) if (edge[prex].to!=fa)
		LCA_DFS(edge[prex].to,ndep+1,now);
}

int LCA(int u,int v)
{
	if (dep[u]<dep[v]) swap(u,v);
	for (int i=20;i>=0;i--) if (dep[l[u][i]]>=dep[v]) u=l[u][i];
	if (u==v) return v;
	for (int i=20;i>=0;i--) if (l[u][i]!=l[v][i])
	{
		u=l[u][i];
		v=l[v][i];
	}
	return l[v][0];
}

int main()
{
	readx(n); readx(m); readx(rot); int tmp_u,tmp_v,fx,tx;
	for (int i=1;i<n;i++)
	{
		readx(fx); readx(tx);
		Is(fx,tx);
	}
	LCA_DFS(rot,1,0);
	for (int i=1;i<=m;i++)
	{
		readx(tmp_u); readx(tmp_v);
		printf("%d\n",LCA(tmp_u,tmp_v));
	}
}
