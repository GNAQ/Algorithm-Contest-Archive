#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<vector>
typedef long long ll;
using namespace std;

struct ed
{
	int pre, to, w, id;
}edge[100010];
int at=1, ptr[100010];

int n, m, ss, tt, val[30010];
int ban;

int ans1c, ans2c;
int e1, e2a, e2b;

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

void Is(int u, int v, int w, int id)
{
	at++;
	edge[at].pre=ptr[u];
	edge[at].to=v;
	edge[at].w=w; edge[at].id=id;
	ptr[u]=at;
	at++;
	edge[at].pre=ptr[v];
	edge[at].to=u;
	edge[at].w=w; edge[at].id=id;
	ptr[v]=at;
}

int dfn[1010], low[1010], tcnt=0;
bool bri[30010];
void Tarjan(int u, int fr)
{
	dfn[u]=low[u]=++tcnt;
	for (int v=ptr[u];v;v=edge[v].pre) if (edge[v].id!=ban)
	{
		if (!dfn[edge[v].to])
		{
			Tarjan(edge[v].to, edge[v].id);
			low[u]=min(low[u], low[edge[v].to]);
			if (low[edge[v].to] > dfn[u])  // 是割边 
			{
				bri[edge[v].id] = 1;
			}
		}
		else if (edge[v].id != fr)
		{
			low[u]=min(low[u], dfn[edge[v].to]);
		}
	}
}

int nnv[1010]; int vis[1010];
int toban[30010];
bool DFS(int u)
{
	if (u==tt) return true;
	vis[u]=1;
	for (int v=ptr[u];v;v=edge[v].pre) if (edge[v].id!=ban)
	{
		if (!vis[edge[v].to] && DFS(edge[v].to))
		{
			nnv[u]=v;
			return true;
		}
	}
	return false;
}

int main()
{
	ans1c=ans2c=2*1e9+100;
	readx(n); readx(m); readx(ss); readx(tt);
	int u, v, w; ban=0;
	
	for (int i=1;i<=m;i++)
	{
		readx(u); readx(v); readx(w);
		Is(u, v, w, i);
		val[i]=w;
	}
	
	if (!DFS(ss))
	{
		printf("0\n0\n");
		return 0;
	}
	
	for (int i=1;i<=n;i++) if (nnv[i]) 
		toban[edge[nnv[i]].id] = 1;
	
	for (ban=1; ban<=m; ban++) if (toban[ban])
	{
		for (int i=1;i<=n;i++) vis[i]=nnv[i]=0;
		bool ok = DFS(ss);
		
		if (!ok)
		{
			if (ans1c>val[ban])
			{
				ans1c=val[ban];
				e1=ban;
			}
		}
		else
		{
			for (int i=1;i<=m;i++) bri[i]=0;
			for (int i=1;i<=n;i++) dfn[i]=low[i]=0;
			tcnt=0;
			Tarjan(ss, -1);
			
			int tmp = ss;
			while (tmp!=tt)
			{
				if (bri[ edge[nnv[tmp]].id ])
				{
					if (ans2c > edge[ nnv[tmp] ].w+val[ban])
					{
						ans2c=edge[ nnv[tmp] ].w+val[ban];
						e2a=edge[ nnv[tmp] ].id; e2b=ban;
					}
				}
				tmp = edge[ nnv[tmp] ].to;
			}
			
		}
	}
	
	if (ans1c==ans2c && ans2c==2*1e9+100)
	{
		printf("-1\n");
		return 0;
	}
	
	if (ans1c<=ans2c)
	{
		printf("%d\n1\n%d\n", ans1c, e1);
	}
	else
	{
		printf("%d\n2\n%d %d\n", ans2c, min(e2a, e2b), max(e2a, e2b));
	}
	
	return 0;
}