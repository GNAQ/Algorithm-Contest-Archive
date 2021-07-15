#include <cstdio>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <string>
#include <algorithm>
#include <vector>
#include <queue>
typedef long long ll;
using namespace std;

// Dij
struct _Node
{
	int dis, id;
	bool operator < (const _Node &b) const
		{ return this->dis > b.dis; }
};
priority_queue<_Node> que;
int dis[100010];

// Shortest Path Tree
struct ed
{
	int pre, to, w;
} edge[100010];
int at, ptr[100010];
bool vis[100010];

// Original Graph
vector< pair<int, int> > edge2[100010];
int n, m, K;

// 点分
int dep[100010], subsiz, hr, tsiz[100010], msiz[100010];

// 统计
int ans1, ans2;
int bac[100010][2], diss[100010][2];
int maxdep1, maxdep2;

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

void Is(int u, int v, int w)
{
	// cerr << "Is " << u << " " << v << " " << w << endl;
	at++;
	edge[at].pre = ptr[u];
	edge[at].to = v;
	edge[at].w = w;
	ptr[u] = at;
}

void Is2(int u, int v, int w)
{
	edge2[u].push_back(make_pair(v, w));
	edge2[v].push_back(make_pair(u, w));
}

void BuildSPTree(int u)
{
	vis[u] = 1;
	for (int i=0; i<edge2[u].size(); i++)
	{
		int v = edge2[u][i].first, w = edge2[u][i].second;
		if ((!vis[v]) && (dis[v]==dis[u]+w))
		{
			Is(u, v, w);
			Is(v, u, w);
			BuildSPTree(v);
		}
	}
}

void Dijkstra(int S)
{
	_Node cac1, cac2;
	dis[S]=0;
	cac1.id = S; cac1.dis = 0;
	que.push(cac1);
	
	while (!que.empty())
	{
		cac1=que.top(); que.pop();
		if (vis[cac1.id]) continue;
		vis[cac1.id] = 1;
		for (int i=0;i<edge2[cac1.id].size();i++)
		{
			int v = edge2[cac1.id][i].first, w = edge2[cac1.id][i].second;
			if (dis[v]>dis[cac1.id]+w)
			{
				dis[v]=dis[cac1.id]+w;
				cac2.id = v; cac2.dis = dis[v];
				que.push(cac2);
			}
		}
	}
}

// 点分
void GetRt(int u, int fa)
{
	tsiz[u]=1; msiz[u]=0;
	for (int v=ptr[u];v;v=edge[v].pre)
		if (!vis[edge[v].to] && edge[v].to!=fa)
		{
			GetRt(edge[v].to, u);
			tsiz[u]+=tsiz[edge[v].to];
			msiz[u]=max(msiz[u], tsiz[edge[v].to]);
		}
	msiz[u]=max(msiz[u], subsiz - tsiz[u]);
	if (msiz[u]<msiz[hr]) hr=u;
}

void DFS_Dis(int u, int fa, int ndis, int ndep)
{
	if (ndep > K) return;
	maxdep2=max(maxdep2, ndep);
	
	if (diss[ndep][0]==ndis)
	{
		diss[ndep][1]++;
	}
	else if (diss[ndep][0]<ndis)
	{
		diss[ndep][0]=ndis;
		diss[ndep][1]=1;
	}
	
	for (int v=ptr[u];v;v=edge[v].pre)
		if (!vis[edge[v].to] && edge[v].to!=fa)
			DFS_Dis(edge[v].to, u, ndis + edge[v].w, ndep + 1);
}

void Calc(int u)
{
	maxdep1=maxdep2=0; bac[0][1]=1;
	for (int v=ptr[u];v;v=edge[v].pre) if (!vis[edge[v].to])
	{
		maxdep2 = 0;
		DFS_Dis(edge[v].to, 0, edge[v].w, 1);
		
		for (int i=1;i<=maxdep2;i++)
		{
			if (diss[i][0]+bac[K-i][0]==ans1)
				ans2+=diss[i][1]*bac[K-i][1];
			if (diss[i][0]+bac[K-i][0]>ans1)
			{
				ans1=diss[i][0]+bac[K-i][0];
				ans2=diss[i][1]*bac[K-i][1];
			}
		}
		
		for (int i=1;i<=maxdep2;i++)
		{
			if (diss[i][0]==bac[i][0])
				bac[i][1]+=diss[i][1];
			if (diss[i][0]>bac[i][0])
			{
				bac[i][0]=diss[i][0];
				bac[i][1]=diss[i][1];
			}
			diss[i][0]=diss[i][1]=0;
		}
		maxdep1=max(maxdep1, maxdep2);
	}
	for (int i=0;i<=maxdep1;i++) bac[i][0]=bac[i][1]=0;
}

void Div(int u)
{
	vis[u]=1; Calc(u);
	for (int v=ptr[u];v;v=edge[v].pre)
		if (!vis[edge[v].to])
		{
			subsiz = tsiz[edge[v].to];
			msiz[hr = 0] = 1e9;
			GetRt(edge[v].to, 0);
			Div(hr);
		}
}

int main()
{
	memset(dis,0x3f,sizeof(dis));
	int u, v, w;
	
	readx(n); readx(m); readx(K); K-=1;
	for (int i=1;i<=m;i++)
	{
		readx(u); readx(v); readx(w);
		Is2(u, v, w);
	}
	for (int i=1;i<=n;i++)
		sort(edge2[i].begin(), edge2[i].end());
	
	Dijkstra(1);
	memset(vis, 0, sizeof(vis)); // vis 反复利用
	BuildSPTree(1);
	
	// 点分治
	memset(vis, 0, sizeof(vis)); // vis 反复利用 2
	subsiz = n; msiz[hr = 0] = 1e9;
	GetRt(1, 0); 
	Div(hr);
	
	printf("%d %d\n", ans1, ans2);
}