

/*
namespace SOL80 // can we get 80 pts??
{
	struct ed
	{
		int to,fr,w;
		friend bool operator < (const ed& a,const ed& b) 
			{ return a.w<b.w; }
	}edge[200020];
	
	namespace LCT
	{
		#define LCH (tree[inx].ch[0])
		#define RCH (tree[inx].ch[1])
		
		struct splay_tree { int fa,ch[2],val,rev; } tree[300010]={0};
		int troo,tsiz=0;
		
		void UpdN(int inx)
		{
			
		}
		void PutRev(int inx)
		{
			swap(LCH,RCH);
			tree[LCH].rev^=1; tree[RCH].rev^=1;
		}
		void Pushdown(int inx)
		{
			if (!tree[inx].rev) return;
			if (LCH) tree[LCH].rev^=1; 
			if (RCH) tree[RCH].rev^=1;
			swap(LCH,RCH); tree[inx].rev^=1;
		}
		bool NoRoot(int inx)
		{
			return (tree[tree[inx].fa].ch[0]==inx || tree[tree[inx].fa].ch[1]==inx);
		}
		void AllPushdown(int inx)
		{
			if (NoRoot(inx)) AllPushdown(tree[inx].fa);
			Pushdown(inx);
		}
		
		void Rotate(int inx)
		{
			int f=tree[inx].fa,g=tree[f].fa,flag=(tree[f].ch[1]==inx);
		
			if (NoRoot(f)) tree[g].ch[(tree[g].ch[1]==f)]=inx;
			if (tree[inx].ch[!flag]) tree[tree[inx].ch[!flag]].fa=f;
			tree[f].ch[flag]=tree[inx].ch[!flag]; tree[f].fa=inx;
			tree[inx].ch[!flag]=f; tree[inx].fa=g;
			UpdN(f); UpdN(inx);
		}
		void Splay(int inx)
		{
			AllPushdown(inx);
			for (;NoRoot(inx);Rotate(inx))
			{
				if (NoRoot(tree[inx].fa))
				{
					int g=tree[tree[inx].fa].fa;
					if ((tree[g].ch[1]==tree[inx].fa)==(tree[tree[inx].fa].ch[1]==inx)) Rotate(tree[inx].fa);
					else Rotate(inx);
				}
			}
		}
		
		void Access(int inx)
		{
			for (int ch=0;inx;inx=tree[ch=inx].fa) 
				{ Splay(inx); RCH=ch; UpdN(inx); }
		}
		void Makeroot(int inx)
		{
			Access(inx); Splay(inx);
			PutRev(inx);
		}
		int Findroot(int inx)
		{
			Access(inx); Splay(inx);
			while (LCH) { Pushdown(inx); inx=LCH; }
			Splay(inx); 
			return inx;
		}
		void Split(int x,int y)
		{
			Makeroot(x);
			Access(y); Splay(y);
		}
		int Link(int x,int y)
		{
			Makeroot(x); 
			if (Findroot(y)==x) return -1;
			tree[x].fa=y; return 1;
		}
		int Cut(int x,int y)
		{
			Makeroot(x);
			if (Findroot(y)==x && tree[y].fa==x && (!tree[y].ch[0]))
				{ tree[y].fa=tree[x].ch[1]=0; UpdN(x); return 1; }
			return -1;
		}
	};
	
	void AddE()
	{
		
	}
	void DelE()
	{
		
	}
	bool IsCon()
	{
		
	}
	
	void Work()
	{
		int fx,tx,wx;
		for (int i=1;i<=m;i++)
		{
			
		}
	}

	
	// Solution Sketch
	// 动态图连通性
	// 怎么处理重边
	// 毒瘤
	
}
*/

#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<vector>
#include<random>
#include<climits>
#include<ctime>
typedef long long ll;
using namespace std;

int n,m;

