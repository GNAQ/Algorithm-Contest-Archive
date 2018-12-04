#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<iterator>
#include<cstdlib>
#include<vector>
#include<queue>
#include<map>
#include<set>
#define ll long long
using namespace std;

int n,m,q,seq[500010];
char opt;

template<typename int_t>
void readx(int_t& x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

namespace DS
{
	int fa[500010];
	
	void Init(int siz)
	{
		for (int i=1;i<=siz;i++) fa[i]=i;
	}
	
	int Find(int e)
	{
		if (e!=fa[e]) fa[e]=Find(fa[e]);
		return fa[e];
	}
	
	void Merge(int a,int b)
	{
		fa[Find(a)]=Find(b);
	}
};

namespace Treap
{
	#define LCH tree[inx].ch[0]
	#define RCH tree[inx].ch[1]
	
	struct Treap_Tree
	{
		int val,key,ch[2],fa,siz,w,cod;
	}tree[500010];
	int rots[500010],tsiz,ans;
	
	void Update(int inx)
	{
		tree[inx].siz=tree[inx].w+tree[LCH].siz+tree[RCH].siz;
	}
	
	void Rotate(int& inx,int dir)
	{
		int chs=tree[inx].ch[!dir];
		tree[inx].ch[!dir]=tree[chs].ch[dir];
		tree[chs].ch[dir]=inx;
		Update(inx); Update(inx=chs);
	}
	
	void Ins(int& inx,int val,int cod)
	{
		if (!inx)
		{
			inx=++tsiz; ans++;
			tree[inx].siz=tree[inx].w=1;
			tree[inx].val=val; tree[inx].cod=cod; tree[inx].key=rand();
			return;
		}
		tree[inx].siz++;
		if (tree[inx].val==val) { tree[inx].w++; return; }
		bool dir=(tree[inx].val<val);
		Ins(tree[inx].ch[dir],val,cod);
		if (tree[inx].key<tree[tree[inx].ch[dir]].key) Rotate(inx,!dir);
	}
	
	void Del(int& inx,int val)
	{
		if (!inx) return;
		tree[inx].siz--;
		if (tree[inx].val==val)
		{
			if (tree[inx].w>1) { tree[inx].w--; return; }
			if (!(LCH*RCH)) { inx=LCH+RCH; return; }
			bool dir=(tree[LCH].key>tree[RCH].key);
			Rotate(inx,dir); Del(inx,val);
		}
		else Del(tree[inx].ch[tree[inx].val<val],val);
	}
	
	int Rank(int inx,int val)
	{
		if (!inx) return -1;
		if (val<=tree[LCH].siz) return Rank(LCH,val);
		if (val>tree[LCH].siz+tree[inx].w) return Rank(RCH,val-tree[LCH].siz-tree[inx].w);
		return tree[inx].cod;
	}
	
	void Isp_Merge(int& inx,int& targ)
	{
		if (LCH) Isp_Merge(LCH,targ);
		if (RCH) Isp_Merge(RCH,targ);
		Ins(targ,tree[inx].val,tree[inx].cod);
		Del(inx,tree[inx].val);
	}
};

int main()
{
	srand(20020420);
	readx(n); readx(m); int fx,tx,tmp,k; DS::Init(n);
	for (int i=1;i<=n;i++) readx(seq[i]);
	for (int i=1;i<=n;i++) Treap::Ins(Treap::rots[i],seq[i],i);
	
	for (int i=1;i<=m;i++)
	{
		readx(fx); readx(tx); fx=DS::Find(fx); tx=DS::Find(tx);
		if (Treap::tree[Treap::rots[fx]].siz>Treap::tree[Treap::rots[tx]].siz) 
				swap(fx,tx);
		
		DS::Merge(fx,tx);
		Treap::Isp_Merge(Treap::rots[fx],Treap::rots[tx]);
	}
	
	readx(q);
	for (int i=1;i<=q;i++)
	{
		opt=0; while (opt<'A' || opt>'Z') opt=getchar();
		if (opt=='B')
		{
			readx(fx); readx(tx); fx=DS::Find(fx); tx=DS::Find(tx);
			if (fx==tx) continue;
			if (Treap::tree[Treap::rots[fx]].siz>Treap::tree[Treap::rots[tx]].siz) 
				swap(fx,tx);
			
			DS::Merge(fx,tx);
			Treap::Isp_Merge(Treap::rots[fx],Treap::rots[tx]);
		}
		if (opt=='Q')
		{
			readx(tmp); readx(k); tmp=DS::Find(tmp); 
			printf("%d\n",Treap::Rank(Treap::rots[tmp],k));
		}
	}
}
