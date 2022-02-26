#include <cctype>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
const int N = 100007;
std::vector<int> e[N];
int n, ans, root, mn, size[N], vis[N];
int read()
{
	int x = 0, c = getchar();
	while (isspace(c)) c = getchar();
	while (isdigit(c)) (x *= 10) += c & 15, c = getchar();
	return x;
}

void merge(int &a, int &b, int c, int d)
{
	if (a > c)
		a = c, b = d;
}
void get(int u)
{
	size[u] = vis[u] = 1;
	for (int v : e[u])
		if (!vis[v])
			get(v), size[u] += size[v];
	vis[u] = 0;
}
void get(int u, int fa)
{
	size[u] = 1;
	for (int v : e[u])
		if (v ^ fa)
			get(v, u), size[u] += size[v];
}
void find(int u, int s)
{
	int mx = s - size[u];
	vis[u] = 1;
	for (int v : e[u])
		if (!vis[v])
			find(v, s), mx = std::max(mx, size[v]);
	if (vis[u] = 0, mx < mn)
		root = u, mn = mx;
}
int get(int u, int fa, int s)
{
	int mn = n, mx = s - size[u];
	for (int v : e[u])
		if (v ^ fa)
			mn = std::min(mn, get(v, u, s)), mx = std::max(mx, size[v]);
	return std::min(mn, mx);
}
void divide(int u)
{
	mn = n, get(u), find(u, size[u]), vis[u = root] = 1;
	int mn = 1e9, pos = 0;
	for (int v : e[u])
		get(v, u), merge(mn, pos, n - size[v] + get(v, u, size[v]), v);
	if (ans = std::max(ans, mn), !vis[pos])
		divide(pos);
}
int main()
{
	n = read();
	for (int i = 1, u, v; i < n; ++i)
		u = read(), v = read(), e[u].push_back(v), e[v].push_back(u);
	divide(1), printf("%d", ans);
}