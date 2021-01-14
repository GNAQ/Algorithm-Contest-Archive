#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#define ll long long
using namespace std;

struct ed { int pre,to; }edge[200010];
int at,ptr[100010],n,m,rot; 
ll mod,nodev[100010],nnv[100010];

template<typename int_t>
void readx(int_t& x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

void Is(int fx,int tx)
{
	edge[++at].pre=ptr[fx];
	edge[at].to=tx;
	ptr[fx]=at;
	edge[++at].pre=ptr[tx];
	edge[at].to=fx;
	ptr[tx]=at;
}

namespace SGT
{
	struct Seg_tree
	{
		int l,r;
		ll val,tag;
	}tree[4*100010];
	int lx,rx; ll Val;
	
	void BuildTree(int inx,int lxx,int rxx)
	{
		tree[inx].l=lxx; tree[inx].r=rxx;
		if (lxx==rxx)
		{
			tree[inx].val=nnv[lxx];
			return;
		}
		int mid=(lxx+rxx)>>1;
		BuildTree(inx<<1,lxx,mid);
		BuildTree(inx<<1|1,mid+1,rxx);
		tree[inx].val=(tree[inx<<1].val+tree[inx<<1|1].val)%mod;
	}
	
	void Pushdown(int inx)
	{
		ll tmp=tree[inx].tag; tree[inx].tag=0;
		tree[inx<<1].tag+=tmp; tree[inx<<1|1].tag+=tmp;
		tree[inx<<1].val+=(tree[inx<<1].r-tree[inx<<1].l+1)*tmp%mod;
		tree[inx<<1|1].val+=(tree[inx<<1|1].r-tree[inx<<1|1].l+1)*tmp%mod;
		tree[inx<<1].val%=mod; tree[inx<<1|1].val%=mod;
		tree[inx<<1].tag%=mod; tree[inx<<1|1].tag%=mod;
	}
	
	void Upd(int inx)
	{
		if (tree[inx].l>=lx && tree[inx].r<=rx)
		{
			tree[inx].tag=(tree[inx].tag+Val)%mod;
			tree[inx].val+=(tree[inx].r-tree[inx].l+1)*Val%mod;
			tree[inx].val%=mod; return;
		}
		if (tree[inx].tag) Pushdown(inx);
		int mid=(tree[inx].r+tree[inx].l)>>1;
		if (lx<=mid) Upd(inx<<1);
		if (rx>mid) Upd(inx<<1|1);
		tree[inx].val=(tree[inx<<1].val+tree[inx<<1|1].val)%mod;
	}
	
	ll Qry(int inx)
	{
		if (tree[inx].l>=lx && tree[inx].r<=rx) return tree[inx].val;
		if (tree[inx].tag) Pushdown(inx);
		int mid=(tree[inx].l+tree[inx].r)>>1; ll ret=0;
		if (lx<=mid) ret=Qry(inx<<1);
		if (rx>mid) ret=(ret+Qry(inx<<1|1))%mod;
		tree[inx].val=(tree[inx<<1].val+tree[inx<<1|1].val)%mod;
		return ret%mod;
	}
};

namespace HLP
{
	int tsiz[100010],topx[100010],anc[100010],dfn[100010],hson[100010];
	int tstamp,dep[100010];

	void Fancy(int now,int fa,int ndep)
	{
		dep[now]=ndep; anc[now]=fa; tsiz[now]=1;
		for (int v=ptr[now];v;v=edge[v].pre) if (edge[v].to!=fa)
		{
			Fancy(edge[v].to,now,ndep+1);
			tsiz[now]+=tsiz[edge[v].to];
			if (tsiz[hson[now]]<tsiz[edge[v].to]) hson[now]=edge[v].to;
		}
	}
	
	void Dreams(int now,int src)
	{
		dfn[now]=++tstamp; topx[now]=src; nnv[tstamp]=nodev[now];
		if (hson[now]) Dreams(hson[now],src);
		for (int v=ptr[now];v;v=edge[v].pre)
			if (edge[v].to!=anc[now] && edge[v].to!=hson[now]) 
				Dreams(edge[v].to,edge[v].to);
	}
	
	void UpdRg(int u,int v,ll val)
	{
		SGT::Val=val;
		while (topx[u]!=topx[v])
		{
			if (dep[topx[u]]<dep[topx[v]]) swap(u,v);
			SGT::lx=dfn[topx[u]]; SGT::rx=dfn[u]; SGT::Upd(1);
			u=anc[topx[u]];
		}
		if (dep[v]>dep[u]) swap(u,v);
		SGT::lx=dfn[v]; SGT::rx=dfn[u]; SGT::Upd(1);
 	}
	void UpdPt(int now,ll val)
	{
		SGT::lx=dfn[now]; SGT::rx=dfn[now]+tsiz[now]-1; SGT::Val=val;
		SGT::Upd(1);
	}
	ll QryRg(int u,int v)
	{
		ll ret=0;
		while (topx[u]!=topx[v])
		{
			if (dep[topx[u]]<dep[topx[v]]) swap(u,v);
			SGT::lx=dfn[topx[u]]; SGT::rx=dfn[u]; ret=(ret+SGT::Qry(1))%mod;
			u=anc[topx[u]];
		}
		if (dep[u]<dep[v]) swap(u,v);
		SGT::lx=dfn[v]; SGT::rx=dfn[u]; ret=(ret+SGT::Qry(1))%mod;
		return ret%mod;
	}
	ll QryPt(int now)
	{
		SGT::lx=dfn[now]; SGT::rx=dfn[now]+tsiz[now]-1;
		return SGT::Qry(1)%mod;
	}
};

int main()
{
	readx(n); readx(m); readx(rot); readx(mod); int fx,tx;
	for (int i=1;i<=n;i++) readx(nodev[i]);
	for (int i=1;i<n;i++)
	{
		readx(fx); readx(tx);
		Is(fx,tx);
	}
	
	HLP::Fancy(rot,0,1);
	HLP::Dreams(rot,rot);
	SGT::BuildTree(1,1,n);
	
	int opt,u,v; ll val;
	for (int i=1;i<=m;i++)
	{
		readx(opt);
		if (opt==1)
		{
			readx(u); readx(v); readx(val);
			HLP::UpdRg(u,v,val);
		}
		else if (opt==2)
		{
			readx(u); readx(v);
			printf("%lld\n",HLP::QryRg(u,v));
		}
		else if (opt==3)
		{
			readx(u); readx(val);
			HLP::UpdPt(u,val);
		}
		else { readx(u); printf("%lld\n",HLP::QryPt(u)); }
	}
}
