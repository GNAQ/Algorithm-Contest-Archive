#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<iterator>
#include<cstdlib>
#include<queue>
#include<vector>
#include<map>
#include<set>
using namespace std;
typedef long long ll;
typedef ostream_iterator<int> os_iter_int;

struct ed { int pre,to; } edge[200010];
int at=1,ptr[100010];

int m,n,root; ll mod,nodev[100010];

template<typename inp_t>
void readx(inp_t& x)
{
	x=0; int k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

void Is(int fx,int tx)
{
	at++;
	edge[at].pre=ptr[fx];
	edge[at].to=tx;
	ptr[fx]=at;
	at++;
	edge[at].pre=ptr[tx];
	edge[at].to=fx;
	ptr[tx]=at;
}

namespace HLD
{
	#define LCH (inx<<1)
	#define RCH (inx<<1|1)
	
	struct Seg_Tree
	{
		int l,r,mid;
		ll val,tag;
	}tree[400010];
	int _lx,_rx,_pos; ll _val;
	
	int topx[100010],anc[100010],dep[100010];
	int hson[100010],tsiz[100010],dfn[100010],dfst;
	ll nnv[100010];
	
	void Fancy(int now,int ndep,int fa)
	{
		tsiz[now]=1; dep[now]=ndep; anc[now]=fa;
		for (int v=ptr[now];v;v=edge[v].pre) if (edge[v].to!=fa)
		{
			Fancy(edge[v].to,ndep+1,now);
			tsiz[now]+=tsiz[edge[v].to];
			if (tsiz[edge[v].to]>tsiz[hson[now]]) hson[now]=edge[v].to;
		}
	}
	void Dreams(int now,int src)
	{
		dfst++; dfn[now]=dfst; topx[now]=src; nnv[dfst]=nodev[now];
		if (hson[now]) Dreams(hson[now],src);
		for (int v=ptr[now];v;v=edge[v].pre) 
			if (edge[v].to!=anc[now] && edge[v].to!=hson[now]) Dreams(edge[v].to,edge[v].to);
	}
	
	void BuildTree(int inx,int lxx,int rxx)
	{
		tree[inx].l=lxx; tree[inx].r=rxx; tree[inx].mid=(lxx+rxx)>>1;
		if (lxx==rxx) 
		{
			tree[inx].val=nnv[tree[inx].mid];
			return;
		}
		BuildTree(LCH,lxx,tree[inx].mid);
		BuildTree(RCH,tree[inx].mid+1,rxx);
		tree[inx].val=(tree[LCH].val+tree[RCH].val)%mod;
	}
	void Pushdown(int inx)
	{
		ll tmp=tree[inx].tag; tree[inx].tag=0;
		tree[LCH].tag=(tree[LCH].tag+tmp)%mod;
		tree[RCH].tag=(tree[RCH].tag+tmp)%mod;
		tree[LCH].val=(tree[LCH].val+tmp*(tree[LCH].r-tree[LCH].l+1)%mod)%mod;
		tree[RCH].val=(tree[RCH].val+tmp*(tree[RCH].r-tree[RCH].l+1)%mod)%mod;
	}
	void Seg_Upd(int inx)
	{
		if (tree[inx].l>=_lx && tree[inx].r<=_rx)
		{
			tree[inx].val=(tree[inx].val+_val*(tree[inx].r-tree[inx].l+1)%mod)%mod;
			tree[inx].tag=(tree[inx].tag+_val)%mod; return;
		}
		if (tree[inx].tag) Pushdown(inx);
		if (_lx<=tree[inx].mid) Seg_Upd(LCH);
		if (_rx>tree[inx].mid) Seg_Upd(RCH);
		tree[inx].val=(tree[LCH].val+tree[RCH].val)%mod;
	}
	ll Seg_Qry(int inx)
	{
		if (tree[inx].l>=_lx && tree[inx].r<=_rx) return tree[inx].val;
		if (tree[inx].tag) Pushdown(inx);
		ll ret=0;
		if (_lx<=tree[inx].mid) ret+=Seg_Qry(LCH);
		if (_rx>tree[inx].mid) ret=(ret+Seg_Qry(RCH))%mod;
		tree[inx].val=(tree[LCH].val+tree[RCH].val)%mod;
		return ret%mod;
	}
	
	void UpdPnt(int u,ll w)
	{
		_lx=dfn[u]; _rx=dfn[u]+tsiz[u]-1;
		_val=w; Seg_Upd(1);
	}
	ll QryPnt(int u)
	{
		_lx=dfn[u]; _rx=dfn[u]+tsiz[u]-1;
		return Seg_Qry(1);
	}
	void UpdPth(int u,int v,ll w)
	{
		_val=w;
		while (topx[u]!=topx[v])
		{
			if (dep[topx[u]]<dep[topx[v]]) swap(u,v);
			_lx=dfn[topx[u]]; _rx=dfn[u]; Seg_Upd(1);
			u=anc[topx[u]];
		}
		if (dep[v]>dep[u]) swap(u,v);
		_lx=dfn[v]; _rx=dfn[u]; Seg_Upd(1);
	}
	ll QryPth(int u,int v)
	{
		ll ret=0;
		while (topx[u]!=topx[v])
		{
			if (dep[topx[u]]<dep[topx[v]]) swap(u,v);
			_lx=dfn[topx[u]]; _rx=dfn[u]; ret=(ret+Seg_Qry(1))%mod;
			u=anc[topx[u]];
		}
		if (dep[v]>dep[u]) swap(u,v);
		_lx=dfn[v]; _rx=dfn[u]; ret=(ret+Seg_Qry(1))%mod;
		return ret;
	}
	
	#undef LCH
	#undef RCH
};

int main()
{
	readx(n); readx(m); readx(root); readx(mod); int fx,tx;
	for (int i=1;i<=n;i++) readx(nodev[i]);
	for (int i=1;i<n;i++)
	{
		readx(fx); readx(tx);
		Is(fx,tx);
	}
	
	HLD::Fancy(root,1,0);
	HLD::Dreams(root,root);
	HLD::BuildTree(1,1,n);
	
	int opt,u,v; ll val;
	while (m--)
	{
		readx(opt);
		if (opt==1)
		{
			readx(u); readx(v); readx(val);
			HLD::UpdPth(u,v,val);
		}
		if (opt==2)
		{
			readx(u); readx(v); 
			printf("%lld\n",HLD::QryPth(u,v));
		}
		if (opt==3)
		{
			readx(u); readx(val);
			HLD::UpdPnt(u,val);
		}
		if (opt==4)
		{
			readx(u); 
			printf("%lld\n",HLD::QryPnt(u));
		}
	}
}