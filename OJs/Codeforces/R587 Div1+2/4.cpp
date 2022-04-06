#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

bool vis[1000010];
int dsu[1000010],siz[1000010];
int n, k;

int findfa(int e)
{
	if (dsu[e] != e) dsu[e] = findfa(dsu[e]);
	return dsu[e];
}

void merge(int a, int b)
{
	if (findfa(a) != findfa(b))
	{
		int fb = findfa(b), fa = findfa(a);
		dsu[fb] = fa;
		siz[fa] += siz[fb];
	}
}

int main()
{
	int u, v;
	scanf("%d%d", &n, &k);
	for (int i=1;i<=n;i++)
	{
		dsu[i] = i;
		siz[i] = 1;
	}
	for (int i=1;i<=k;i++)
	{
		scanf("%d%d", &u, &v);
		merge(u, v);
	}
	ll ans = 0;
	for (int i=1;i<=n;i++) if (!vis[findfa(i)])
	{
		vis[findfa(i)] = 1;
		ans += siz[findfa(i)] - 1;
	}
	printf("%lld\n", k - ans);
	return 0;
}