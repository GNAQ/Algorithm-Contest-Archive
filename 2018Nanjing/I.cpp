#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

struct ed
{
	int pre, to, w;
} edge[800100];
int at = 1, ptr[10110];


int n, m, k;
vector<int> Mi[1010];
int sMi[1010];

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
	edge[++at].pre = ptr[u];
	edge[at].to = v;
	edge[at].w = w;
	ptr[u] = at;
	edge[++at].pre = ptr[v];
	edge[at].to = u;
	edge[at].w = 0;
	ptr[v] = at;
}

int SS, TT;
int lvl[10110], cur[10110];
queue<int> que;
bool BFS()
{
	for (int i=0;i<=n+m+12;i++)
		lvl[i]=0;
	lvl[SS]=1;
	que.push(SS);
	while (!que.empty())
	{
		int cac = que.front(); que.pop();
		for (int v=ptr[cac];v;v=edge[v].pre)
			if (!lvl[edge[v].to] && edge[v].w)
			{
				lvl[edge[v].to] = lvl[cac] + 1;
				que.push(edge[v].to);
			}
	}
	if (!lvl[TT]) return false;
	for (int i=0;i<=n+m+12;i++)
		cur[i] = ptr[i];
	return true;
}


int Dinic(int u, int minf)
{
	if (!minf || u == TT) return minf;
	int needf = 0, sumf = 0;
	for (int v=ptr[u];v;v=edge[v].pre)
		if (lvl[edge[v].to] == lvl[u]+1)
		{
			int e = edge[v].to;
			cur[e] = v;
			if (needf=Dinic(e, min(minf, edge[v].w)))
			{
				sumf += needf; minf -= needf;
				edge[v].w -= needf; edge[v^1].w += needf;
				if (!minf) break;
			}
		}
	return sumf;
}


int main()
{
	int tmp;
	readx(n); readx(m); readx(k);
	for (int i=1;i<=n;i++)
	{
		readx(sMi[i]); 
		for (int j=1;j<=sMi[i];j++)
		{
			readx(tmp);
			Mi[i].push_back(tmp);
			Is(i, tmp + n, 1);
		}
	}
	
	SS = n + m + 1; TT = n + m + 2;
	int kid = n + m + 3;
	
	Is(SS, kid, k);
	for (int i=1;i<=n;i++)
	{
		Is(SS, i, 1);
		Is(kid, i, 1);
	}
	for (int i=n+1;i<=n+m;i++)
	{
		Is(i, TT, 1);
	}
	
	int ans = 0;
	while (BFS()) ans += Dinic(SS, 2*1e9);
	
	cout << ans << endl;
	
}