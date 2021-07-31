#include<cstdio>
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<string>
#include<algorithm>
#include<queue>
typedef long long ll;
using namespace std;

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

// Splay - 无区间反转
namespace SPL
{
	#define LCH (t[inx].ch[0])
	#define RCH (t[inx].ch[1])
	
	struct Splay_Tree
	{
		int ch[2], siz, fa, w, val;
	} t[400010];
	int tsiz,rt;
	
	// 更新节点数据
	void Upd(int inx)
	{
		t[inx].siz=t[inx].w+t[LCH].siz+t[RCH].siz;
	}
	// 旋转一个节点
	void Rotate(int inx)
	{
		int f=t[inx].fa, g=t[t[inx].fa].fa, dir=(t[t[inx].fa].ch[1]==inx);
		
		if (g) t[g].ch[t[g].ch[1]==f]=inx;
		if (t[inx].ch[!dir]) t[t[inx].ch[!dir]].fa=f;
		t[f].ch[dir]=t[inx].ch[!dir]; t[f].fa=inx;
		t[inx].fa=g; t[inx].ch[!dir]=f;
		
		Upd(f); Upd(inx);
	}
	// 把一个点旋转到 Targ 下面
	void Splay(int inx, int targ)
	{
		for (;t[inx].fa!=targ; Rotate(inx))
		{
			int f=t[inx].fa, g=t[t[inx].fa].fa;
			if (g!=targ)
			{
				if ( (t[g].ch[1]==f) == (t[f].ch[1]==inx) ) Rotate(f);
				else Rotate(inx);
			}
		}
		if (!targ) rt=inx;
	}
	// 求一个数的排名
	int GetRank(int inx, int val)
	{
		if (t[inx].val==val) { Splay(inx, 0); return t[LCH].siz+1; }
		return GetRank(t[inx].ch[t[inx].val<val], val);
	}
	// 求排名为 val 的数的值
	int GetVal(int inx, int val)
	{
		if (t[LCH].siz<val && t[inx].w+t[LCH].siz>=val) 
			{ Splay(inx, 0); return t[inx].val; }
		if (val<=t[LCH].siz) return GetVal(LCH, val);
		else return GetVal(RCH, val-t[LCH].siz-t[inx].w);
	}
	// 求值为 val 的结点下标
	int GetInx(int val)
	{
		int inx=rt;
		while (t[inx].val!=val)
			inx=t[inx].ch[t[inx].val<val];
		return inx;
	}
	// 求 [inx] 结点的 (0)前驱/(1)后继
	int PreSuc(int inx, int dir)
	{
		inx=t[inx].ch[dir];
		while (t[inx].ch[!dir]) inx=t[inx].ch[!dir];
		return inx;
	}
	// 插入 val
	void Ins(int &inx, int f, int val)
	{
		if (!inx)
		{
			inx=++tsiz;
			t[inx].fa=f; t[inx].siz=t[inx].w=1;
			t[inx].val=val;
			Splay(inx,0); return;
		}
		t[inx].siz++;
		if (t[inx].val==val) { t[inx].w++; Splay(inx, 0); return; }
		Ins(t[inx].ch[t[inx].val<val], inx, val);
	}
	// 删除一次 val
	void Del(int val)
	{
		int inx=GetInx(val); Splay(inx,0);
		if (t[inx].w>1) { t[inx].w--; t[inx].siz--; return; }
		
		Splay(PreSuc(inx,0), inx);
		rt=LCH; t[LCH].fa=0;
		t[LCH].ch[1]=RCH; t[RCH].fa=LCH;
		Upd(LCH); 
	}
	// 初始化树并插入两个哨兵结点
	void Init_Tree()
	{
		tsiz=2; rt=1;
		t[1].w=1; t[1].siz=2; t[1].val=-2*1e9; t[1].ch[1]=2;
		t[2].w=1; t[2].siz=1; t[2].val=2*1e9; t[2].fa=1;
	}
	
	#undef LCH
	#undef RCH
}

