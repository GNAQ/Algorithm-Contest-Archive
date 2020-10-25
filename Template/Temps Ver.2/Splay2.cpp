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

int n,m;

template<typename inp_t>
void readx(inp_t& x)
{
	x=0; int k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

namespace SPL
{
	#define LCH tree[inx].ch[0]
	#define RCH tree[inx].ch[1]
	
	struct Splay_Tree
	{
		int ch[2],fa,rev,val,siz;
	}tree[100010];
	int root,tsiz;
	
	void Upd(int inx)
	{
		tree[inx].siz=1+tree[LCH].siz+tree[RCH].siz;
	}
	void Pushdown(int inx)
	{
		if (!tree[inx].rev) return;
		tree[inx].rev=0; swap(LCH,RCH);
		if (LCH) tree[LCH].rev^=1;
		if (RCH) tree[RCH].rev^=1;
	}
	void Rotate(int inx)
	{
		int f=tree[inx].fa,g=tree[f].fa,dir=(tree[f].ch[1]==inx);
		
		if (g) tree[g].ch[tree[g].ch[1]==f]=inx;
		if (tree[inx].ch[!dir]) tree[tree[inx].ch[!dir]].fa=f;
		tree[f].ch[dir]=tree[inx].ch[!dir]; tree[f].fa=inx;
		tree[inx].fa=g; tree[inx].ch[!dir]=f;
		
		Upd(f); Upd(inx);
	}
	void Splay(int inx,int targ)
	{
		for (;tree[inx].fa!=targ;Rotate(inx))
		{
			int f=tree[inx].fa,g=tree[f].fa;
			Pushdown(g); Pushdown(f); Pushdown(inx);
			if (g!=targ)
			{
				if ( (tree[g].ch[1]==f) == (tree[f].ch[1]==inx) ) Rotate(f);
				else Rotate(inx);
			}
		}
		if (!targ) root=inx;
	}
	
	int BuildTree(int f,int lxx,int rxx)
	{
		int mid=(lxx+rxx)>>1;
		tree[mid].fa=f; 
		if (mid>lxx) tree[mid].ch[0]=BuildTree(mid,lxx,mid-1);
		if (mid<rxx) tree[mid].ch[1]=BuildTree(mid,mid+1,rxx);
		Upd(mid); return mid;
	}
	
	int GetInx(int val)
	{
		int inx=root;
		while (1)
		{
			Pushdown(inx); Upd(inx);
			if (val<=tree[LCH].siz) inx=LCH;
			else
			{
				val-=tree[LCH].siz+1;
				if (!val) return inx;
				inx=RCH;
			}
		}
		return -1;
	}
	
	void Output(int inx)
	{
		Pushdown(inx);
		if (LCH) Output(LCH);
		if (inx>1 && inx<n+2) printf("%d ",inx-1);
		if (RCH) Output(RCH);
	}
	
	#undef LCH
	#undef RCH
};

int main()
{
	using namespace SPL;
	readx(n); readx(m); int lx,rx;
	root=BuildTree(0,1,n+2);

	while (m--)
	{
		readx(lx); readx(rx);
		lx=GetInx(lx); rx=GetInx(rx+2);
		Splay(lx,0); Splay(rx,lx);
		tree[tree[tree[root].ch[1]].ch[0]].rev^=1;
	}
	
	Output(root); putchar('\n');
}