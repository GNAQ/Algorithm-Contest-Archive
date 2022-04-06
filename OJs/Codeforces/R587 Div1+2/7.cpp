#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

#define LCH (u<<1)
#define RCH (u<<1|1)

struct SegNode
{
	int tag;
	int lmaxc, rmaxc, mmaxc;
	int midans, minb;
}t[200010 * 4];
int lx, rx, px, vx;

int n, q;
set<int> stx[200010];
int ai[200010];

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

void Pushdown(int u)
{
	t[LCH].tag += t[u].tag;
	t[RCH].tag += t[u].tag;
	t[LCH].minb += t[u].tag;
	t[RCH].minb += t[u].tag;
	t[u].tag = 0;
}

void Pushup(int u)
{
	t[u].minb = min(t[LCH].minb, t[RCH].minb);
	t[u].mmaxc = max(t[LCH].mmaxc, t[RCH].mmaxc);
	// case 1: L minB > R minB
	if (t[LCH].minb > t[RCH].minb)
	{
		t[u].lmaxc = max(t[LCH].mmaxc, t[RCH].lmaxc);
		t[u].rmaxc = t[RCH].rmaxc;
		t[u].midans = t[RCH].midans;
	}
	// case 2: L minB < R minB
	else if (t[LCH].minb < t[RCH].minb)
	{
		t[u].rmaxc = max(t[RCH].mmaxc, t[LCH].rmaxc);
		t[u].lmaxc = t[LCH].lmaxc;
		t[u].midans = t[LCH].midans;
	}
	// case 3: ==
	else if (t[LCH].minb == t[RCH].minb)
	{
		t[u].lmaxc = t[LCH].lmaxc;
		t[u].rmaxc = t[RCH].rmaxc;
		t[u].midans = t[LCH].midans + t[RCH].midans + max(t[LCH].rmaxc, t[RCH].lmaxc);
	}
}

// Queries func are not needed, 'cause there is no subrange queries; we only need values in root
void UpdB(int u, int l, int r)
{
	// cerr << "UPDB " << u << " " << lx << " " << rx << endl;
	if (lx > rx) return;
	if (l >= lx && r <= rx)
	{
		t[u].minb += vx;
		t[u].tag += vx;
		return;
	}
	if (t[u].tag) Pushdown(u);
	int mid = (l + r) / 2;
	if (lx <= mid) UpdB(LCH, l, mid);
	if (rx >  mid) UpdB(RCH, mid + 1, r);
	Pushup(u);
}

void UpdC(int u, int l, int r)
{
	// cerr << "UPDC " << u << " " << lx << " " << rx << " | " << l << " " << r << endl;
	if (l == px && r == px)
	{
		t[u].lmaxc = t[u].mmaxc = vx;
		// 注意这里 rmaxc 和 midans 是不设值的！！！！！！！
		// 可以通过手推最低两（三）层的合并得到应该怎么做
		// 一定要推，一定不要想当然
		return;
	}
	if (t[u].tag) Pushdown(u);
	int mid = (l + r) / 2;
	if (px <= mid) UpdC(LCH, l, mid);
	if (px > mid) UpdC(RCH, mid + 1, r);
	Pushup(u);
}

void Ins(int p)
{
	if (stx[ai[p]].size())
	{
		lx = *stx[ai[p]].begin(); rx = (*stx[ai[p]].rbegin()) - 1;
		vx = -1;
		UpdB(1, 1, n);
		px = *stx[ai[p]].begin();
		vx = 0;
		UpdC(1, 1, n);
	}
	// cerr << "OK1 " << p << endl;
	stx[ai[p]].insert(p);
	lx = *stx[ai[p]].begin(); rx = (*stx[ai[p]].rbegin()) - 1;
	vx = 1;
	UpdB(1, 1, n);
	px = *stx[ai[p]].begin();
	vx = stx[ai[p]].size();
	UpdC(1, 1, n);
}

void Del(int p)
{
	lx = *stx[ai[p]].begin(); rx = (*stx[ai[p]].rbegin()) - 1;
	vx = -1;
	UpdB(1, 1, n);
	px = *stx[ai[p]].begin();
	vx = 0;
	UpdC(1, 1, n);
	
	stx[ai[p]].erase(p);
	if (stx[ai[p]].size())
	{
		lx = *stx[ai[p]].begin(); rx = (*stx[ai[p]].rbegin()) - 1;
		vx = 1;
		UpdB(1, 1, n);
		px = *stx[ai[p]].begin();
		vx = stx[ai[p]].size();
		UpdC(1, 1, n);
	}
}

int main()
{
	readx(n); readx(q);
	for (int i=1;i<=n;i++)
	{
		readx(ai[i]);
		Ins(i);
	}
	printf("%d\n", n - t[1].midans - t[1].lmaxc - t[1].rmaxc);
	int x, val;
	for (int i=1;i<=q;i++)
	{
		readx(x); readx(val);
		Del(x);
		ai[x] = val;
		Ins(x);
		printf("%d\n", n - t[1].midans - t[1].lmaxc - t[1].rmaxc);
	}
}

/*
Soluton:

	Please refer to:
	  https://www.cnblogs.com/18Michael/p/14974099.html
	
*/