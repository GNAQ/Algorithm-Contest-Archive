#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<iterator>
using namespace std;
typedef long long ll;
typedef ostream_iterator<int> os_iter_int;

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
		int ch[2],fa,siz,w,val;
	}tree[300010];
	int tsiz,root;
	
	void Upd(int inx)
	{
		tree[inx].siz=tree[inx].w+tree[LCH].siz+tree[RCH].siz;
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
			if (g!=targ)
			{
				if ( (tree[g].ch[1]==f) == (tree[f].ch[1]==inx) ) Rotate(f);
				else Rotate(inx);
			}
		}
		if (!targ) root=inx;
	}
	
	int GetRk(int inx,int val)
	{
		if (tree[inx].val==val) { Splay(inx,0); return tree[LCH].siz+1; }
		return GetRk(tree[inx].ch[tree[inx].val<val],val);
	}
	int GetVal(int inx,int val)
	{
		if (tree[LCH].siz<val && tree[inx].w+tree[LCH].siz>=val) 
			{ Splay(inx,0); return tree[inx].val; }
		if (val<=tree[LCH].siz) return GetVal(LCH,val);
		else return GetVal(RCH,val-tree[LCH].siz-tree[inx].w);
	}
	int GetInx(int val)
	{
		int inx=root;
		while (tree[inx].val!=val)
			inx=tree[inx].ch[tree[inx].val<val];
		return inx;
	}
	int PreSuc(int inx,int dir)
	{
		inx=tree[inx].ch[dir];
		while (tree[inx].ch[!dir]) inx=tree[inx].ch[!dir];
		return inx;
	}
	
	void Ins(int& inx,int f,int val)
	{
		if (!inx)
		{
			inx=++tsiz;
			tree[inx].fa=f; tree[inx].val=val;
			tree[inx].w=tree[inx].siz=1;
			Splay(inx,0); return;
		}
		tree[inx].siz++;
		if (tree[inx].val==val) { tree[inx].w++; Splay(inx,0); return; }
		Ins(tree[inx].ch[val>tree[inx].val],inx,val);
	}
	
	void Del(int val)
	{
		int inx=GetInx(val); Splay(inx,0);
		if (tree[inx].w>1) { tree[inx].w--; tree[inx].siz--; return; }
		
		Splay(PreSuc(inx,0),inx);
		root=LCH; tree[LCH].fa=0; 
		tree[LCH].ch[1]=RCH; tree[RCH].fa=LCH;
		Upd(LCH); return;
	}
	
	void Init_Tree()
	{
		tsiz=2; root=1;
		tree[1].w=1; tree[1].siz=2;
		tree[1].val=-2*1e9; tree[1].ch[1]=2; 
		tree[2].fa=1; tree[2].siz=tree[2].w=1;
		tree[2].val=2*1e9;
	}
	
	#undef LCH
	#undef RCH
};

int main()
{
	using namespace SPL;
	Init_Tree();
	int n,opt,val; readx(n);
	while (n--)
	{
		readx(opt); readx(val);
		if (opt==1)
		{
			Ins(root,0,val);
		}
		if (opt==2)
		{
			Del(val);
		}
		if (opt==3)
		{
			printf("%d\n",GetRk(root,val)-1);
		}
		if (opt==4)
		{
			printf("%d\n",GetVal(root,val+1));
		}
		if (opt==5 || opt==6)
		{
			Ins(root,0,val);
			printf("%d\n",tree[PreSuc(root,opt-5)].val);
			Del(val);
		}
	}
}