#include<cstdio>
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<string>
#include<algorithm>
typedef long long ll;

// 普通并查集+路径压缩
namespace DSU
{
	int dsu[100010];
	
	// 初始化并查集. mode: 0=清空 1=指向自己
	void Init(int st, int ed, int mode)
	{
		for (int i=st;i<=ed;i++)
			dsu[i] = ( (mode==0) ? 0 : i );
	}
	// 查询集合 id 并做路径压缩.
	int Find(int u)
	{
		if (u!=dsu[u]) dsu[u]=Find(dsu[u]);
		return dsu[u];
	}
	// 合并 a <- b.
	void Merge(int a,int b)
	{
		dsu[Find(b)]=Find(a);
	}
}

// 按秩合并 (aka 启发式合并)
namespace DSU2
{
	struct Dsu_node
	{
		int fa,siz;
	} dsu[100010];
	
	// 初始化并查集. mode: 0=清空 1=指向自己
	void Init(int st, int ed, int mode)
	{
		for (int i=st;i<=ed;i++)
		{
			dsu[i].fa = ( (mode==0) ? 0 : i );
			dsu[i].siz = (mode!=0);
		}
	}
	// 查询集合 id.
	int Find(int u)
	{
		while (dsu[u].fa!=u)
			u=dsu[u].fa;
		return u;
	}
	// 按秩合并 a 和 b, 若秩相同则 a <- b.
	void Merge(int a,int b)
	{
		int afa=Find(a), bfa=Find(b);
		if (dsu[afa].siz<dsu[bfa].siz) std::swap(afa,bfa);
		dsu[afa].siz+=dsu[bfa].siz;
		dsu[bfa].fa=afa;
	}
} 

// 带删除并查集
namespace DSU3
{
	struct Dsu_node
	{
		int fa,siz,me;
	} dsu[100010];
	int id[100010], cnt; // id[i]=0 表示不存在 || cnt 是 dsu 计数器
	
	// 初始化并查集. mode: 0=清空 1=指向自己
	void Init(int st, int ed, int mode)
	{
		cnt=ed;
		for (int i=st;i<=ed;i++)
		{
			dsu[i].fa = dsu[i].me = ( (mode==0) ? 0 : i );
			dsu[i].siz = (mode!=0);
		}
		if (mode)
			for (int i=st;i<=ed;i++) id[i]=i;
	}
	// 查询集合 id.
	int Find(int u)
	{
		while (dsu[u].fa!=dsu[u].me)
			u=dsu[u].fa;
		return u;
	}
	// 按秩合并 a 和 b, 若秩相同则 a <- b.
	void Merge(int a,int b)
	{
		int afa=Find(a), bfa=Find(b);
		if (dsu[afa].siz<dsu[bfa].siz) std::swap(afa,bfa);
		dsu[afa].siz+=dsu[bfa].siz;
		dsu[bfa].fa=afa;
	}
	// 从集合中抠出 u (1) 或不可恢复地删除 u (-1).
	void Escape(int u, int mode)
	{
		if (mode==-1) id[u]=0;
		else
		{
			cnt++;
			dsu[cnt].fa=dsu[cnt].me=u;
			dsu[cnt].siz=1;
			id[u]=cnt;
		}
	}
}

// 朴素的线段树. 支持区间/单点加/乘, 区间/单点求和, 单点求 max(min).
namespace SGT
{
	struct Seg_Tree
	{
		int l,r;
		ll val, atag, mtag, maxv;
	} t[100010*4];
	
	#define LCH (u<<1)
	#define RCH (u<<1|1)
	
	// 变量说明.
	// lx rx 为查询/修改的左右界
	// vx 为修改的值
	int lx,rx; ll vx;
	
