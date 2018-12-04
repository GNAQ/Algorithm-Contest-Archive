#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#define ll long long
using namespace std;

ll n,m,seq[100010],opt;

template<typename int_t>
void readx(int_t& x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

namespace SGT
{
	struct Seg_Tree
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
			tree[inx].val=seq[lxx];
			return;
		}
		int mid=(lxx+rxx)>>1;
		BuildTree(inx<<1,lxx,mid);
		BuildTree(inx<<1|1,mid+1,rxx);
		tree[inx].val=tree[inx<<1].val+tree[inx<<1|1].val;
	}

	void Pushdown(int inx)
	{
		ll tmp=tree[inx].tag; tree[inx].tag=0;
		tree[inx<<1].tag+=tmp; tree[inx<<1|1].tag+=tmp;
		tree[inx<<1].val+=(tree[inx<<1].r-tree[inx<<1].l+1)*tmp;
		tree[inx<<1|1].val+=(tree[inx<<1|1].r-tree[inx<<1|1].l+1)*tmp;
	}

	void Upd(int inx)
	{
		if (tree[inx].l>=lx && tree[inx].r<=rx)
		{
			tree[inx].val+=Val*(tree[inx].r-tree[inx].l+1);
			tree[inx].tag+=Val;
			return;
		}
		if (tree[inx].tag) Pushdown(inx);
		int mid=(tree[inx].r+tree[inx].l)>>1;
		if (lx<=mid) Upd(inx<<1);
		if (rx>mid) Upd(inx<<1|1);
		tree[inx].val=tree[inx<<1].val+tree[inx<<1|1].val;
	}

	ll Qry(int inx)
	{
		if (tree[inx].l>=lx && tree[inx].r<=rx) return tree[inx].val;
		if (tree[inx].tag) Pushdown(inx);
		int mid=(tree[inx].l+tree[inx].r)>>1; ll ret=0;
		if (lx<=mid) ret+=Qry(inx<<1);
		if (rx>mid) ret+=Qry(inx<<1|1);
		tree[inx].val=tree[inx<<1].val+tree[inx<<1|1].val;
		return ret;
	}
};

int main()
{
	readx(n); readx(m);
	for (int i=1;i<=n;i++) readx(seq[i]);
	SGT::BuildTree(1,1,n);
	for (int i=1;i<=m;i++)
	{
		readx(opt);
		if (opt==1)
		{
			readx(SGT::lx); readx(SGT::rx); readx(SGT::Val);
			SGT::Upd(1);
		}
		else
		{
			readx(SGT::lx); readx(SGT::rx);
			printf("%lld\n",SGT::Qry(1));
		}
	}
}
