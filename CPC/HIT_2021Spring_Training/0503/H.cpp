#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<algorithm>
#include<cmath>
#include<cstdlib>
#include<vector>
#include<string>
typedef long long ll;
using namespace std;

struct ed
{
	int pre, to;
}edge[1000010];
int at=1,ptr[500010];

int n, m, f[500010], ai[500010];

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

void Is(int u, int v)
{
	at++;
	edge[at].pre = ptr[u];
	edge[at].to = v;
	ptr[u]=at;
}

namespace SGT
{
	struct Seg_Tree
	{
		int l, r;
		int val, maxv;
	}t[500010*4];
	int lx, rx, px, vx;
	
	void BuildTree(int inx, int lxx, int rxx)
	{
		t[inx].l=lxx; t[inx].r=rxx;
		if (lxx==rxx) return;
		int mid = (lxx + rxx) / 2;
		BuildTree(inx<<1, lxx, mid);
		BuildTree(inx<<1|1, mid+1, rxx);
	}
	
	void Upd(int inx)
	{
		if (t[inx].l==px && t[inx].r==px)
		{
			t[inx].val = vx;
			return;
		}
		int mid = (t[inx].l + t[inx].r) / 2;
		if (px <= mid) Upd(inx<<1);
		else Upd(inx<<1|1);
		t[inx].val=max(t[inx<<1].val, t[inx<<1|1].val);
	}
	
	int Qry(int inx)
	{
		if (t[inx].l>=lx && t[inx].r<=rx) 
			return t[inx].val;
		int mid = (t[inx].l + t[inx].r) / 2, ret = 0;
		if (lx<=mid) ret=max(ret, Qry(inx<<1));
		if (rx>mid) ret=max(ret, Qry(inx<<1|1));
		return ret;
	}
}

namespace HLP
{
	int tsiz[500010], topx[500010], anc[500010], dep[500010], hson[500010];
	int dfn[500010], tcnt;
	
	void DFS1(int u, int fa)
	{
		dep[u]=dep[fa]+1; anc[u]=fa; tsiz[u]=1;
		for (int v=ptr[u];v;v=edge[v].pre) if (edge[v].to!=fa)
		{
			DFS1(edge[v].to, u);
			tsiz[u]+=tsiz[edge[v].to];
			if (tsiz[edge[v].to]>tsiz[hson[u]])
				hson[u]=edge[v].to;
		}
	}
	
	void DFS2(int u, int src)
	{
		dfn[u]=++tcnt; topx[u]=src;
		if (hson[u]) DFS2(hson[u], src);
		for (int v=ptr[u];v;v=edge[v].pre) 
			if (edge[v].to!=anc[u] && edge[v].to!=hson[u])
				DFS2(edge[v].to, edge[v].to);
	}
	
	void Upd(int u, int val)
	{
		SGT::vx = val;
		SGT::px = dfn[u];
		SGT::Upd(1);
	}
	
	int Qry(int u, int v)
	{
		int ret = 0;
		while (topx[u]!=topx[v])
		{
			if (dep[topx[u]]<dep[topx[v]]) swap(u, v);
			SGT::lx = dfn[topx[u]]; SGT::rx = dfn[u];
			ret = max(ret, SGT::Qry(1));
			u = anc[topx[u]];
		}
		if (dep[v]<dep[u]) swap(u, v);
		SGT::lx = dfn[u]; SGT::rx = dfn[v];
		ret = max(ret, SGT::Qry(1));
		return ret;
	}
}

int main()
{
	readx(n); readx(m);
	for (int i=2;i<=n;i++) readx(f[i]);
	for (int i=1;i<=m;i++) readx(ai[i]);
	
	for (int i=2;i<=n;i++)
	{
		Is(f[i], i);
	}
	
	HLP::DFS1(1, 0);
	HLP::DFS2(1, 1);
	SGT::BuildTree(1, 1, n);
	
	int ans = 1;
	for (int i=1;i<=m;i++)
	{
		int tmp;
		if (ai[i]==1)
		{
			HLP::Upd(1, 1);
		}
		else
		{
			tmp = HLP::Qry(1, f[ai[i]]);
			ans = max(ans, tmp+1);
			HLP::Upd(ai[i], tmp+1);
		}
		
	}
	cout << ans << endl;
	return 0;
}