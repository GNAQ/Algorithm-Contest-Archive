#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<vector>
typedef long long ll;
using namespace std;

const double eps=1e-9;
int n,seq[500010],ans[500010]; double k;
int bac[500010]; // 相等尽量靠后选(的桶)
bool vis[500010];

int tsiz[500010],fa[500010];

template<typename inp_typ>
void readx(inp_typ& x)
{
	x=0; int k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

namespace SGT
{
	#define LCH (inx<<1)
	#define RCH (inx<<1|1)
	
	struct Seg_Tree
	{
		int l,r,mid,tag,minv;
	}tree[2000010];
	int lx,rx,_pos,_val;
	
	void Pushdown(int inx)
	{
		register int tmp=tree[inx].tag; 
		tree[inx].tag=0;
		tree[LCH].tag+=tmp; tree[RCH].tag+=tmp;
		tree[LCH].minv+=tmp; tree[RCH].minv+=tmp;
	}
	
	void BuildTree(int inx,int lxx,int rxx)
	{
		tree[inx].l=lxx; tree[inx].r=rxx;
		tree[inx].mid=(lxx+rxx)>>1;
		if (lxx==rxx)
		{
			tree[inx].minv=lxx;
			return;
		}
		BuildTree(LCH,lxx,tree[inx].mid);
		BuildTree(RCH,tree[inx].mid+1,rxx);
		tree[inx].minv=min(tree[LCH].minv,tree[RCH].minv);
	}
	
	void Upd(int inx)
	{
		if (tree[inx].l>=lx && tree[inx].r<=rx)
		{
			tree[inx].minv+=_val;
			tree[inx].tag+=_val;
			return;
		}
		if (tree[inx].tag) Pushdown(inx);
		if (lx<=tree[inx].mid) Upd(LCH);
		if (rx>tree[inx].mid) Upd(RCH);
		tree[inx].minv=min(tree[LCH].minv,tree[RCH].minv);
	}
	
	int Qry(int inx)
	{
		if (tree[inx].l==tree[inx].r) 
		{
			return (tree[inx].minv>=_pos) ? (tree[inx].l) : (tree[inx].l+1);
		} 
		if (tree[inx].tag) Pushdown(inx);
		int ret;
		if (_pos<=tree[RCH].minv) ret=Qry(LCH);
		else ret=Qry(RCH); // 尽量选大数
		tree[inx].minv=min(tree[LCH].minv,tree[RCH].minv);
		return ret;
	}
	
	#undef LCH
	#undef RCH
};

void BuildTree()
{
    for (int i=1;i<=n;i++) { fa[i]=(int)floor(i/k+eps); tsiz[i]=1; }
	for (int i=n;i;i--) tsiz[fa[i]]+=tsiz[i];
}

int main()
{
    readx(n); scanf("%lf",&k); 
    for (int i=1;i<=n;i++) readx(seq[i]);
    BuildTree();
	
	sort(seq+1,seq+n+1,greater<int>());
	for (int i=n;i;i--) 
		bac[i]=(seq[i]==seq[i+1]) ? (bac[i+1]+1) : 0;

	SGT::BuildTree(1,1,n);
	for (int i=1;i<=n;i++) // enumerate nodes
	{
		if (fa[i] && !vis[fa[i]]) 
		{
			SGT::lx=ans[fa[i]]; SGT::rx=n; SGT::_val=tsiz[fa[i]]-1; 
			SGT::Upd(1); vis[fa[i]]=1;
		}
		SGT::_pos=tsiz[i]; int tmp=SGT::Qry(1);
		
		tmp+=bac[tmp]; bac[tmp]++; tmp-=bac[tmp]-1;
		ans[i]=tmp;
		// 毒瘤实现逻辑 先移到末尾再看看用了多少
		
		SGT::lx=ans[i]; SGT::rx=n; SGT::_val=-1*tsiz[i];
		SGT::Upd(1);
	}
	for (int i=1;i<=n;i++) printf("%d%c",seq[ans[i]]," \n"[i==n]);
	
}

/*
 * solution sketch
 * 直接扩展贪心的 60 做法
 * 考虑让答案更优的策略是对换同代的结点和儿子结点, 可能会让答案变优
 * 因为很显然的是同代结点 i 的 index 是小于儿子的。
 * 所以考虑线段树维护目前可用的所有数字 (按从大到小排序)
 * 显然线段树的权值随 index 递增
 * 主要思想就是把 "在左侧取子树大小个" 换成 "选定权值以及右边的每个权值的前驱个数都 -1"
 * 顺次枚举每个结点，在线段树上二分选最大的满足条件的点
 * 然后考虑如果有相同的话，选末尾(最靠后)那个
 * 之后直接改一下所有后继的权值
 * 注意如果从父亲跳到儿子, 要还原父亲为了留给儿子的可选结点(注意只要还原一次)
 * 然后线段树上二分的时候卡人 毒瘤
 */