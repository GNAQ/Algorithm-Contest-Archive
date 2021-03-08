#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<vector>
#include<queue>
typedef long long ll;
using namespace std;

struct ed
{
	int pre,to,cap;
}edge[400010];
int at=1,ptr[1010];

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' ||  ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
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

namespace Dinic
{
	int lvl[100010], cur[100010];
	int S, T;
	queue<int> que;
	
	int BFS(void)
	{
		memset(lvl, 0, sizeof(int)*(T+3));
		lvl[S]=1; que.push(S);
		int cac;
		while (!que.empty())
		{
			cac=que.front(); que.pop();
			for (int v=ptr[cac];v;v=edge[v].pre)
				if (!lvl[edge[v].to] && edge[v].cap)
				{
					lvl[edge[v].to]=lvl[cac]+1;
					que.push(edge[v].to);
				}
		}
		if (!lvl[T]) return false;
		memcpy(cur, ptr, sizeof(int)*(T+3));
		return true;
	}
	
	int DFS(int u, int minf)
	{
		if (!minf || u==T) return minf;
		int needf, sumf=0;
		for (int v=cur[u];v;v=edge[v].pre)
			if (lvl[u]+1==lvl[edge[v].to])
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

int n,m, L, R;
int Ai[1010][1010], CA[1010], RA[1010];

void ClearEd(int siz)
{
	at=1; memset(ptr, 0, sizeof(int)*siz);
}

int IsLR(int u, int v, int lb, int ub)
{
	Is(u, v, ub-lb);
	Is(Dinic::S, v, lb);
	Is(u, Dinic::T, lb);
	return lb;
}

int Try(int mid) // s -> rows -> columns -> t
{
	int lb, ub, req=0, flow=0;
	int s=n+m+1, t=n+m+2;
	Dinic::S = t+1;
	Dinic::T = t+2;
	
	Is(t, s, 1e8);
	for (int i=1; i<=n; i++) // rows
	{
		lb = max(0, RA[i]-mid);
		ub = RA[i]+mid;
		req+=IsLR(s, i, lb, ub);
	}
	for (int i=1; i<=m; i++) // columns
	{
		lb = max(0, CA[i]-mid);
		ub = CA[i]+mid;
		req+=IsLR(i+n, t, lb, ub);
	}
	for (int i=1; i<=n; i++)
		for (int j=1; j<=m; j++)
			req+=IsLR(i, j+n, L, R);
	
	while (Dinic::BFS()) flow+=Dinic::DFS(Dinic::S, 2*1e9);
	
	ClearEd(n+m+7);
	return req==flow;
}

int main()
{
	int l=0, r=0, mid, ans;
	
	readx(n); readx(m);
	for (int i=1; i<=n; i++)
		for (int j=1; j<=m; j++)
		{
			readx(Ai[i][j]);
			RA[i]+=Ai[i][j];
			CA[j]+=Ai[i][j];
		}
	readx(L); readx(R);
	for (int i=1;i<=n;i++) r = max(r, RA[i]);
	for (int i=1;i<=m;i++) r = max(r, CA[i]);
	
	while (l<=r)
	{
		mid = (l+r)/2;
		if (Try(mid))
		{
			ans = mid;
			r = mid-1;
		}
		else 
			l = mid+1;
	}
	printf("%d\n", ans);
	
	return 0;
}