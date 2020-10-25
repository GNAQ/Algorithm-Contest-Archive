#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<vector>
typedef long long ll;
using namespace std;

vector<int> ed[1000010];
int fa[1000010],n,m;
int dep[1000010], max_dep[1000010];

int ans, pre[1000010];

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}


void DFSdep(int u)
{
	max_dep[u]=dep[u];
	for (auto v:ed[u])
	{
		dep[v]=dep[u]+1;
		DFSdep(v);
		max_dep[u]=max(max_dep[u], max_dep[v]);
	}
}

bool cmp(int a,int b)
{
	return max_dep[a] < max_dep[b];
}

void DFS(int u)
{
	pre[u]=u;
	for (auto v:ed[u])
	{
		DFS(v);
		ans+=min(dep[u]+1, dep[pre[u]]-dep[u]+1);
		pre[u]=pre[v];
	}
}

void Clear()
{
	for (int i=1;i<=n;i++) ed[i].clear();
	ans=0;
	for (int i=1;i<=n;i++) 
		dep[i]=max_dep[i]=0;
}

int main()
{
	int T; readx(T);
	for (int ttt=1;ttt<=T;ttt++)
	{
		readx(n); dep[1]=0;
		for (int i=2;i<=n;i++)
		{
			readx(fa[i]);
			ed[fa[i]].push_back(i);
		}
		
		DFSdep(1);
		
		for (int i=1;i<=n;i++) 
			sort(ed[i].begin(), ed[i].end(), cmp);
		
		DFS(1);
		
		printf("Case #%d: %d\n", ttt, ans);
		Clear();
	}
}