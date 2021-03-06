// 2021年3月6日22点18分
#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<vector>
typedef long long ll;
using namespace std;

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

// 基于大根堆的 fhq_treap -> 可重集结点合并策略
namespace fhq_treap
{
	#define LCH (t[inx].ch[0])
	#define RCH (t[inx].ch[1])
	
	struct fhq_treap
	{
		int ch[2], siz, fa, val, key;
	}t[1000010];
	int rt,tsiz;
	
	void Update(int inx)
	{
		t[inx].siz=1+t[LCH].siz+t[RCH].siz;
	}
	
	// 拆成 [min, val] 和 [val+1, max]
	void Split(int inx, int val, int &rt1, int &rt2)
	{
		if (!inx) 
		{
			rt1=rt2=0;
			return;
		}
		// 好记的思路：拆哪边就接哪边。要往左拆的，当前点就归[2]，反之亦同
		if (val<t[inx].val)
		{
			Split(LCH, val, rt1, rt2);
			LCH=rt2;
			rt2=inx;
		}
		else
		{
			Split(RCH, val, rt1, rt2);
			RCH=rt1;
			rt1=inx;
		}
		Update(inx);
	}
	
	// 将 rt2（DFS 序意义上）合到 rt1 后面.
	int Merge(int rt1, int rt2)
	{
		if (!(rt1*rt2)) return rt1+rt2;
		if (t[rt1].key >= t[rt2].key)
		{
			t[rt1].ch[1] = Merge(t[rt1].ch[1], rt2);
			Update(rt1);
			return rt1;
		}
		else
		{
			t[rt2].ch[0] = Merge(rt1, t[rt2].ch[0]);
			Update(rt2);
			return rt2;
		}
	}
	
	void Insert(int val)
	{
		int inx = ++tsiz; 
		t[inx].val=val; t[inx].siz=1;
		t[inx].key=rand();
		int rt1, rt2;
		Split(rt, val, rt1, rt2);
		rt = Merge(Merge(rt1, inx), rt2);
	}
	
	void Delete(int val)
	{
		int inx, rt1, rt2, rt3;
		Split(rt, val, rt1, rt2);
		Split(rt1, val-1, rt3, inx);
		inx = Merge(LCH, RCH);
		rt = Merge(Merge(rt3, inx), rt2);
	}
	
	// 求 val 数的 rank
	int Rank(int val)
	{
		int rt1, rt2, ret;
		Split(rt, val-1, rt1, rt2);
		ret = t[rt1].siz+1;
		rt = Merge(rt1, rt2);
		return ret;
	}
	
	// 求 val 数的 ID
	int ID(int inx, int val)
	{
		if (!inx) return -1;
		if (t[inx].val==val) return inx;
		else if (t[inx].val > val) 
			return ID(LCH, val);
		else 
			return ID(RCH, val);
	}
	
	// 求排名为 k 的数的 ID
	int Kth(int inx, int k)
	{
		if (k <= t[LCH].siz) return Kth(LCH, k);
		else if (k == t[LCH].siz+1) return inx;
		else return Kth(RCH, k - 1 - t[LCH].siz);
	}
	
	int Pre(int val)
	{
		int rt1, rt2;
		Split(rt, val-1, rt1, rt2);
		int ret = Kth(rt1, t[rt1].siz);
		rt = Merge(rt1, rt2);
		return ret;
	}
	
	int Suc(int val)
	{
		int rt1, rt2;
		Split(rt, val, rt1, rt2);
		int ret = Kth(rt2, 1);
		rt = Merge(rt1, rt2);
		return ret;
	}
	
	#undef LCH
	#undef RCH
}

int main()
{
	srand(20020420);
	int n, opt, x;
	readx(n);
	int &root = fhq_treap::rt;
	while (n--)
	{
		readx(opt); readx(x);
		if (opt == 1)
		{
			fhq_treap::Insert(x);
		}
		else if (opt == 2)
		{
			fhq_treap::Delete(x);
		}
		else if (opt == 3)
		{
			printf("%d\n", fhq_treap::Rank(x));
		}
		else if (opt == 4)
		{
			printf("%d\n", fhq_treap::t[fhq_treap::Kth(root, x)].val);
		}
		else if (opt == 5)
		{
			printf("%d\n", fhq_treap::t[fhq_treap::Pre(x)].val);
		}
		else 
		{
			printf("%d\n", fhq_treap::t[fhq_treap::Suc(x)].val);
		}
	}
	
	return 0;
}