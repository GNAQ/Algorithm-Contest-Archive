#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<iterator>
#include<queue>
#include<vector>
#include<map>
#include<set>
typedef long long ll;
using namespace std;

struct ed { int pre,to; } edge[200010];
int at=1,ptr[100010];

int n,nodev[100010],q;


template<typename inp_t>
void readx(inp_t& x)
{
	x=0; int k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

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

int dfn[100010],nnv[100010],ord[100010];
int dep[100010],tsiz[100010];

namespace LCA
{
	int dtim,laa[100010][22];
	
	void DFS1(int now,int fa,int ndep)
	{
		laa[now][0]=fa;
		for (int i=1;i<=20;i++) laa[now][i]=laa[laa[now][i-1]][i-1];
		
		dfn[++dtim]=now; nnv[dtim]=nodev[now]; 
		
		ord[now]=dtim; dep[now]=ndep; tsiz[now]=1;
		for (int v=ptr[now];v;v=edge[v].pre) if (edge[v].to!=fa)
		{
			DFS1(edge[v].to,now,ndep+1);
			tsiz[now]+=tsiz[edge[v].to];
		}
	}
	
	int LCA(int u,int v)
	{
		if (dep[v]>dep[u]) swap(u,v);
		for (int i=20;i>=0;i--) if (dep[laa[u][i]]>=dep[v]) u=laa[u][i];
		if (u==v) return v;
		
		for (int i=20;i>=0;i--) if (laa[u][i]!=laa[v][i])
		{
			u=laa[u][i];
			v=laa[v][i];
		}
		return laa[u][0];
	}
};

namespace DS
{
	#define LCH tree[inx].ch[0]
	#define RCH tree[inx].ch[1]
	#define lch tree[now].ch[0]
	#define rch tree[now].ch[1]

	struct Trie
	{
		int ch[2],siz;
	}tree1[400010],tree2[400010];
	int trsiz,root1[400010],root2[400010];


	void Upd(int now,int inx,int dep,int val,Trie* tree)
	{
		if (dep==-1) 
		{
			tree[now].siz++;
			return;
		}
		bool dir=(val>>dep)&1LL;
		
		tree[now].ch[!dir]=tree[inx].ch[!dir];
		tree[now].ch[dir]=++trsiz;
		tree[tree[now].ch[dir]].siz=tree[tree[inx].ch[dir]].siz;
		
		Upd(tree[now].ch[dir],tree[inx].ch[dir],dep-1,val,tree);
		
		tree[now].siz=tree[lch].siz+tree[rch].siz;
	}
	
	int Qry1(int now,int inx,int dep,int val,Trie* tree)
	{
		if (dep==-1) return 0;
		bool dir=(val>>dep)&1LL;
		
		int d2=(tree[tree[now].ch[dir^1]].siz-tree[tree[inx].ch[dir^1]].siz>0);
		return Qry1(tree[now].ch[dir^d2],tree[inx].ch[dir^d2],
					dep-1,val,tree)+(d2<<dep);
	}
	
	void Qry2(int )
	{
		
	}

	#undef lch
	#undef rch
	#undef LCH
	#undef RCH
};

int main()
{
	readx(n); readx(q); int fx,tx;
	for (int i=1;i<=n;i++) readx(nodev[i]);
	for (int i=1;i<n;i++)
	{
		readx(fx); readx(tx); 
		Is(fx,tx);
	}
	
	LCA::DFS1(1,0,1);
	
	int opt,u,v,val;
	while (q--)
	{
		readx(opt);
		if (opt==1)
		{
			
		}
		else
		{
			
			
		}
	}
}