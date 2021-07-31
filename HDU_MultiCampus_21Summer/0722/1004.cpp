#pragma GCC optimize(3)
#include<cstdio>
#include<iostream>
#include<string>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<vector>
typedef long long ll;
using namespace std;

int n, ci[100010], q;
struct Ask
{
	int l, r, a, b, id, ans;
}asks[100010];
int blk[100010];

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

namespace DS
{
	#define LCH (t[u].ch[0])
	#define RCH (t[u].ch[1])
	
	struct Trie_Node
	{
		int ch[2], val, siz;
	}t[100010*22];
	int tsiz;
	
	void Ins(int u, int dep, int val, int w)
	{
		if (dep==-1) 
		{
			t[u].siz+=w;
			if (t[u].siz==w) t[u].val=1;
			if (t[u].siz==0) t[u].val=0;
			return;
		}
		bool dir = (val>>dep)&1;
		
		if (!t[u].ch[dir]) t[u].ch[dir]=++tsiz;
		Ins(t[u].ch[dir], dep-1, val, w);
		
		if (LCH*RCH==0)
		{
			t[u].val=t[LCH+RCH].val;
		}
		else
		{
			t[u].val=t[LCH].val+t[RCH].val;
		}
	}
	
	int Qry(int u, int dep, int val, int w) // w is B
	{
		if (u==0) return 0;
		if (dep==-1)
		{
			return t[u].val;
		}
		bool vf = (val>>dep)&1, wf = (w>>dep)&1;
		
		if (wf)
		{
			if (vf==1) 
				return Qry(t[u].ch[0], dep-1, val, w) + t[t[u].ch[1]].val;
			else 
				return Qry(t[u].ch[1], dep-1, val, w) + t[t[u].ch[0]].val;
		}
		else
		{
			if (vf==1) 
				return Qry(t[u].ch[1], dep-1, val, w);
			else 
				return Qry(t[u].ch[0], dep-1, val, w);
		}
	}
	
	#undef LCH
	#undef RCH
}

bool cmp2(const Ask &a, const Ask &b)
{
	return a.id < b.id;
}

bool cmp1(const Ask &a, const Ask &b)
{
	if (blk[a.l]==blk[b.l])
	{
		if (blk[a.l]&1) return a.r<b.r;
		else return a.r>b.r;
	}
	return blk[a.l]<blk[b.l];
}

int main()
{
	readx(n); DS::tsiz = 1;
	for (int i=1;i<=n;i++) readx(ci[i]);
	readx(q);
	for (int i=1;i<=q;i++)
	{
		readx(asks[i].l); readx(asks[i].r);
		readx(asks[i].a); readx(asks[i].b);
		asks[i].id = i;
	}
	
	int blksiz = n / sqrt(q*2/3);
	for (int i=1;i<=n;i++) 
		blk[i] = 1 + i/blksiz;
	
	sort(asks+1, asks+q+1, cmp1);
	
	int pl, pr;
	
	pl=asks[1].l; pr = asks[1].l-1;
	for (int i=1;i<=q;i++)
	{
		while (pr < asks[i].r)
		{
			pr++;
			DS::Ins(1, 17, ci[pr], 1);
		}
		while (pr > asks[i].r)
		{
			DS::Ins(1, 17, ci[pr], -1);
			pr--;
		}
		while (pl > asks[i].l)
		{
			pl--;
			DS::Ins(1, 17, ci[pl], 1);
		}
		while (pl < asks[i].l)
		{
			DS::Ins(1, 17, ci[pl], -1);
			pl++;
		}
		asks[i].ans = DS::Qry(1, 17, asks[i].a, asks[i].b);
	}
	
	sort(asks+1, asks+q+1, cmp2);
	
	for (int i=1;i<=q;i++) printf("%d\n", asks[i].ans);
	return 0;
}