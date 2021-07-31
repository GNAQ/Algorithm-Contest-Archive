#include<bits/stdc++.h>
typedef long long ll;
using namespace std;

struct ed
{
	int fr, to, w;
}edge[1000010];
int at=0;
int n, m, k;

int dsu[100010];

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
	at++;
	edge[at].fr = u;
	edge[at].to = v;
	edge[at].w = w;
}

int Find(int e)
{
	if (dsu[e]!=e) dsu[e]=Find(dsu[e]);
	return dsu[e];
}

void Merge(int e1, int e2)
{
	dsu[Find(e2)]=Find(e1);
}

int Kruskal()
{
	if (k==n) return 0;
	
	for (int i=1;i<=n;i++) dsu[i]=i;
	
	int blk = n, ans = 0;
	for (int i=1;i<=at;i++)
	{
		if (blk == k) 
		{
			while (i<=at && Find(edge[i].fr)==Find(edge[i].to)) i++;
			if (i<=at && edge[i].w == ans)
				return -1;
			else 
				return ans;
		}
		if (Find(edge[i].fr)!=Find(edge[i].to))
		{
			Merge(edge[i].fr, edge[i].to);
			blk--;
			ans=max(ans, edge[i].w);
		}
	}
	return ans;
}

bool cmp1(const ed &a, const ed &b)
{
	return a.w < b.w;
}

void Solve()
{
	readx(n); readx(m); readx(k);
	int u, v, w;
	for (int i=1;i<=m;i++)
	{
		readx(u); readx(v); readx(w);
		Is(u, v, w);
	}
	sort(edge+1, edge+at+1, cmp1);
	
	int ans = Kruskal();
	printf("%d\n", ans);
	return;
}

void Clear()
{
	at=0;
}

int main()
{
	int T; readx(T);
	while (T--)
	{
		Solve();
		Clear();
	}
	return 0;
}