// 无旋 Treap.
namespace Treap
{
	#define LCH t[inx].ch[0]
	#define RCH t[inx].ch[1]
	
	struct Treap_tree
	{
		int ch[2], val, key, w, fa, siz;
	}t[100010];
	int tsiz, rt;
	
	void Update(int inx)
	{
		t[inx].siz=t[LCH].siz+t[RCH].siz+t[inx].w;
	}
	
	// 0 代表左旋，1 代表右旋；动态更新结点编号
	void Rotate(int &inx, int dir)
	{
		int ch=t[inx].ch[!dir];
		t[inx].ch[!dir]=t[ch].ch[dir];
		t[ch].ch[dir]=inx;
		Update(inx); Update(inx = ch);
	}
	
	// inx 是 ref，旋转时注意时机和写法。
	void Ins(int &inx, int val)
	{
		if (!inx)
		{
			inx=++tsiz;
			t[inx].w=t[inx].siz=1;
			t[inx].key=rand(); t[inx].val=val;
			return;
		}
		t[inx].siz++;
		if (t[inx].val==val)
		{
			t[inx].w++;
			return;
		}
		bool flag=t[inx].val<val;
		Ins(t[inx].ch[flag], val);
		if (t[inx].key<t[t[inx].ch[flag]].key) Rotate(inx, !flag);
	}
	
	// 删除，注意旋转和只有单儿子的情况
	void Del(int &inx, int val)
	{
		if (!inx) return;
		t[inx].siz--;
		if (t[inx].val==val)
		{
			if (t[inx].w>1) 
			{
				t[inx].w--;
				return;
			}
			if (!(LCH*RCH)) { inx=LCH+RCH; return; }
			bool flag=(t[LCH].key<t[RCH].key);
			Rotate(inx, !flag); Del(inx, val);
		}
		else Del(t[inx].ch[t[inx].val<val], val);
	}
	
	// 前后驱，注意构造性写法
	int Pre(int inx, int val)
	{
		if (!inx) return -2*1e9;
		if (t[inx].val>=val) return Pre(LCH, val);
		return max(t[inx].val, Pre(RCH, val));
	}
	
	int Suc(int inx, int val)
	{
		if (!inx) return 2*1e9;
		if (t[inx].val<=val) return Suc(RCH, val);
		return min(t[inx].val, Suc(LCH, val));
	}
	
	int Rank(int inx, int val)
	{
		if (!inx) return 0;
		if (t[inx].val==val) return t[LCH].siz+1;
		else if (t[inx].val>val) return Rank(LCH, val);
		else return t[LCH].siz+t[inx].w+Rank(RCH, val);
	}
	
	int ID(int inx, int val)
	{
		if (val<=t[LCH].siz) return ID(LCH, val);
		if (val>t[LCH].siz+t[inx].w) return ID(RCH, val-t[LCH].siz-t[inx].w);
		return inx;
	}
	
	#undef LCH
	#undef RCH
}

// 维护集合 | 基于大根堆的 fhq_treap -> 可重集结点合并策略
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

// 无 "特殊" 优化的朴素 Dinic，注意 T 最好是最大的点
namespace Dinic
{
	struct ed
	{
		int pre, to;
		int cap;
	}edge[200010];
	int at=1, ptr[100010];
	
	int lvl[100010],cur[100010];
	int S,T;
	
	queue<int> que;
	int BFS(void)
	{
		memset(lvl, 0, sizeof(int) * (T+5)); // 注意
		lvl[S] = 1; que.push(S);
		int cac;
		while (!que.empty())
		{
			cac = que.front(); que.pop();
			for (int v=ptr[cac]; v; v=edge[v].pre)
				if (!lvl[edge[v].to] && edge[v].cap)
				{
					lvl[edge[v].to] = lvl[cac] + 1;
					que.push(edge[v].to);
				}
		}
		if (!lvl[T]) return false;
		memcpy(cur, ptr, sizeof(int) * (T+5));
		return true;
	}
	
