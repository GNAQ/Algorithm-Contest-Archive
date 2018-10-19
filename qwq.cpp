#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<iterator>
#include<algorithm>
#include<cstdlib>
#include<queue>
#include<vector>
#include<map>
#include<set>
#define ll long long
using namespace std;

int n,m;
vector<int> edge[100010];
int W[100010];
struct Paths
{
	int u,v,lca;
}pth[100010];

//LCA
int dep[100010],l[100010][22];

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
	edge[fx].push_back(tx);
	edge[tx].push_back(fx);
}
void LCADFS(int now,int ndep,int fa)
{
	dep[now]=ndep; l[now][0]=fa;
	for (int i=1;i<=20;i++) l[now][i]=l[l[now][i-1]][i-1];
	
	for (auto v:edge[now]) if (v!=fa)
		LCADFS(v,ndep+1,now);
}
int LCA(int u,int v)
{
	if (dep[u]<dep[v]) swap(u,v);
	for (int i=20;i>=0;i--) if (dep[l[u][i]]>=dep[v]) u=l[u][i];
	if (u==v) return v;
	for (int i=20;i>=0;i--) if (l[u][i]!=l[v][i])
		{ u=l[u][i]; v=l[v][i]; }
	return l[u][0];
}


int main()
{
	readx(n); readx(m); int fx,tx;
	for (int i=1;i<n;i++) 
	{
		readx(fx); readx(tx);
		Is(fx,tx);
	}
	LCADFS(1,1,0);
	for (int i=1;i<=n;i++) readx(W[i]);
	for (int i=1;i<=m;i++)
	{
		readx(pth[i].u); readx(pth[i].v);
		pth[i].lca=LCA(pth[i].u,pth[i].v);
	}
	
	
	
	
	
}