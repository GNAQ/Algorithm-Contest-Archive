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
vector<int> edge[300010];
int W[300010];
struct Paths { int u,v,lca,dist; }pth[300010];
int dep[300010],l[300010][22];

//paths
int st[300010];
vector<int> ps[300010],invs[300010],pn[300010];

//bucket
int buc[600010];
int ans[300010];

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

void DFS1(int now,int fa)
{
	int tmp=buc[dep[now]+W[now]];
	for (auto v:edge[now]) if (v!=fa) DFS1(v,now);
	buc[dep[now]]+=st[now];
	ans[now]+=buc[dep[now]+W[now]]-tmp;
	for (auto v:ps[now]) buc[dep[v]]--;
}

void DFS2(int now,int fa)
{
	int tmp=buc[W[now]-dep[now]+n];
	for (auto v:edge[now]) if (v!=fa) DFS2(v,now);
	for (auto v:invs[now]) buc[v+n]++;
	ans[now]+=buc[W[now]-dep[now]+n]-tmp;
	for (auto v:pn[now]) buc[v+n]--;
}

int main()
{
	// freopen("dat.in","r",stdin);
	// freopen("dat.out","w",stdout);
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
		pth[i].dist=dep[pth[i].u]+dep[pth[i].v]-2*dep[pth[i].lca];
		
		st[pth[i].u]++;
		ps[pth[i].lca].push_back(pth[i].u);
		invs[pth[i].v].push_back(pth[i].dist-dep[pth[i].v]);
		pn[pth[i].lca].push_back(pth[i].dist-dep[pth[i].v]);
	}
	
	DFS1(1,0);
	DFS2(1,0);
	for (int i=1;i<=m;i++) 
		if (dep[pth[i].u]==dep[pth[i].lca]+W[pth[i].lca]) ans[pth[i].lca]--;
	for (int i=1;i<=n;i++) printf("%d%c",ans[i]," \n"[i==n]);
	return 0;
}