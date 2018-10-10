#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<iterator>
#include<vector>
#include<queue>
#include<map>
#include<set>
#define ll long long
using namespace std;

vector<int> edge[10010];
int n,m;
vector<int> deps[10010];
int dep[10010],upat;
bool vis[10010];

template<typename int_t>
void readx(int_t& x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

void Is(int fx,int tx) { edge[fx].push_back(tx); edge[tx].push_back(fx); }

void _init(int now,int _dep,int fa)
{
	dep[now]=_dep; deps[_dep].push_back(now); upat=max(upat,_dep);
	for (auto v:edge[now]) if (v!=fa) _init(v,_dep+1,now);
}

int cntans,ans=2*1e9;

void Count(int now,int fa)
{
	cntans+=vis[now];
	for (auto v:edge[now]) if (!vis[v] && v!=fa) Count(v,now);
}

void DFS(int _dep)
{
	cntans=0; Count(1,0); ans=max(ans,cntans);
	for (auto u:deps[_dep])
		for (auto v:edge[u]) if (dep[v]<dep[u]) vis[u]|=vis[u];
	for (auto u:deps[_dep]) if (!vis[u])
	{
		vis[u]=1;
		DFS(_dep+1);
		vis[u]=0;
	}
}

int main()
{
	readx(n); readx(m); int fx,tx;
	for (int i=1;i<=m;i++) { readx(fx); readx(tx); Is(fx,tx); }
	_init(1,1,0);
	DFS(1);
	printf("%d\n",ans);
	return 0;
}
