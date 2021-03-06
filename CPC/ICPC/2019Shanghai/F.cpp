#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<queue>
#include<map>
typedef long long ll;
using namespace std;

struct ed
{
	int pre,to;
}edge[200010];
int at,ptr[100010],n,m;

const ll mod = 1000000007;
int nodev[100010], nnv[100010];

template<typename int_t>
void readx(int_t &x)
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
}

namespace SGT
{
	#define LCH (inx<<1)
	#define RCH (inx<<1|1)
	
	struct SGT
	{
		int l,r;
		int ta,tm,v,v2,v3;
	}t[4*100010];
	int va,vm,lx,rx;
	
	void NodeMul(int ch, int m)
	{
		int m2=(1LL*m*m)%mod;
		int m3=(1LL*m*m2)%mod;
		
		t[ch].ta=(1LL*t[ch].ta*m)%mod;
		t[ch].tm=(1LL*t[ch].tm*m)%mod;
		
		t[ch].v=(1LL*t[ch].v*m)%mod;
		t[ch].v2=(1LL*t[ch].v2*m2)%mod;
		t[ch].v3=(1LL*t[ch].v3*m3)%mod;
	}
	
	void NodeAdd(int ch, const int a, const int len)
	{
		int a2=(1LL*a*a)%mod;
		int a3=(1LL*a2*a)%mod;
		
		t[ch].v3=(t[ch].v3 + (1LL*a3*len)%mod )%mod;
		t[ch].v3=(t[ch].v3 + (3LL*a2*t[ch].v)%mod )%mod;
		t[ch].v3=(t[ch].v3 + (3LL*a*t[ch].v2)%mod )%mod;
		
		t[ch].v2=(t[ch].v2 + (1LL*a2*len)%mod )%mod;
		t[ch].v2=(t[ch].v2 + (2LL*a*t[ch].v)%mod )%mod;
		
		t[ch].v=(t[ch].v + (1LL*a*len)%mod )%mod;
		
		t[ch].ta=(t[ch].ta+a)%mod;
	}
	
	void Pushdown(int inx)
	{
		int a=t[inx].ta, m=t[inx].tm;
		t[inx].tm=1; t[inx].ta=0;
		if (m!=1)
		{
			NodeMul(LCH,m);
			NodeMul(RCH,m);
		}
		if (a!=0)
		{
			NodeAdd(LCH,a,t[LCH].r-t[LCH].l+1);
			NodeAdd(RCH,a,t[RCH].r-t[RCH].l+1);
		}
	}
	
	void Pushup(int inx)
	{
		t[inx].v=(t[LCH].v+t[RCH].v)%mod;
		t[inx].v2=(t[LCH].v2+t[RCH].v2)%mod;
		t[inx].v3=(t[LCH].v3+t[RCH].v3)%mod;
	}
	
	void BuildTree(int inx,int lxx,int rxx)
	{
		t[inx].l=lxx; t[inx].r=rxx; 
		t[inx].ta=0; t[inx].tm=1;
		if (lxx==rxx)
		{
			t[inx].v=nnv[lxx];
			t[inx].v2=(1LL*nnv[lxx]*nnv[lxx])%mod;
			t[inx].v3=(1LL*nnv[lxx]*t[inx].v2)%mod;
			return;
		}
		int mid = (lxx+rxx)/2;
		BuildTree(LCH, lxx, mid);
		BuildTree(RCH, mid+1, rxx);
		Pushup(inx);
	}
	
	void Upd(int inx)
	{
		if (t[inx].l>=lx && t[inx].r<=rx)
		{
			NodeMul(inx,vm);
			NodeAdd(inx,va,t[inx].r-t[inx].l+1);
			return;
		}
		Pushdown(inx);
		int mid = (t[inx].l+t[inx].r)/2;
		if (lx<=mid) Upd(LCH);
		if (rx>mid) Upd(RCH);
		Pushup(inx);
	}
	
