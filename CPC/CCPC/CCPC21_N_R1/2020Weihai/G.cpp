#include<bits/stdc++.h>
typedef long long ll;
using namespace std;

const int c1 = 233;
const ll mod = 1e9+9;

int c1n[500010];
int pf_c1n[500010];

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

ll fastpow(ll an, ll p)
{
	ll ret = 1;
	for (;p;p>>=1, an=an*an%mod) if (p&1) ret = ret * an % mod;
	return ret;
}

struct SegT
{
	int l, r;
	int tag, val;
	ll hsh;
}t[500010*4];
int n, q, lx, rx, px, vx;
unsigned short a[500010];

#define LCH (u<<1)
#define RCH (u<<1|1)

void Pushup(int u)
{
	t[u].val = max(t[LCH].val, t[RCH].val);
	t[u].hsh = (t[LCH].hsh + t[RCH].hsh)%mod;
}

void Pushdown(int u)
{
	if (!t[u].tag) return;
	int tag = t[u].tag; t[u].tag = 0;
	t[LCH].tag += tag; t[RCH].tag += tag;
	t[LCH].val += tag; t[RCH].val += tag;
	t[LCH].hsh = (1LL * t[LCH].hsh + 
		1LL * (pf_c1n[t[LCH].r] - pf_c1n[t[LCH].l-1])*tag%mod + 3LL * mod) % mod;
	t[RCH].hsh = (1LL * t[RCH].hsh + 
		1LL * (pf_c1n[t[RCH].r] - pf_c1n[t[RCH].l-1])*tag%mod + 3LL * mod) % mod;
}

void BuildTree(int u, int lxx, int rxx)
{
	t[u].l = lxx; 
	t[u].r = rxx;
	if (lxx==rxx)
	{
		t[u].val = a[lxx];
		t[u].hsh = 1LL*c1n[lxx]*a[lxx]%mod;
		t[u].tag = 0;
		return;
	}
	int mid = (lxx+rxx)/2;
	BuildTree(LCH, lxx, mid);
	BuildTree(RCH, mid+1, rxx);
	Pushup(u);
}

void Upd(int u, int L, int R)
{
	if (L>=lx && R<=rx)
	{
		t[u].val += 1;
		t[u].tag += 1;
		t[u].hsh = (1LL*t[u].hsh + 
			1LL*(pf_c1n[R]-pf_c1n[L-1])%mod + 2LL*mod)%mod;
		return;
	}
	Pushdown(u);
	int mid = (L+R)/2;
	if (lx<=mid) Upd(LCH, L, mid);
	if (rx>mid) Upd(RCH, mid+1, R);
	Pushup(u);
}

unsigned int Qry(int u, int L, int R)
{
	if (L>=lx && R<=rx)
		return t[u].hsh;
	Pushdown(u);
	unsigned int ret = 0;
	int mid = (L+R)/2;
	if (lx <= mid)
		ret = Qry(LCH, L, mid);
	if (rx > mid)
		ret = (ret + Qry(RCH, mid+1, R)) % mod;
	Pushup(u);
	return ret;
}

void CutHash(int u)
{
	if (t[u].l == t[u].r)
	{
		t[u].hsh = 0;
		t[u].val = 0;
		return;
	}
	Pushdown(u);
	if (t[LCH].val == 65536)
		CutHash(LCH);
	if (t[RCH].val == 65536)
		CutHash(RCH);
	Pushup(u);
}

int main()
{
	c1n[0]=1;
	for (int i=1;i<=500000;i++)
		c1n[i]=1LL*c1n[i-1]*c1%mod;
	pf_c1n[0]=1;
	for (int i=1;i<=500000;i++)
		pf_c1n[i]=(pf_c1n[i-1]+c1n[i])%mod;
	
	readx(n); readx(q);
	for (int i=1;i<=n;i++)
		readx(a[i]);
	
	BuildTree(1, 1, n);
	
	int op, l, r, x, y;
	for (int qi=1;qi<=q;qi++)
	{
		readx(op);
		if (op == 1)
		{
			readx(lx); readx(rx);
			Upd(1, 1, n);
			CutHash(1);
		}
		else
		{
			readx(l); readx(x); readx(op);
			if (l>x) swap(l, x);
			y = x + op - 1;
			r = l + op - 1;
			
			lx = l; rx = r;
			unsigned int h1 = Qry(1, 1, n);
			lx = x; rx = y;
			unsigned int h2 = Qry(1, 1, n);
			
			h1 = (1LL * h1 * c1n[x-l]) % mod;
			if (h1 == h2) puts("yes");
			else puts("no");
		}
	}
}