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

int n,seq[100010],m,opt;

template<typename int_t>
void readx(int_t& x)
{
    x=0; int_t k=1; char ch=0;
    while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
    while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
    x*=k;
}

namespace Treap
{
    #define LCH tree[inx].ch[0]
    #define RCH tree[inx].ch[1]
    
    struct Treap_Tree
    {
        int ch[2],fa,val,w,siz,key;
    }tree[100010];
    int tsiz,rot;
    
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
    
    void Ins(int& inx,int val)
    {
        if (!inx) 
        {
            inx=++tsiz;
            tree[inx].w=tree[inx].siz=1;
            tree[inx].key=rand(); tree[inx].val=val;
            return;
        }
        tree[inx].siz++;
        if (tree[inx].val==val) { tree[inx].w++; return; }
        bool flag=(tree[inx].val<val);
        Ins(tree[inx].ch[flag],val);
        if (tree[inx].key<tree[tree[inx].ch[flag]].key) Rotate(inx,!flag);
    }
    
    void Del(int& inx,int val)
    {
        if (!inx) return;
        tree[inx].siz--;
        if (tree[inx].val==val)
        {
            if (tree[inx].w>1) { tree[inx].w--; return; }
            if (!(LCH*RCH)) { inx=LCH+RCH; return; }
			bool flag=(tree[LCH].key>tree[RCH].key);
			Rotate(inx,flag); Del(inx,val);
        }
		else Del(tree[inx].ch[tree[inx].val<val],val);
	}
	
	int Pre(int inx,int val)
	{
		if (!inx) return -2*1e9;
		if (tree[inx].val>=val) return Pre(LCH,val);
		return max(tree[inx].val,Pre(RCH,val));
	}
	
	int Suc(int inx,int val)
	{
		if (!inx) return 2*1e9;
		if (tree[inx].val<=val) return Suc(RCH,val);
		return min(tree[inx].val,Suc(LCH,val));
	}
	
	int Rank(int inx,int val)
	{
		if (!inx) return 0;
		if (tree[inx].val==val) return (tree[LCH].siz+1);
		if (tree[inx].val>val) return Rank(LCH,val);
		return Rank(RCH,val)+tree[LCH].siz+tree[inx].w;
	}
	
	int Inx(int inx,int val)
	{
		if (val<=tree[LCH].siz) return Inx(LCH,val);
		if (val>tree[LCH].siz+tree[inx].w) return Inx(RCH,val-tree[LCH].siz-tree[inx].w);
		return tree[inx].val;
	}
	
	#undef LCH 
	#undef RCH
}

int main()
{
	srand(20020420);
	readx(n); Treap::rot=0;
	for (int i=1;i<=n;i++)
	{
		readx(opt);
		switch(opt)
		{
			case 1:
				readx(m); Treap::Ins(Treap::rot,m);
				break;
			case 2:
				readx(m); Treap::Del(Treap::rot,m);
				break;
			case 3:
				readx(m); printf("%d\n",Treap::Rank(Treap::rot,m));
				break;
			case 4:
				readx(m); printf("%d\n",Treap::Inx(Treap::rot,m));
				break;
			case 5:
				readx(m);
				printf("%d\n",Treap::Pre(Treap::rot,m));
				break;
			case 6:
				readx(m);
				printf("%d\n",Treap::Suc(Treap::rot,m));
				break;
		}
	}
	return 0;
}
