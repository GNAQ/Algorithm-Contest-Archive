#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cstdlib>
typedef long long ll;
using namespace std;

int n,q;
struct ed
{
	int pre,to;
}edge[200010];
int at=1,ptr[100010];

template<typename int_inp>
void readx(int_inp& x)
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
	// Heavy-Ligit chain decomposition
	#define LCH (inx<<1)
	#define RCH (inx<<1|1)
	
	struct Seg_Tree
	{
		int l,r,mid,val,pos;
	}tree[400010];
	int _pos,_val,lx,rx;
	
	void BuildTree(int inx,int lxx,int rxx)
	{
		tree[inx].l=lxx; tree[inx].r=rxx;
		tree[inx].mid=(lxx+rxx)>>1; tree[inx].pos=2*1e9;
		if (lxx==rxx) return;
		BuildTree(LCH,lxx,tree[inx].mid);
		BuildTree(RCH,tree[inx].mid+1,rxx);
	}
	
	void Upd(int inx)
	{
		if (tree[inx].l==tree[inx].r)
		{
			tree[inx].val=1;
			tree[inx].pos=tree[inx].l;
			return;
		}
		if (_pos<=tree[inx].mid) Upd(LCH);
		else Upd(RCH);
		tree[inx].val=(tree[LCH].val|tree[RCH].val);
		if (tree[inx].val) 
		{
			if (tree[LCH].val) tree[inx].pos=tree[LCH].pos;
			else tree[inx].pos=tree[RCH].pos;
		}
	}

	int Qry(int inx)
	{
		if (tree[inx].l>=lx && tree[inx].r<=rx) return tree[inx].pos;
		int ret=2*1e9;
		if (lx<=tree[inx].mid) ret=min(ret,Qry(LCH));
		if (rx>tree[inx].mid) ret=min(ret,Qry(RCH));
		return ret;
	}
	
	int dep[100010],anc[100010],hson[100010],tsiz[100010];
	int dfn[100010],tst,topx[100010];
	
	void Fancy(int now,int ndep,int fa)
	{
		dep[now]=ndep; anc[now]=fa; tsiz[now]=1;
		for (int v=ptr[now];v;v=edge[v].pre) if (edge[v].to!=fa)
		{
			Fancy(edge[v].to,ndep+1,now);
			tsiz[now]+=tsiz[edge[v].to];
			if (tsiz[hson[now]]<tsiz[edge[v].to]) hson[now]=edge[v].to;
		}
	}
	
	void Dreams(int now,int src)
	{
		dfn[now]=++tst; topx[now]=src;
		if (hson[now]) Dreams(hson[now],src);
		for (int v=ptr[now];v;v=edge[v].pre)
			if (edge[v].to]!=fa && edge[v].to!=hson[now]) Dreams(edge[v].to,edge[v].to);
	}
	
	#undef LCH
	#undef RCH
};

int main()
{
	readx(n); readx(q); int fx,tx;
	for (int i=1;i<n;i++)
	{
		readx(fx); readx(tx);
		Is(fx,tx);
	}
	
	HLD::Fancy(1,1,0); HLD::Dreams(1,1);
	HLD::BuildTree(1,1,n);
	
	
}