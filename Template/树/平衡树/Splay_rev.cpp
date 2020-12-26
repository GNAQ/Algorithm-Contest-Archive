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

struct splay_t { int rev,fa,ch[2],siz; } t[100010]={0};
int tsiz,troo;

int n,opt,lx,rx;

inline void readx(int& x)
{
	x=0; int k=1; register char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}
inline void updata(int pos) { t[pos].siz=t[t[pos].ch[0]].siz+t[t[pos].ch[1]].siz+1; }
inline void pushdown(int pos)
{
	if (!t[pos].rev) return;
	t[t[pos].ch[0]].rev^=1; t[t[pos].ch[1]].rev^=1;
	swap(t[pos].ch[0],t[pos].ch[1]); t[pos].rev=0;
}
inline void rotatex(int pos)
{
	int f=t[pos].fa,g=t[f].fa,flag=(t[f].ch[1]==pos),flag2=(t[g].ch[1]==f);

	t[f].ch[flag]=t[pos].ch[!flag]; t[f].fa=pos;
	if (t[pos].ch[!flag]) t[t[pos].ch[!flag]].fa=f;
	t[pos].fa=g; t[pos].ch[!flag]=f;
	if (g) t[g].ch[flag2]=pos;
	
	updata(f); updata(pos);
}
inline void splay(int pos,int targ)
{
	for (;t[pos].fa!=targ;rotatex(pos))
	{
		pushdown(t[t[pos].fa].fa); pushdown(t[pos].fa); pushdown(pos);
		if (t[t[pos].fa].fa!=targ)
		{
			int g=t[t[pos].fa].fa;
			if ((t[g].ch[1]==t[pos].fa)==(t[t[pos].fa].ch[1]==pos)) rotatex(t[pos].fa);
			else rotatex(pos);
		}
	}
	if (!targ) troo=pos;
}

inline int Buildt(int lxx,int rxx,int f)
{
	int mid=(lxx+rxx)>>1;
	t[mid].fa=f;
	if (mid>lxx) t[mid].ch[0]=Buildt(lxx,mid-1,mid);
	if (mid<rxx) t[mid].ch[1]=Buildt(mid+1,rxx,mid);
	updata(mid); return mid;
}

inline int splay_get_pos(int val)
{
	int pos=troo;
	while (1)
	{
		pushdown(pos); updata(pos);
		if (val<=t[t[pos].ch[0]].siz) pos=t[pos].ch[0];
		else
		{
			val-=t[t[pos].ch[0]].siz+1;
			if (!val) return pos;
			pos=t[pos].ch[1];
		}
	}
}

inline void output(int pos)
{
	pushdown(pos);
	if (t[pos].ch[0]) output(t[pos].ch[0]);
	if (pos>1 && pos<n+2) printf("%d ",pos-1);
	if (t[pos].ch[1]) output(t[pos].ch[1]);
}


int main()
{
	readx(n); readx(opt);
	troo=Buildt(1,n+2,0);
	for (int i=1;i<=opt;i++)
	{
		readx(lx); readx(rx);
		lx=splay_get_pos(lx); rx=splay_get_pos(rx+2);
		splay(lx,0); splay(rx,lx);
		t[t[t[troo].ch[1]].ch[0]].rev^=1;
	}
	output(troo);
	return 0;
}