	int DFS(int u, int minf)
	{
		if (!minf || u==T) return minf;
		int needf=0, sumf=0;
		for (int v=cur[u]; v; v=edge[v].pre)
			if (lvl[edge[v].to]==lvl[u]+1)
			{
				cur[u]=v;
				if (needf=DFS(edge[v].to, min(minf, edge[v].cap)))
				{
					sumf+=needf; minf-=needf;
					edge[v].cap-=needf; edge[v^1].cap+=needf;
					if (!minf) break;
				}
			}
		return sumf;
	}
}

// AC 自动机
namespace ACAM
{
	
	// AC 自动机，注意根是 [1] 号点！！
	struct ACAM
	{
		int fil, ch[27], val;
	}ac[1000010];
	int tsiz=1;

	void Ins(char *wd)
	{
		int u = 1, len = strlen(wd+1);
		
		for (int i=1;i<=len;i++) wd[i]=wd[i]-'a'+1;
		
		for (int i=1;i<=len;i++)
		{
			if (!ac[u].ch[wd[i]])
				ac[u].ch[wd[i]]=++tsiz;
			u = ac[u].ch[wd[i]];
		}
		
		// 这里是客制化代码
		ac[u].val++;
	}

	void GetFail()
	{
		queue<int> que;
		int u, cac;
		
		// 必须从第二层开始增量构造，否则会导致自指。
		// 注意根的儿子的 fail 要指向根。
		// 注意根节点的空儿子要指回根
		for (int i=1;i<=26;i++) 
		{
			if (ac[1].ch[i]) 
			{
				ac[ac[1].ch[i]].fil = 1;
				// 这里可以显式建树
				// Is(1, ac[1].ch[i]);
				que.push(ac[1].ch[i]);
			}
			else
				ac[1].ch[i] = 1;
		}
		
		while (!que.empty())
		{
			u = que.front(); que.pop();
			
			for (int i=1;i<=26;i++)
			{
				int v = ac[u].ch[i];
				if (v)
				{
					ac[v].fil = ac[ac[u].fil].ch[i];
					
					// 这里可以显式建树
					// Is(ac[v].fil, v);
					
					que.push(v);
				}
				else
					ac[u].ch[i] = ac[ac[u].fil].ch[i];
			}
		}
	}

	void Qry(char *str)
	{
		int len = strlen(str+1), u = 1, ans = 0;
		
		for (int i=1;i<=len;i++) str[i]=str[i]-'a'+1;
		
		for (int i=1;i<=len;i++)
		{
			u = ac[u].ch[str[i]];
			int v = u;
			while (v && ac[v].val!=-1)
			{
				ans += ac[v].val;
				ac[v].val=-1;
				v = ac[v].fil;
			}
		}
		
		printf("%d\n", ans);
		return;
	}
}

// 维护 fail 树的 AC 自动机，例题；洛谷模板（二次加强版）
// 询问 pattern string 的出现次数
namespace ACAM_2_Fail
{
	vector<int> edge[400010];

	void Is(int u, int v)
	{
		edge[u].push_back(v);
	}

	struct ACAM
	{
		int ch[27], fil, val;
		vector<int> ids;
	}ac[400010];
	int tsiz = 1;
	
	void Ins(char *wd, int id)
	{
		int len = strlen(wd + 1);
		for (int i=1;i<=len;i++) wd[i] = wd[i] - 'a' + 1;
		
		int u = 1;
		for (int i=1;i<=len;i++)
		{
			if (!ac[u].ch[wd[i]])
				ac[u].ch[wd[i]]=++tsiz;
			u = ac[u].ch[wd[i]];
		}
		ac[u].ids.push_back(id);
	}
	
