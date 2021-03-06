#include<cstdio>
#include<iostream>
#include<cmath>
#include<cstring>
#include<string>
#include<cmath>
#include<cstdlib>
#include<vector>
#include<algorithm>
#include<queue>
typedef long long ll;
using namespace std;

struct ed
{
	int pre,to,cap;
}edge[20010];
int at=1,ptr[1010];
int n,m;
int ai[1010], bi[10010];
vector<int> keys[1010];
int last[1010];

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

void Is(int u, int v, int c)
{
	at++;
	edge[at].pre=ptr[u];
	edge[at].to=v;
	edge[at].cap=c;
	ptr[u]=at;
	at++;
	edge[at].pre=ptr[v];
	edge[at].to=u;
	edge[at].cap=0;
	ptr[v]=at;
}

// 朴素 Dinic，注意 T 最好是最大的点
namespace Dinic
{
	int lvl[100010],cur[100010];
	int S,T;
	
	queue<int> que;
	int BFS(void)
	{
		memset(lvl, 0, sizeof(int) * (T+5)); // 注意
		lvl[S] = 1; que.push(S);
		int cac;
		while (!que.empty())
		{
			cac = que.front(); que.pop();
			for (int v=ptr[cac]; v; v=edge[v].pre)
				if (!lvl[edge[v].to] && edge[v].cap)
				{
					lvl[edge[v].to] = lvl[cac] + 1;
					que.push(edge[v].to);
				}
		}
		if (!lvl[T]) return false;
		memcpy(cur, ptr, sizeof(int) * (T+5));
		return true;
	}
	
	int DFS(int u, int minf)
	{
		if (!minf || u==T) return minf;
		int needf=0, sumf=0;
		for (int v=cur[u]; v; v=edge[v].pre)
			if (lvl[edge[v].to]==lvl[u]+1)
			{
				cur[u]=v;
				if (needf=DFS(edge[v].to, min(minf, edge[v].cap)))
				{
					sumf+=needf; minf-=needf;
					edge[v].cap-=needf; edge[v^1].cap+=needf;
					if (!minf) break;
				}
			}
		return sumf;
	}
}

int main()
{
	readx(m); readx(n);
	Dinic::S = m + n + 1; Dinic::T = m + n + 2;
	for (int i=1; i<=m; i++) 
	{
		readx(ai[i]);
		Is(Dinic::S, i, ai[i]);
	}
	for (int i=1; i<=n; i++)
	{
		int keynum, cac; readx(keynum);
		for (int j=1; j<=keynum; j++)
		{
			readx(cac); keys[i].push_back(cac);
			Is(cac, i+m, 100000000);
			if (last[cac])
				Is(last[cac]+m, i+m, 100000000);
			last[cac]=i;
			
		}
		readx(bi[i]);
		Is(i+m, Dinic::T, bi[i]);
		
	}
	
	int ans = 0;
	while (Dinic::BFS()) ans+=Dinic::DFS(Dinic::S, 2*1e9);
	printf("%d\n", ans);
}