	// 下推 u 的标记.
	void Pushdown(int u)
	{
		if (!t[u].atag && t[u].mtag==1) return; // boost
		
		ll at=t[u].atag, mt=t[u].mtag;
		t[u].atag=0; t[u].mtag=1;
		
		// 先乘后加
		if (mt!=1)
		{
			t[LCH].mtag*=mt; t[RCH].mtag*=mt;
			t[LCH].atag*=mt; t[RCH].atag*=mt;
			t[LCH].val*=mt; t[RCH].val*=mt;
		}
		if (at)
		{
			t[LCH].atag+=at; t[RCH].atag+=at;
			t[LCH].val+=(t[LCH].r-t[LCH].l+1)*at;
			t[RCH].val+=(t[RCH].r-t[RCH].l+1)*at;
		}
	}
	// 用子树更新 u.
	void Pushup(int u)
	{
		t[u].maxv=std::max(t[LCH].maxv, t[RCH].maxv);
		t[u].val=t[LCH].val+t[RCH].val;
	}
	// L <-> R 建树.
	void BuildTree(int u,int L, int R)
	{
		t[u].l=L; t[u].r=R;
		t[u].mtag=1; // **这个标记要注意**
		if (L==R)
		{
			t[u].atag=t[u].maxv=t[u].val=0;
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
			t[u].val+=(t[u].r-t[u].l+1)*vx;
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
			t[u].val*=vx;
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
	// 查询区间/单点求和
	ll Qry_Sum(int u)
	{
		if (t[u].l>=lx && t[u].r<=rx)
			return t[u].val;
		Pushdown(u);
		int m=(t[u].l+t[u].r)/2; ll ret=0;
		if (lx<=m) ret+=Qry_Sum(LCH);
		if (rx>m) ret+=Qry_Sum(RCH);
		Pushup(u);
		return ret;
	}
	// 查询区间/单点最大
	ll Qry_Max(int u)
	{
		if (t[u].l>=lx && t[u].r<=rx)
			return t[u].maxv;
		Pushdown(u);
		int m=(t[u].l+t[u].r)/2; ll ret=0;
		if (rx<=m) ret=Qry_Max(LCH);
		else if (lx>m) ret=Qry_Max(RCH);
		else ret=std::max(Qry_Max(LCH), Qry_Max(RCH));
		Pushup(u);
		return ret;
	}
}

// 朴素的 FFT
namespace FFT
{
	const double PI=3.14159265358;
	struct Complex
	{
		double r,i;
		Complex(double inr=0, double ini=0) { r=inr; i=ini; }
		Complex operator + (const Complex& B) { return Complex(r+B.r, i+B.i); }
		Complex operator - (const Complex& B) { return Complex(r-B.r, i-B.i); }
		Complex operator * (const Complex& B) { return Complex(r*B.r-i*B.i, i*B.r+r*B.i); }
	};
	
	// 蝴蝶变换; 接受任意类型的数组和一个长度 (**可以是非 2^n 长度).
	int pre_len=-1,revt,rev[300010];
	template<typename poly_arr>
	void BtFl(poly_arr *y, int len)
	{
		if (len!=pre_len)
		{
			pre_len=len; revt=0; int tmp=2;
			while (tmp<len) { tmp<<=1; revt++; }
			for (int i=0;i<len;i++) rev[i]=(rev[i>>1]>>1)|((i&1)<<revt); // 预处理反转位置
		}
		for (int i=0;i<len;i++) if (i<rev[i]) swap(y[i],y[rev[i]]); // 反转
	}
	// 法法塔; 要求 len 是 2^n; mode=1 实现 DFT, mode=-1实现 IDFT.
	void FFT(Complex *y, int len, int mode)
	{
		BtFl(y,len);
		
		for (int i=1;i<len;i<<=1)
		{
			const Complex wn( cos(PI/i), mode*sin(PI/i) );
			for (int j=0;j<len;j+=(i<<1)) // Each Process Start Point
			{
				Complex w(1,0);
				for (int k=0;k<i;k++,w=w*wn) // Step size
				{
					Complex t1=y[j+k], t2=w*y[i+j+k];
					y[j+k]=t1+t2;
					y[i+j+k]=t1-t2;
				}
			}
		}
		if (mode==-1) for (int i=0;i<len;i++) y[i].r/=len;
	}
}

// 求 a 和 b 的最大公约数
ll gcd(ll a, ll b)
{
	if (!b) return a;
	return gcd(b,a%b);
}

// 解丢番图方程 ax+by=gcd(a,b). exgcd 的推广见数学手册 exgcd 部分.
void exgcd(ll &x,ll &y,ll a,ll b)
{
	if (!b) { x=1; y=0; }
	else
	{
		exgcd(y,x,b,a%b);
		y=y-x*(a/b);
	}
}

// 在数组中对 [l,r] 进行快排; 默认比较器: <
template<typename arr_>
void QuickSort(int l, int r, arr_ *seq)
{
	int i=l,j=r,mid=seq[(l+r)/2];
	while (i<=j)
	{
		while (seq[i]<mid) i++;
		while (seq[j]>mid) j--;
		if (i<=j) 
		{
			swap(seq[i], seq[j]);
			i++; j--;
		}
	}
	if (i<r) QuickSort(i,r,seq);
	if (j>l) QuickSort(l,j,seq);
}