	void GetFail()
	{
		queue<int> que;
		int u, cac;
		
		for (int i=1;i<=26;i++)
		{
			if (ac[1].ch[i])
			{
				ac[ac[1].ch[i]].fil = 1;
				
				// Add Edge
				Is(1, ac[1].ch[i]);
				
				que.push(ac[1].ch[i]);
			}
			else
				ac[1].ch[i]=1;
		}
		
		while (!que.empty())
		{
			u = que.front(); que.pop();
			for (int i=1;i<=26;i++) 
			{
				int v = ac[u].ch[i];
				if (v)
				{
					ac[v].fil = ac[ac[u].fil].ch[i];
					
					// Add Edge
					Is(ac[v].fil, v);
					
					que.push(v);
				}
				else
					ac[u].ch[i] = ac[ac[u].fil].ch[i];
			}
		}
	}
	
	void Qry(char *str)
	{
		int len = strlen(str + 1), u = 1;
		
		for (int i=1;i<=len;i++) 
			str[i] = str[i] - 'a' + 1;
		
		for (int i=1;i<=len;i++)
		{
			u = ac[u].ch[str[i]];
			ac[u].val++;
		}
	}
	
	void DFS(int u)
	{
		for (int i=0;i<edge[u].size();i++)
		{
			DFS(edge[u][i]);
			ac[u].val+=ac[edge[u][i]].val;
		}
	}
}

// 朴素的点分治，题目：统计树上是否有 k 长路径
namespace Node_Div
{
	struct ed
	{
		int pre, to , w;
	} edge[200010];
	int at, ptr[100010], n, m, qry[1010], ans[1010];

	// 点分
	int tsiz[100010], msiz[100010];
	bool vis[100010];
	int subsiz, hr;

	// 统计路径
	bool bac[10000010];
	vector<int> diss;
	
	// 求树的重心。使用的全局变量：[subsiz] [hr]
	void GetRt(int u, int fa)
	{
		tsiz[u]=1; msiz[u]=0;
		for (int v=ptr[u];v;v=edge[v].pre) 
			if (edge[v].to!=fa && !vis[edge[v].to])
			{
				GetRt(edge[v].to, u);
				tsiz[u]+=tsiz[edge[v].to];
				msiz[u]=max(msiz[u], tsiz[edge[v].to]);
				
			}
		msiz[u]=max(msiz[u], subsiz-tsiz[u]);
		if (msiz[u]<msiz[hr]) hr=u;
	}
	
	// DFS 求子树根到每个点的路径
	void DFS_Dis(int u, int fa, int ndis)
	{
		if (ndis>10000002) return; // 毒瘤
		diss.push_back(ndis);
		for (int v=ptr[u];v;v=edge[v].pre) 
			if (edge[v].to!=fa && !vis[edge[v].to])
				DFS_Dis(edge[v].to, u, ndis + edge[v].w); 
	}

	// 点分治需要灵活设计的 Calc 函数
	void Calc(int u)
	{
		vector<int> totdis;
		for (int v=ptr[u];v;v=edge[v].pre) if (!vis[edge[v].to])
		{
			diss.clear();
			DFS_Dis(edge[v].to, u, edge[v].w);
			
			for (int j=0;j<diss.size();j++)
				for (int k=1;k<=m;k++)
					if (qry[k]>=diss[j])
						ans[k]|=bac[qry[k]-diss[j]];
				
			for (int j=0;j<diss.size();j++)
			{
				totdis.push_back(diss[j]);
				bac[diss[j]]=1;
			}
		}
		for (int i=0;i<totdis.size();i++)
			bac[totdis[i]]=0;
	}

	// 点分过程（在这里建点分树）
	void Div(int u, int totn)
	{
		vis[u]=1; Calc(u);
		for (int v=ptr[u];v;v=edge[v].pre) if (!vis[edge[v].to])
		{
			subsiz = tsiz[edge[v].to];
			if (subsiz>tsiz[u]) subsiz = totn - tsiz[u];
			msiz[hr=0]=1e9;
			GetRt(edge[v].to, 0);
			Div(hr, subsiz);
		}
	}
	
	void INTO_MAIN()
	{
		// READ
		bac[0]=1;
		subsiz = n;
		msiz[hr=0]=1e9;
		GetRt(1, 0);
		Div(hr, n);
		
	}
};