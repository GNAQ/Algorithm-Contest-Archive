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

struct ed { int pre,to; }edge[200010];
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

namespace LCA
{
	int dep[100010],tsiz[100010],laa[100010][22];
	int dfn[100010],nnv[100010],dfstime;
	
	void DFS1(int now,int fa,int ndep)
	{
		laa[now][0]=fa;
		for (int i=1;i<=20;i++) laa[now][i]=laa[laa[now][i-1]][i-1];
		
		dep[now]=ndep; tsiz[now]=1;
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

namespace PT
{
	#define LCH trie[inx].ch[0]
	#define RCH trie[inx].ch[1]
	
	struct Pres_Trie
	{
		int ch[2],val;
	}trie[5000010];
	int tsiz[100010],root[100010];
};

int main()
{
	readx(n); readx(q); int fx,tx;
	for (int i=1;i<n;i++)
	{
		readx(fx); readx(tx); 
		Is(fx,tx);
	}
	
	LCA::DFS1(1,0,1);
	
	
}