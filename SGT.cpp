#include<cstdio>
#include<iostream>
#include<cmath>
#include<cstring>
#include<string>
#include<algorithm>
#include<iterator>
#include<queue>
#include<cstdlib>
#include<vector>
#include<map>
#include<set>
#define ll long long
using namespace std;

struct Seg_Tree
{
	int l,r,mid,val,sum,lmax,rmax,tmax;
}SGT[400010]={0};

struct _Node { int sum,lmax,rmax,tmax; };

void readx(int& x)
{
	x=0; int k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

int max3

void Update_Info(int inx)
{
	SGT[inx].sum=SGT[inx<<1].sum+SGT[inx<<1|1].sum;
	SGT[inx].lmax=max(SGT[inx<<1].sum+SGT[inx<<1|1].lmax,SGT[inx<<1].lmax);
	SGT[inx].rmax=max(SGT[inx<<1].rmax+SGT[inx<<1|1].sum,SGT[inx<<1|1].rmax);
	SGT[inx].tmax=max(SGT[inx<<1].sum+SGT[inx<<1|1].lmax,SGT[inx<<1|1].sum+SGT[inx<<1].rmax
					 ,SGT[inx].sum,SGT[inx<<1].rmax+SGT[inx].lmax,SGT[inx<<1].tmax,SGT[inx<<1|1].tmax);
}

void BuildTree(int inx,int lxx,int rxx)
{
	SGT[inx].l=lxx; SGT[inx].r=rxx;
	if (lxx==rxx)
	{
		SGT[inx].val=seq[lxx];
		SGT[inx].lmax=SGT[inx].rmax=SGT[inx].tmax=seq[lxx];
		return;
	}
	SGT[inx].mid=(lxx+rxx)>>1;
	BuildTree(inx<<1,lxx,SGT[inx].mid);
	BuildTree(inx<<1|1,SGT[inx].mid+1,rxx);
	Update_Info(inx);
}

_Node make_node(Seg_Tree a)
{
	_Node newn;
	newn.sum=a.sum;
	newn.lmax=a.lmax;
	newn.rmax=a.rmax;
	newn.tmax=a.tmax;
	return newn;
}

_Node _Merge(_Node a,_Node b)
{
	_Node c;
	c.lmax=max(a.lmax,a.tmax+b.lmax);
	c.rmax=max(b.rmax,a.rmax+b.tmax);
	c.tmax=max(a.rmax+b.lmax,a.tmax,b.tmax,a.sum+b.lmax,a.rmax+b.sum)
}

_Node qry(int inx)
{
	if (lx<=SGT[inx].l && rx>=SGT[inx].r) return make_node(SGT[inx]);
	
	
}


int main()
{
	
	
	
}
