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
using namespace std;

struct ed { int pre,to; } edge[200010]={0};
struct segment_tree { int l,r,w,tag; } SGT[400010]={0};
int nodenum,rootx,opt,typ,mo,fx,tx,at=0,pointer[100010]={0};

int hson[100010]={0},dfn[100010]={0},dep[100010]={0},anc[100010]={0};
int topx[100010]={0},tstamp=0,tsize[100010]={0},nnv[100010]={0},nodev[100010]={0};

int lx,rx,val,ux,vx,ans;

inline void readx(int& x)
{
	x=0; int k=1; register char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}
inline void Insert()
{
	at++;
	edge[at].pre=pointer[fx];
	edge[at].to=tx;
	pointer[fx]=at;
	at++;
	edge[at].pre=pointer[tx];
	edge[at].to=fx;
	pointer[tx]=at;
}

inline void Fancy(int nownode,int nowdep,int fa)
{
	tsize[nownode]=1; dep[nownode]=nowdep; anc[nownode]=fa;
	for (int prex=pointer[nownode];prex;prex=edge[prex].pre) if (edge[prex].to!=fa)
	{
		Fancy(edge[prex].to,nowdep+1,nownode);
		tsize[nownode]+=tsize[edge[prex].to];
		if (tsize[edge[prex].to]>tsize[hson[nownode]]) hson[nownode]=edge[prex].to;
	}
}
inline void Dreams(int nownode,int src)
{
	dfn[nownode]=++tstamp; topx[nownode]=src; nnv[tstamp]=nodev[nownode];
	if (hson[nownode]) Dreams(hson[nownode],src);
	for (int prex=pointer[nownode];prex;prex=edge[prex].pre)
		if (edge[prex].to!=anc[nownode] && edge[prex].to!=hson[nownode]) Dreams(edge[prex].to,edge[prex].to);
}

inline void BuildTree(int lxx,int rxx,int inx)
{
	SGT[inx].l=lxx; SGT[inx].r=rxx;
	if (lxx==rxx) { SGT[inx].w=nnv[lxx]; return; }
	int mid=(lxx+rxx)>>1;
	BuildTree(lxx,mid,inx<<1);
	BuildTree(mid+1,rxx,inx<<1|1);
	SGT[inx].w=(SGT[inx<<1].w+SGT[inx<<1|1].w)%mo;
}
inline void pushdown(int inx)
{
	SGT[inx<<1].tag+=SGT[inx].tag; SGT[inx<<1].tag%=mo;
	SGT[inx<<1|1].tag+=SGT[inx].tag; SGT[inx<<1|1].tag%=mo;
	SGT[inx<<1].w+=(SGT[inx<<1].r-SGT[inx<<1].l+1)*SGT[inx].tag; SGT[inx<<1].w%=mo;
	SGT[inx<<1|1].w+=(SGT[inx<<1|1].r-SGT[inx<<1|1].l+1)*SGT[inx].tag; SGT[inx<<1|1].w%=mo;
	SGT[inx].tag=0;
}
inline void update(int inx)
{
	if (SGT[inx].l>=lx && SGT[inx].r<=rx)
	{
		SGT[inx].w+=val*(SGT[inx].r-SGT[inx].l+1);
		SGT[inx].tag+=val; SGT[inx].tag%=mo; SGT[inx].w%=mo;
		return;
	}
	if (SGT[inx].tag) pushdown(inx);
	int mid=(SGT[inx].l+SGT[inx].r)>>1;
	if (lx<=mid) update(inx<<1);
	if (rx>mid) update(inx<<1|1);
	SGT[inx].w=(SGT[inx<<1].w+SGT[inx<<1|1].w)%mo;
}
inline int query(int inx)
{
	if (SGT[inx].l>=lx && SGT[inx].r<=rx) return SGT[inx].w;
	if (SGT[inx].tag) pushdown(inx);
	int mid=(SGT[inx].l+SGT[inx].r)>>1,ret=0;
	if (mid>=lx) ret+=query(inx<<1);
	if (mid<rx) ret=(ret+query(inx<<1|1))%mo;
	SGT[inx].w=(SGT[inx<<1].w+SGT[inx<<1|1].w)%mo;
	return ret;
}

inline void upd_range(int u,int v)
{
	while (topx[u]!=topx[v])
	{
		if (dep[topx[u]]<dep[topx[v]]) swap(u,v);
		lx=dfn[topx[u]]; rx=dfn[u]; update(1);
		u=anc[topx[u]];
	}
	if (dep[u]<dep[v]) swap(u,v);
	lx=dfn[v]; rx=dfn[u];
	update(1);
}
inline int solve_range(int u,int v)
{
	int ret=0;
	while (topx[u]!=topx[v])
	{
		if (dep[topx[u]]<dep[topx[v]]) swap(u,v);
		lx=dfn[topx[u]]; rx=dfn[u]; 
		ret+=query(1); ret%=mo;
		u=anc[topx[u]];
	}
	if (dep[u]<dep[v]) swap(u,v);
	lx=dfn[v]; rx=dfn[u];
	ret+=query(1);
	return ret%mo;
}
inline void upd_subt(int u)
{
	lx=dfn[u]; rx=dfn[u]+tsize[u]-1;
	update(1);
}
inline int solve_subt(int u)
{
	lx=dfn[u]; rx=dfn[u]+tsize[u]-1;
	return query(1)%mo;
}

int main()
{
	readx(nodenum); readx(opt); readx(rootx); readx(mo);
	for (int i=1;i<=nodenum;i++) readx(nodev[i]);
	for (int i=1;i<nodenum;i++) { readx(fx); readx(tx); Insert(); }
	
	Fancy(rootx,1,0); Dreams(rootx,rootx);
	BuildTree(1,tstamp,1);
	
	for (int i=1;i<=opt;i++)
	{
		readx(typ);
		if (typ==1) { readx(ux); readx(vx); readx(val); upd_range(ux,vx); }
		else if (typ==2) { readx(ux); readx(vx); printf("	%d\n",solve_range(ux,vx)); }
		else if (typ==3) { readx(ux); readx(val); upd_subt(ux); }
		else { readx(ux); printf("	%d\n",solve_subt(ux)); }
	}
	return 0;
}
