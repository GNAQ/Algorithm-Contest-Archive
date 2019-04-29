#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

const int N = 1000010;

int n, q, a[N];

inline char nc()
{
	static char buf[100000], *p1 = buf, *p2 = buf;
	return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++;
}

inline void read(int &x)
{
	char c = nc();
	x = 0;
	for (; c > '9' || c < '0'; c = nc())
		;
	for (; c >= '0' && c <= '9'; x = x * 10 + c - '0', c = nc())
		;
}

struct Qry
{
	int l, r, g;
	friend bool operator<(Qry a, Qry b)
	{
		return a.l < b.l || (a.l == b.l && a.r > b.r);
	}
} Q[N];

int cnt, G[N], S[N], vis[N], b[N], tot, t;
ll ans[N], sum[N], ti[N], mx, tms;

struct edge
{
	int t, nx;
} E[N];

inline void addedge(int x, int y)
{
	E[++cnt].t = y;
	E[cnt].nx = G[x];
	G[x] = cnt;
}

void PutAns(ll x)
{
	if (x >= 10)
		PutAns(x / 10);
	putchar(x % 10 + '0');
}

int siz[N], son[N];

void pfs(int x)
{
	siz[x] = 1;
	for (int i = G[x]; i; i = E[i].nx)
	{
		pfs(E[i].t);
		if (son[x] == -1 || siz[E[i].t] > siz[son[x]])
			son[x] = E[i].t;
		siz[x] += siz[E[i].t];
	}
}

void add(int x)
{
	if (Q[x].l == Q[x].r)
	{
		int cur = a[Q[x].l];
		sum[cur]++;
		mx = max(mx, sum[cur] * b[cur]);
		return;
	}
	for (int i = G[x]; i; i = E[i].nx)
		add(E[i].t);
}

void del(int x)
{
	if (Q[x].l == Q[x].r)
		sum[a[Q[x].l]]--;
	for (int i = G[x]; i; i = E[i].nx)
		del(E[i].t);
}

void dfs(int x)
{
	for (int i = G[x]; i; i = E[i].nx)
		if (E[i].t != son[x])
			dfs(E[i].t), del(E[i].t), mx = 0;
	if (~son[x])
		dfs(son[x]);
	if (Q[x].l == Q[x].r)
	{
		int cur = a[Q[x].l];
		sum[cur]++;
		mx = max(mx, sum[cur] * b[cur]);
	}
	for (int i = G[x]; i; i = E[i].nx)
		if (E[i].t != son[x])
			add(E[i].t);
	if (~Q[x].g)
		ans[Q[x].g] = mx;
}

int main()
{
	read(n);
	read(q);
	tot = q;
	for (int i = 1; i <= n; i++)
		read(a[i]), b[i] = a[i];
	sort(b + 1, b + n + 1);
	t = unique(b + 1, b + 1 + n) - b - 1;
	for (int i = 1; i <= n; i++)
		a[i] = lower_bound(b + 1, b + 1 + t, a[i]) - b;
	t = 0;
	for (int i = 1; i <= q; i++)
	{
		read(Q[i].l), read(Q[i].r), Q[i].g = i;
		if (Q[i].l == Q[i].r)
			vis[Q[i].l] = 1;
	}
	for (int i = 1; i <= n; i++)
		if (!vis[i])
			Q[++tot].l = i, Q[tot].r = i, Q[tot].g = -1;
	sort(Q + 1, Q + 1 + tot);
	Q[0].r = n + 1;
	son[0] = -1;
	for (int i = 1; i <= tot; i++)
	{
		while (Q[S[t]].r < Q[i].l)
			t--;
		addedge(S[t], i);
		S[++t] = i;
		son[i] = -1;
	}
	pfs(0);
	dfs(0);
	for (int i = 1; i <= q; i++)
		PutAns(ans[i]), putchar('\n');
	return 0;
}