template<typename inp_t>
void readx(inp_t& x)
{
	x=0; int k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

namespace SOL1 // get 50 pts
{
	struct ed
	{
		int to,pre,w;
	}edge[400020];
	int at=1,ptr[100010];

	void Is(int fx,int tx,int wx)
	{
		at++;
		edge[at].pre=ptr[fx];
		edge[at].to=tx;
		edge[at].w=wx;
		ptr[fx]=at;
		at++;
		edge[at].pre=ptr[tx];
		edge[at].to=fx;
		edge[at].w=wx;
		ptr[tx]=at;
	}

	bool vis[100010];
	void DFS(int now,int ban)
	{
		vis[now]=1;
		for (int v=ptr[now];v;v=edge[v].pre) if (edge[v].w!=ban)
			if (!vis[edge[v].to]) DFS(edge[v].to,ban);
	}
	
	void Solve(int minW,int maxW)
	{
		cerr<<"!!Solve - 1!!"<<endl;
		
		if (minW>0) { printf("0\n"); return; }
		for (int wi=minW;wi<=maxW+1;wi++)
		{
			memset(vis,0,sizeof(bool)*(n+10));
			DFS(1,wi); int conn=0;
			for (int i=1;i<=n;i++) conn+=vis[i];
			if (conn==n) 
			{
				printf("%d\n",wi);
				return;
			}
		}
	}
	
	// complexity : O(wm(logm_ds)+mlogm)
	void Work()
	{
		int fx,tx,wx;
		int minW=2*1e9,maxW=-2*1e9;
		for (int i=1;i<=m;i++) 
		{
			readx(fx); readx(tx); readx(wx);
			Is(fx,tx,wx);
			minW=min(minW,wx);
			maxW=max(maxW,wx);
		}
		Solve(minW,maxW);
	}
};

namespace SOL70 // get 70 pts using randomize method (Dzy Loves Chinese II)
{
	std::random_device rng_dev;
	std::mt19937 rng_gen(rng_dev());
	std::uniform_int_distribution<unsigned long long> gen(1,ULLONG_MAX);
	
	struct ed
	{
		int pre,to;
	}edge[400010];
	int at=1,ptr[100010];
	
	unsigned long long lb[67];
	int dfn[100010],tstamp;
	unsigned long long ve[500010],se[100010];

	vector<int> wi[100003];

	void Is(int fx,int tx)
	{
		at++;
		edge[at].pre=ptr[fx];
		edge[at].to=tx;
		ptr[fx]=at;
		at++;
		edge[at].pre=ptr[tx];
		edge[at].to=fx;
		ptr[tx]=at;
	}

	void DFS(int now,int fa)
	{
		dfn[now]=++tstamp;
		for (int v=ptr[now];v;v=edge[v].pre)
		{
			int V=edge[v].to;
			if (V==fa) continue;
			if (!dfn[V]) // tree edge
			{
				DFS(V,now);
				ve[v>>1]=se[V];
				se[now]^=se[V];
			}
			else if (dfn[now]>dfn[V]) // not tree edge
			{
				ve[v>>1]=gen(rng_gen);
				se[now]^=ve[v>>1];
				se[V]^=ve[v>>1];
			}
		}
	}
	
	bool Solve(vector<int>& vec)
	{
		bool flag=1; unsigned long long tmp;
		memset(lb,0,sizeof lb);
		for (auto v:vec)
		{
			tmp=ve[v];
			for (int w=63;w>=0;w--) if ((tmp>>w)&1ULL)
			{
				if (!lb[w]) { lb[w]=tmp; break; }
				else tmp=tmp^lb[w];
			}
			if (!tmp) flag=0;
		}
		return flag;
	}
	
	void Work()
	{
		int fx,tx,wx; int minW=2*1e9,maxW=-2*1e9;
		for (int i=1;i<=m;i++)
		{
			readx(fx); readx(tx); readx(wx);
			Is(fx,tx);
			
			// SPC
			SOL1::Is(fx,tx,wx);
			
			wi[wx].push_back(i);
			minW=min(minW,wx); maxW=max(maxW,wx);
		}
		
		// special case
		// if (maxW<=100) { SOL1::Solve(minW,maxW); return; }
		
		if (minW>0) { printf("0\n"); return; }
		
		DFS(1,0);
		for (int w=minW;w<=maxW;w++)
		{
			if (Solve(wi[w]))
			{
				printf("%d\n",w);
				return;
			}
		}
		printf("%d\n",maxW+1);
	}
};

int main()
{
	char inpfile[20];
	scanf("%s",inpfile);
	freopen(inpfile,"r",stdin);
	
	readx(n); readx(m);
	
	// :case 1
	if (n<=1000 && m<=2000) 
	{
		SOL1::Work();
		return 0;
	}
	
	// :case 2
	if (n<=100000 && m<=200000)
	{
		SOL70::Work();
		return 0;
	}
	
	SOL1::Work();
}
	
/* ans==2 
8 11
1 2 0
3 2 1
1 3 1
1 5 0
5 6 5
6 8 9
7 5 1
6 7 2
7 8 1
4 7 5
8 4 3
*/