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
#include<queue>
#include<vector>
using namespace std;
typedef long long ll;

int n,m,nodev[300010];

template<typename inp_t>
void readx(inp_t& x)
{
	x=0; int k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

namespace LCT
{
	#define LCH tree[inx].ch[0]
	#define RCH tree[inx].ch[1]
	
	struct Splay_tree
	{
		int ch[2],fa,val,rev;
	}tree[300010];
	
	void Upd(int inx)
	{
		tree[inx].val=tree[LCH].val^tree[RCH].val^nodev[inx];
	}
	void PutRev(int inx)
	{
		swap(LCH,RCH);
		if (LCH) tree[LCH].rev^=1;
		if (RCH) tree[RCH].rev^=1;
	}
	void PushRev(int inx)
	{
		if (!tree[inx].rev) return;
		tree[inx].rev=0; PutRev(inx);
	}
	bool NotRoot(int inx)
	{
		return (tree[tree[inx].fa].ch[0]==inx) || (tree[tree[inx].fa].ch[1]==inx);
	}
	void AllPushdown(int inx)
	{
		if (NotRoot(inx)) AllPushdown(tree[inx].fa);
		PushRev(inx);
	}
	
	void Rotate(int inx)
	{
		int f=tree[inx].fa,g=tree[f].fa,dir=(tree[f].ch[1]==inx);
		
		if (NotRoot(f)) tree[g].ch[tree[g].ch[1]==f]=inx;
		if (tree[inx].ch[!dir]) tree[tree[inx].ch[!dir]].fa=f;
		tree[f].ch[dir]=tree[inx].ch[!dir]; tree[f].fa=inx;
		tree[inx].fa=g; tree[inx].ch[!dir]=f;
		
		Upd(f); Upd(inx);
	}
	void Splay(int inx)
	{
		AllPushdown(inx);
		for (;NotRoot(inx);Rotate(inx))
		{
			int f=tree[inx].fa,g=tree[f].fa;
			if (NotRoot(f))
			{
				if ( (tree[g].ch[1]==f) == (tree[f].ch[1]==inx) ) Rotate(f);
				else Rotate(inx);
			}
		}
	}
	
	void Access(int inx)
	{
		for (int ch=0;inx;inx=tree[inx].fa)
		{
			Splay(inx); RCH=ch;
			ch=inx; Upd(inx);
		}
	}
	void MakeRoot(int inx)
	{
		Access(inx); 
		Splay(inx); PutRev(inx);
	}
	int FindRoot(int inx)
	{
		Access(inx); Splay(inx); PushRev(inx);
		while (LCH) { inx=LCH; PushRev(inx); }
		Splay(inx); return inx;
	}
	void Connect(int u,int v)
	{
		MakeRoot(u);
		Access(v); Splay(v);
	}
	int Link(int u,int v)
	{
		MakeRoot(u);
		if (FindRoot(v)==u) return -1;
		tree[u].fa=v; return 1;
	}
	int Cut(int u,int v)
	{
		MakeRoot(u);
		if (FindRoot(v)==u && tree[v].fa==u && (!tree[v].ch[0]))
		{
			tree[u].ch[1]=tree[v].fa=0;
			Upd(u); return 1;
		}
		return -1;
	}
	
	#undef LCH
	#undef RCH
};

int main()
{
	readx(n); readx(m);
	for (int i=1;i<=n;i++) readx(nodev[i]);
	
	while (m--)
	{
		int opt,u,v;
		readx(opt); readx(u); readx(v);
		if (opt==0)
		{
			LCT::Connect(u,v);
			printf("%d\n",LCT::tree[v].val);
		}
		if (opt==1)
		{
			LCT::Link(u,v);
		}
		if (opt==2)
		{
			LCT::Cut(u,v);
		}
		if (opt==3)
		{
			LCT::Splay(u); 
			nodev[u]=v; LCT::Upd(u);
		}
	}
}