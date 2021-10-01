#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<algorithm>
#include<cmath>
#include<cstdlib>
#include<vector>
#include<string>
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

int ai[100010], n, m;
char str[100010];

// 朴素的线段树. 支持区间/单点加/乘, 区间/单点求和, 单点求 max(min).
namespace SGT
{
	struct Seg_Tree
	{
		int l,r;
		int minv, maxv, atag, mtag;
	} t[100010*4];
	
	#define LCH (u<<1)
	#define RCH (u<<1|1)
	
	// 变量说明.
	// lx rx 为查询/修改的左右界
	// vx 为修改的值
	int lx,rx; int vx;
	
	// 下推 u 的标记.
	void Pushdown(int u)
	{
		if (!t[u].atag && t[u].mtag==1) return; // boost
		
		int at=t[u].atag, mt=t[u].mtag;
		t[u].atag=0; t[u].mtag=1;
		
		// 先乘后加
		if (mt!=1)
		{
			t[LCH].mtag*=mt; t[RCH].mtag*=mt;
			t[LCH].atag*=mt; t[RCH].atag*=mt;
			t[LCH].minv*=mt; t[RCH].minv*=mt;
			t[LCH].maxv*=mt; t[RCH].maxv*=mt;
			if (mt<0) 
			{
				swap(t[LCH].maxv, t[LCH].minv);
				swap(t[RCH].maxv, t[RCH].minv);
			}
		}
		if (at)
		{
			t[LCH].atag+=at; t[RCH].atag+=at;
			t[LCH].minv+=(t[LCH].r-t[LCH].l+1)*at;
			t[LCH].maxv+=(t[LCH].r-t[LCH].l+1)*at;
			t[RCH].minv+=(t[RCH].r-t[RCH].l+1)*at;
			t[RCH].maxv+=(t[RCH].r-t[RCH].l+1)*at;
		}
	}
	// 用子树更新 u.
	void Pushup(int u)
	{
		t[u].minv=min(t[LCH].minv, t[RCH].minv);
		t[u].maxv=max(t[LCH].maxv, t[RCH].maxv);
	}
	// L <-> R 建树.
	void BuildTree(int u,int L, int R)
	{
		t[u].l=L; t[u].r=R;
		t[u].mtag=1; // **这个标记要注意**
		if (L==R)
		{
			t[u].atag=0;
			t[u].minv=t[u].maxv=ai[L];
			return;
		}
		int m=(L+R)/2;
		BuildTree(LCH,L,m); BuildTree(RCH,m+1,R);
		Pushup(u);
	}
	// 单点/区间加
	void Upd_Add(int u)
	{
		if (t[u].l>=lx && t[u].r<=rx)
		{
			t[u].minv+=(t[u].r-t[u].l+1)*vx;
			t[u].maxv+=(t[u].r-t[u].l+1)*vx;
			t[u].atag+=vx;
			return;
		}
		Pushdown(u);
		int m=(t[u].l+t[u].r)/2;
		if (lx<=m) Upd_Add(LCH);
		if (rx>m) Upd_Add(RCH);
		Pushup(u);
	}
	// 单点/区间乘
	void Upd_Mul(int u)
	{
		if (t[u].l>=lx && t[u].r<=rx)
		{
			t[u].minv*=vx;
			t[u].maxv*=vx;
			if (vx<0) swap(t[u].minv, t[u].maxv);
			t[u].atag*=vx;
			t[u].mtag*=vx;
			return;
		}
		Pushdown(u);
		int m=(t[u].l+t[u].r)/2;
		if (lx<=m) Upd_Mul(LCH);
		if (rx>m) Upd_Mul(RCH);
		Pushup(u);
	}
	
	int Qry_Pt(int u)
	{
		if (t[u].l==lx && t[u].r==lx)
			return t[u].maxv;
		Pushdown(u);
		int m = (t[u].l+t[u].r)/2, ret;
		if (lx<=m) ret = Qry_Pt(LCH);
		else ret = Qry_Pt(RCH);
		Pushup(u);
		return ret;
	}
	
	// 查询区间/单点最大
	int Qry_Max(int u)
	{
		if (t[u].l>=lx && t[u].r<=rx)
			return t[u].maxv;
		Pushdown(u);
		int m=(t[u].l+t[u].r)/2; int ret=0;
		if (rx<=m) ret=Qry_Max(LCH);
		else if (lx>m) ret=Qry_Max(RCH);
		else ret=std::max(Qry_Max(LCH), Qry_Max(RCH));
		Pushup(u);
		return ret;
	}
	
	// 查询区间/单点最大
	int Qry_Min(int u)
	{
		if (t[u].l>=lx && t[u].r<=rx)
			return t[u].minv;
		Pushdown(u);
		int m=(t[u].l+t[u].r)/2; int ret=0;
		if (rx<=m) ret=Qry_Min(LCH);
		else if (lx>m) ret=Qry_Min(RCH);
		else ret=std::min(Qry_Min(LCH), Qry_Min(RCH));
		Pushup(u);
		return ret;
	}
}

int main()
{
	readx(n); readx(m);
	scanf("%s", str+1);
	for (int i=1;i<=n;i++)
	{
		if (str[i]=='(') ai[i]=1;
		else ai[i]=-1;
	}
	
	for (int i=1;i<=n;i++) ai[i]=ai[i]+ai[i-1];
	
	SGT::BuildTree(1, 1, n);
	
	for (int i=1;i<=m;i++)
	{
		int l, r; readx(l); readx(r);
		if (l>1)
		{
			SGT::lx = l; SGT::rx = r;
			SGT::vx = -1;
			SGT::Upd_Mul(1);
			SGT::lx = l-1;
			SGT::vx = 2 * SGT::Qry_Pt(1);
			SGT::Upd_Add(1);
		}
		if (SGT::t[1].minv>=0)
		{
			SGT::lx = n;
			if (SGT::Qry_Pt(1))
			{
				printf("YES\n");
			}
			else printf("NO\n");
		}
		else
		{
			printf("NO\n");
		}
		
	}
	
	
}