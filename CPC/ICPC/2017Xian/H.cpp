#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<vector>
typedef long long ll;
using namespace std;

struct Seg_T
{
	int l, r;
	int val, tag;
}t[100010<<2];
int lx, rx; 
int vx;

int n, k;
int ai[100010];

#define LCH (u<<1)
#define RCH (u<<1|1)

void Pushdown(int u)
{
	if (!t[u].tag) return;
	int r = t[u].tag; t[u].tag = 0;
	t[LCH].val += r;
	t[RCH].val += r;
	t[LCH].tag += r;
	t[RCH].tag += r;
}

void BuildTree(int u, int lxx, int rxx)
{
	t[u].l = lxx; t[u].r = rxx;
	t[u].tag = t[u].val = 0;
	if (lxx == rxx)
	{
		//t[u].tag = t[u].val = 0;
		t[u].val = ai[lxx];
		return;
	}
	int mid = (lxx + rxx) / 2;
	BuildTree(LCH, lxx, mid);
	BuildTree(RCH, mid+1, rxx);
	t[u].val = min(t[LCH].val, t[RCH].val);
}

void Upd(int u)
{
	if (t[u].l >= lx && t[u].r <= rx)
	{
		t[u].val += vx;
		t[u].tag += vx;
		return;
	}
	Pushdown(u);
	int mid = (t[u].l + t[u].r) / 2;
	if (lx <= mid) Upd(LCH);
	if (rx > mid) Upd(RCH);
	t[u].val = min(t[LCH].val, t[RCH].val);
}

int Qry(int u)
{
	if (t[u].l >= lx && t[u].r <= rx)
		return t[u].val;
	Pushdown(u);
	int mid = (t[u].l + t[u].r) / 2;
	int ret = 1e12;
	if (lx <= mid) ret = min(ret, Qry(LCH));
	if (rx > mid) ret = min(ret, Qry(RCH));
	//t[u].val = min(t[LCH].val, t[RCH].val);
	return ret;
}

void Solve()
{
	scanf("%d%d", &n, &k);
	for (int i=1;i<=n;i++)
		scanf("%d", &ai[i]);
	
	BuildTree(1, 1, n);
	
	ll ans = 0; 
	for (int i=1;i<=n-k+1;i++)
	{
		lx = i; rx = i+k-1;
		vx = -Qry(1);
		if (vx < 0)
		{
			ans+=(-vx);
			Upd(1);
		}
	}
	
	printf("%lld\n", ans);
}

int main()
{
	int T; scanf("%d", &T);
	while (T--)
	{
		Solve();
	}
	
}