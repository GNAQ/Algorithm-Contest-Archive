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
#define ll long long
using namespace std;

struct Segment_tree { ll l,r,w,tag; } SGT[400010]={0};
ll n,seq[100010]={0},opt,typ,lx,rx,val;

inline void readx(ll& x)
{
	x=0; ll k=1; register char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

inline void BuildTree(ll lxx,ll rxx,ll inx)
{
	SGT[inx].l=lxx; SGT[inx].r=rxx;
	if (lxx==rxx) { SGT[inx].w=seq[lxx]; return; }
	ll mid=(lxx+rxx)>>1;
	BuildTree(lxx,mid,inx<<1);
	BuildTree(mid+1,rxx,inx<<1|1);
	SGT[inx].w=(SGT[inx<<1].w+SGT[inx<<1|1].w);
}
inline void pushdown(int inx)
{
	SGT[inx<<1].tag+=SGT[inx].tag;
	SGT[inx<<1|1].tag+=SGT[inx].tag;
	SGT[inx<<1].w+=(SGT[inx<<1].r-SGT[inx<<1].l+1)*SGT[inx].tag;
	SGT[inx<<1|1].w+=(SGT[inx<<1|1].r-SGT[inx<<1|1].l+1)*SGT[inx].tag;
	SGT[inx].tag=0;
}
inline void update(int inx)
{
	if (SGT[inx].l>=lx && SGT[inx].r<=rx)
	{
		SGT[inx].w+=(SGT[inx].r-SGT[inx].l+1)*val; SGT[inx].tag+=val;
		return;
	}
	if (SGT[inx].tag) pushdown(inx);
	ll mid=(SGT[inx].l+SGT[inx].r)>>1;
	if (lx<=mid) update(inx<<1);
	if (rx>mid) update(inx<<1|1);
	SGT[inx].w=(SGT[inx<<1].w+SGT[inx<<1|1].w);
}
inline ll query(int inx)
{
	if (SGT[inx].l>=lx && SGT[inx].r<=rx) return SGT[inx].w;
	if (SGT[inx].tag) pushdown(inx);
	ll mid=(SGT[inx].l+SGT[inx].r)>>1,ret=0;
	if (lx<=mid) ret+=query(inx<<1);
	if (rx>mid) ret+=query(inx<<1|1);
	SGT[inx].w=(SGT[inx<<1].w+SGT[inx<<1|1].w);
	return ret;
}

int main()
{
	readx(n); readx(opt);
	for (int i=1;i<=n;i++) readx(seq[i]);
	BuildTree(1,n,1);
	for (int i=1;i<=opt;i++)
	{
		readx(typ);
		if (typ==1)
		{
			readx(lx); readx(rx); readx(val);
			update(1);
		}
		else
		{
			readx(lx); readx(rx);
			printf("%lld\n",query(1));
		}
	}
	return 0;
}
