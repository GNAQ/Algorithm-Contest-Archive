#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

struct Ed
{
	int pre, to, w;
}edge[200010];
int at, ptr[100010];
int n, m;

ll dp[4010][4010];

bool dfsvis[4010][4010];
int ans[4010];

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
}

double GetCrossX(int k1, ll b1, int k2, ll b2)
{
	return (double)(b1 - b2) / (double)(k2 - k1);
}

void DFS(int u, int lvl)
{
	dfsvis[lvl][u] = 1;
	ans[u] = 1;
	if (u == 1) return;
	
	for (int v = ptr[u]; v; v=edge[v].pre) 
		if ((!dfsvis[lvl-1][edge[v].to]) && 
		  (dp[lvl-1][edge[v].to] + edge[v].w == dp[lvl][u]))
			DFS(edge[v].to, lvl-1);
}

int main()
{
	int u, v, w;
	readx(n); readx(m);
	for (int i=1;i<=m;i++)
	{
		readx(u); readx(v); readx(w);
		Is(u, v, w);
		Is(v, u, w);
	}
	
	memset(dp, 0x3f, sizeof(dp));
	dp[0][1]=0;
	for (int k=1;k<=n;k++)
		for (int i=1;i<=n;i++)
			for (int v = ptr[i]; v; v=edge[v].pre)
				dp[k][i] = min(dp[k][i], dp[k-1][edge[v].to]+edge[v].w);
	
	vector<int> stk(n + 5, 0);
	int hd = -1;
	for (int i=n;i>=1;i--) if (dp[i][n] < dp[0][n])
	{
		while (hd>=1)
		{
			int v0 = stk[hd-1], v1 = stk[hd];
			double p0 = GetCrossX(v0, dp[v0][n], i, dp[i][n]);
			double p1 = GetCrossX(v1, dp[v1][n], i, dp[i][n]);
			if (p0 > p1) hd--;
			else break;
		}
		stk[++hd] = i;
	}
	
	ans[1] = 1;
	int i=0;
	while (i<hd && GetCrossX(stk[i], dp[stk[i]][n], 
	  stk[i+1], dp[stk[i+1]][n]) < 0)
		i++;
	for (;i<=hd;i++)
		DFS(n, stk[i]);
	
	vector<int> vans;
	for (int i=1;i<=n;i++)
		if (!ans[i]) vans.push_back(i);
	printf("%d\n", (int)vans.size());
	for (int i=0;i<(int)vans.size();i++)
		printf("%d%c", vans[i], " \n"[i==(int)vans.size()-1]);
}