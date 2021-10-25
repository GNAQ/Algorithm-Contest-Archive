#include <bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ull;
using namespace std;

const ull mod = 1e9+7;

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

int n, m;

struct Edge
{
	int u, v;
	unsigned long long w;
	
	bool operator < (const Edge &b) const
	{
		return this->w < b.w;
	}
}ed[100010];

namespace DG
{
	unsigned long long k1, k2;
	unsigned long long xorShift128Plus()
	{
		unsigned long long k3 = k1, k4 = k2;
		k1 = k4;
		k3 ^= k3 << 23;
		k2 = k3 ^ k4 ^ (k3 >> 17) ^ (k4 >> 26);
		return k2 + k4;
	}
	void gen()
	{
		scanf("%d%d%llu%llu", &n, &m, &k1, &k2);
		for (int i = 1; i <= m; ++i)
		{
			ed[i].u = xorShift128Plus() % n + 1;
			ed[i].v = xorShift128Plus() % n + 1;
			ed[i].w = xorShift128Plus();
		}
	}
}

int fu[100010];
int Find(int e)
{
	if (fu[e]!=e) fu[e]=Find(fu[e]);
	return fu[e];
}

ull Kruskal()
{
	sort(ed+1, ed+m+1);
	for (int i=1;i<=n;i++) fu[i]=i;
	
	ull ans = 0;
	int cnt = 0;
	for (int x=1;x<=m;x++)
	{
		int a = Find(ed[x].u), b = Find(ed[x].v);
		if (a == b) continue;
		fu[b] = a;
		cnt++;
		ans = ( ans + (ed[x].w % mod) ) % mod;
	}
	return (cnt == n-1) ? ans : 0;
}

void Solve()
{
	DG::gen();
	printf("%llu\n", Kruskal());
}

void Clear()
{
}

int main()
{
	int T; 
	readx(T); 
	while (T--)
	{
		Solve();
		Clear();
	}
}