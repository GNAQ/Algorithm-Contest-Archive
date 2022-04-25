#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

#define LCH (u<<1)
#define RCH (u<<1|1)

const int INF_C = 2000000000;

int n, a, b;
int p[200010];

struct SegNode
{
	int l, r, val, pos;
}t1[200010*4], t2[200010*4];

int dis[200010];

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

void Pushup(SegNode *t, int u)
{
	if (t[LCH].val >= t[RCH].val)
	{
		t[u].pos = t[LCH].pos;
		t[u].val = t[LCH].val;
	}
	else
	{
		t[u].pos = t[RCH].pos;
		t[u].val = t[RCH].val;
	}
}

void BuildTree(int u, int lxx, int rxx)
{
	t1[u].l = t2[u].l = lxx;
	t1[u].r = t2[u].r = rxx;
	if (lxx == rxx)
	{
		t1[u].val = lxx + p[lxx];
		t2[u].val = p[lxx] - lxx;
		t1[u].pos = t2[u].pos = lxx;
		return;
	}
	int mid = (lxx + rxx) / 2;
	BuildTree(LCH, lxx, mid);
	BuildTree(RCH, mid + 1, rxx);
	Pushup(t1, u); Pushup(t2, u);
}

void Upd(int u, int p)
{
	if (t1[u].l == t1[u].r)
	{
		t1[u].val = t2[u].val = -INF_C;
		return;
	}
	int mid = (t1[u].l + t1[u].r) / 2;
	if (p <= mid) Upd(LCH, p);
	else Upd(RCH, p);
	Pushup(t1, u); Pushup(t2, u);
}

pair<int, int> Qry(SegNode *t, int u, int lx, int rx)
{
	if (t[u].l >= lx && t[u].r <= rx)
		return {t[u].val, t[u].pos};
	int mid = (t[u].l + t[u].r) / 2;
	if (lx <= mid && rx > mid)
	{
		pair<int, int> p1 = Qry(t, LCH, lx, rx);
		pair<int, int> p2 = Qry(t, RCH, lx, rx);
		if (p1.first >= p2.first) return p1;
		else return p2;
	}
	if (rx <= mid)
		return Qry(t, LCH, lx, rx);
	if (lx > mid)
		return Qry(t, RCH, lx, rx);
}

void BFS()
{
	dis[a] = 0;
	queue<int> que;
	que.push(a);
	Upd(1, a);
	
	int u = 0;
	pair<int, int> tmp;
	while (!que.empty())
	{
		u = que.front(); que.pop();
		
		tmp = Qry(t1, 1, u - p[u], u);
		while (tmp.first != -INF_C && tmp.first >= u)
		{
			Upd(1, tmp.second);
			dis[tmp.second] = dis[u] + 1;
			que.push(tmp.second);
			tmp = Qry(t1, 1, u - p[u], u);
		}
		tmp = Qry(t2, 1, u, u + p[u]);
		while (tmp.first != -INF_C && tmp.first >= -u)
		{
			Upd(1, tmp.second);
			dis[tmp.second] = dis[u] + 1;
			que.push(tmp.second);
			tmp = Qry(t2, 1, u, u + p[u]);
		}
	}
}

void Solve()
{
	readx(n); readx(a); readx(b);
	for (int i=1;i<=n;i++)
		readx(p[i]);
	BuildTree(1, 1, n);
	
	BFS();
	
	printf("%d\n", dis[b]);
}

void Clear()
{
	for (int i=1;i<=n;i++)
		dis[i] = 0;
}

int main()
{
	int T; readx(T);
	while (T--)
	{
		Solve();
		Clear();
	}
}