	int Qry(int inx)
	{
		int ret = 0;
		if (t[inx].l>=lx && t[inx].r<=rx)
			return t[inx].v3;
		Pushdown(inx);
		int mid = (t[inx].l+t[inx].r)/2;
		if (lx<=mid) ret=(ret+Qry(LCH))%mod;
		if (rx>mid) ret=(ret+Qry(RCH))%mod;
		Pushup(inx);
		return (ret+mod)%mod;
	}
	
	#undef LCH
	#undef RCH
}

namespace HLP
{
	int tsiz[100010], topv[100010], anc[100010], dfn[100010], hson[100010];
	int stamp, dep[100010];
	
	void Fancy(int now, int fa, int ndep)
	{
		dep[now]=ndep; anc[now]=fa; tsiz[now]=1;
		for (int v=ptr[now];v;v=edge[v].pre) if (edge[v].to!=fa)
		{
			Fancy(edge[v].to,now,ndep+1);
			tsiz[now]+=tsiz[edge[v].to];
			if (tsiz[hson[now]]<tsiz[edge[v].to]) hson[now]=edge[v].to;
		}
	}
	
	void Dreams(int now, int src)
	{
		dfn[now]=++stamp; topv[now]=src; nnv[stamp]=nodev[now];
		if (hson[now]) Dreams(hson[now], src);
		for (int v=ptr[now];v;v=edge[v].pre)
			if (edge[v].to!=anc[now] && edge[v].to!=hson[now])
				Dreams(edge[v].to, edge[v].to);
	}
	
	void UpdRg(int u, int v, int va, int vm)
	{
		SGT::va=va; SGT::vm=vm;
		while (topv[u]!=topv[v])
		{
			if (dep[topv[u]]<dep[topv[v]]) swap(u,v);
			SGT::lx=dfn[topv[u]]; SGT::rx=dfn[u]; SGT::Upd(1);
			u=anc[topv[u]];
		}
		if (dep[v]>dep[u]) swap(u,v);
		SGT::lx=dfn[v]; SGT::rx=dfn[u]; SGT::Upd(1);
	}
	
	int QryRg(int u, int v)
	{
		int ret=0;
		while (topv[u]!=topv[v])
		{
			if (dep[topv[u]]<dep[topv[v]]) swap(u,v);
			SGT::lx=dfn[topv[u]]; SGT::rx=dfn[u]; ret=(ret+SGT::Qry(1))%mod;
			u=anc[topv[u]];
		}
		if (dep[v]>dep[u]) swap(u,v);
		SGT::lx=dfn[v]; SGT::rx=dfn[u]; ret=(ret+SGT::Qry(1))%mod;
		return (ret+mod)%mod;
	}
}

void Clear()
{
	for (int i=1;i<=n;i++) ptr[i]=0;
	at=0;
	for (int i=1;i<=n;i++)
	{
		nodev[i]=nnv[i]=0;
		HLP::dep[i]=HLP::anc[i]=HLP::hson[i]=0;
		HLP::dfn[i]=HLP::topv[i]=HLP::tsiz[i]=0;
		HLP::stamp=0;
	}
}

void Solve()
{
	readx(n); int u,v;
	for (int i=1;i<n;i++)
	{
		readx(u); readx(v);
		Is(u,v); Is(v,u);
	}
	for (int i=1;i<=n;i++) readx(nodev[i]);
	
	HLP::Fancy(1,0,1);
	HLP::Dreams(1,1);
	SGT::BuildTree(1,1,n);
	
	int q; readx(q);
	int op, w;
	while (q--)
	{
		readx(op);
		readx(u); readx(v);
		if (op!=4) readx(w);
		
		if (op==1)
			HLP::UpdRg(u,v,w,0);
		else if (op==2)
			HLP::UpdRg(u,v,w,1);
		else if (op==3)
			HLP::UpdRg(u,v,0,w);
		else
			printf("%d\n", HLP::QryRg(u,v));
	}
}

int main()
{
	int T; readx(T);
	for (int tt=1;tt<=T;tt++)
	{
		printf("Case #%d:\n", tt);
		Solve();
		Clear();
	}
}