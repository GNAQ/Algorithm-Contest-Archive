#include<cstdio>
#include<iostream>
#include<string>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<iterator>
#include<cstdlib>
#include<queue>
#include<vector>
using namespace std;

struct splay_tree { int rev,fa,ch[2],siz; } tree[100010]={0};
int tsiz,troo;

int n,opt,lx,rx;

inline void readx(int& x)
{
	x=0; int k=1; register char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}
inline void updata(int pos) { tree[pos].siz=tree[tree[pos].ch[0]].siz+tree[tree[pos].ch[1]].siz+1; }
inline void pushdown(int pos)
{
	if (!tree[pos].rev) return;
	tree[tree[pos].ch[0]].rev^=1; tree[tree[pos].ch[1]].rev^=1;
	swap(tree[pos].ch[0],tree[pos].ch[1]); tree[pos].rev=0;
}
inline void rotatex(int pos)
{
	int f=tree[pos].fa,g=tree[f].fa,flag=(tree[f].ch[1]==pos),flag2=(tree[g].ch[1]==f);

	tree[f].ch[flag]=tree[pos].ch[!flag]; tree[f].fa=pos;
	if (tree[pos].ch[!flag]) tree[tree[pos].ch[!flag]].fa=f;
	tree[pos].fa=g; tree[pos].ch[!flag]=f;
	if (g) tree[g].ch[flag2]=pos;
	
	updata(f); updata(pos);
}
inline void splay(int pos,int targ)
{
	for (;tree[pos].fa!=targ;rotatex(pos))
	{
		pushdown(tree[tree[pos].fa].fa); pushdown(tree[pos].fa); pushdown(pos);
		if (tree[tree[pos].fa].fa!=targ)
		{
			int g=tree[tree[pos].fa].fa;
			if ((tree[g].ch[1]==tree[pos].fa)==(tree[tree[pos].fa].ch[1]==pos)) rotatex(tree[pos].fa);
			else rotatex(pos);
		}
	}
	if (!targ) troo=pos;
}

inline int BuildTree(int lxx,int rxx,int f)
{
	int mid=(lxx+rxx)>>1;
	tree[mid].fa=f;
	if (mid>lxx) tree[mid].ch[0]=BuildTree(lxx,mid-1,mid);
	if (mid<rxx) tree[mid].ch[1]=BuildTree(mid+1,rxx,mid);
	updata(mid); return mid;
}

inline int splay_get_pos(int val)
{
	int pos=troo;
	while (1)
	{
		pushdown(pos); updata(pos);
		if (val<=tree[tree[pos].ch[0]].siz)	pos=tree[pos].ch[0];
		else
		{
			val-=tree[tree[pos].ch[0]].siz+1;
			if (!val) return pos;
			pos=tree[pos].ch[1];
		}
	}
}

inline void output(int pos)
{
	pushdown(pos);
	if (tree[pos].ch[0]) output(tree[pos].ch[0]);
	if (pos>1 && pos<n+2) printf("%d ",pos-1);
	if (tree[pos].ch[1]) output(tree[pos].ch[1]);
}


int main()
{
	readx(n); readx(opt);
	troo=BuildTree(1,n+2,0);
	for (int i=1;i<=opt;i++)
	{
		readx(lx); readx(rx);
		lx=splay_get_pos(lx); rx=splay_get_pos(rx+2);
		splay(lx,0); splay(rx,lx);
		tree[tree[tree[troo].ch[1]].ch[0]].rev^=1;
	}
	output(troo);
	return 0;
}
