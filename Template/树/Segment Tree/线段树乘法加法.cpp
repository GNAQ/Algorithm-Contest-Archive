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

struct segment_tree { ll l,r,w,taga,tagm; } SGT[400010]={0};
ll lx,rx,val;

ll n,seq[100010]={0},mo,opt,typ;

inline void readx(ll& x)
{
	x=0; ll k=1; register char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

inline void BuildTree(ll lxx,ll rxx,ll inx)
{
	SGT[inx].l=lxx; SGT[inx].r=rxx; SGT[inx].tagm=1;
	if (lxx==rxx) { SGT[inx].w=seq[lxx]%mo; return; }
	ll mid=(lxx+rxx)>>1;
	BuildTree(lxx,mid,inx<<1);
	BuildTree(mid+1,rxx,inx<<1|1);
	SGT[inx].w=(SGT[inx<<1].w+SGT[inx<<1|1].w)%mo;
}
inline void pushdown(ll inx)
{
	if (SGT[inx].tagm!=1)
	{
		SGT[inx<<1].taga*=SGT[inx].tagm;
		SGT[inx<<1|1].taga*=SGT[inx].tagm;
		SGT[inx<<1].tagm*=SGT[inx].tagm;
		SGT[inx<<1|1].tagm*=SGT[inx].tagm;
		SGT[inx<<1].w*=SGT[inx].tagm;
		SGT[inx<<1|1].w*=SGT[inx].tagm;
		
		SGT[inx<<1].taga%=mo;
		SGT[inx<<1].tagm%=mo;
		SGT[inx<<1].w%=mo;
		SGT[inx<<1|1].taga%=mo;
		SGT[inx<<1|1].tagm%=mo;
		SGT[inx<<1|1].w%=mo;
		SGT[inx].tagm=1;
	}
	if (SGT[inx].taga)
	{
		SGT[inx<<1].taga+=SGT[inx].taga;
		SGT[inx<<1|1].taga+=SGT[inx].taga;
		SGT[inx<<1].w+=(SGT[inx<<1].r-SGT[inx<<1].l+1)*SGT[inx].taga;
		SGT[inx<<1|1].w+=(SGT[inx<<1|1].r-SGT[inx<<1|1].l+1)*SGT[inx].taga;
		
		SGT[inx<<1].taga%=mo;
		SGT[inx<<1].w%=mo;
		SGT[inx<<1|1].taga%=mo;
		SGT[inx<<1|1].w%=mo;
		SGT[inx].taga=0;
	}
}
inline void updatea(ll inx)
{
	if (SGT[inx].l>=lx && SGT[inx].r<=rx)
	{
		SGT[inx].w+=((SGT[inx].r-SGT[inx].l+1)*val)%mo; SGT[inx].w%=mo;
		SGT[inx].taga+=val%mo; SGT[inx].taga%=mo; return;
	}
	pushdown(inx);
	ll mid=(SGT[inx].r+SGT[inx].l)>>1;
	if (lx<=mid) updatea(inx<<1);
	if (rx>mid) updatea(inx<<1|1);
	SGT[inx].w=(SGT[inx<<1].w+SGT[inx<<1|1].w)%mo;
}
inline void updatem(int inx)
{
	if (SGT[inx].l>=lx && SGT[inx].r<=rx)
	{
		SGT[inx].w*=val%mo; SGT[inx].w%=mo;
		SGT[inx].taga*=val%mo; SGT[inx].taga%=mo;
		SGT[inx].tagm*=val%mo; SGT[inx].tagm%=mo; return;
	}
	pushdown(inx);
	ll mid=(SGT[inx].l+SGT[inx].r)>>1;
	if (lx<=mid) updatem(inx<<1);
	if (rx>mid) updatem(inx<<1|1);
	SGT[inx].w=(SGT[inx<<1].w+SGT[inx<<1|1].w)%mo;
}

inline ll query(int inx)
{
	if (SGT[inx].l>=lx && SGT[inx].r<=rx) return SGT[inx].w;
	pushdown(inx);
	ll mid=(SGT[inx].l+SGT[inx].r)>>1,ret=0;
	if (lx<=mid) ret+=query(inx<<1);
	if (rx>mid) ret=(ret+query(inx<<1|1))%mo;
	SGT[inx].w=(SGT[inx<<1].w+SGT[inx<<1|1].w)%mo;
	return ret%mo;
}

int main()
{
	readx(n); readx(opt); readx(mo);
	for (int i=1;i<=n;i++) readx(seq[i]);
	BuildTree(1,n,1);
	for (int i=1;i<=opt;i++)
	{
		readx(typ);
		if (typ==1)
		{
			readx(lx); readx(rx); readx(val);
			updatem(1);
		}
		else if (typ==2)
		{
			readx(lx); readx(rx); readx(val);
			updatea(1);
		}
		else
		{
			readx(lx); readx(rx);
			printf("%lld\n",query(1));
		}
	}
	return 0;
}
