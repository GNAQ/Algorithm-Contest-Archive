#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#define ll long long
using namespace std;

struct ed { int pre,to; }edge[100010],ed2[100010];
int n,m,at,ptr[100010],nodev[100010],at2,ptr2[100010];

//SCC
int sccnum,bel[100010],dfn[100010],low[100010],tstamp,sta[100010],hd,nnv[100010];
bool inst[100010];

int dp[100010];

template<typename int_t>
void readx(int_t& x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

void Is(int fx,int tx)
{
	edge[++at].pre=ptr[fx];
	edge[at].to=tx;
	ptr[fx]=at;
}

void Is2(int fx,int tx)
{
	ed2[++at2].pre=ptr2[fx];
	ed2[at2].to=tx;
	ptr2[fx]=at2;
}

void Tarjan(int now)
{
	dfn[now]=low[now]=++tstamp; sta[++hd]=now; inst[now]=1;
	for (int prex=ptr[now];prex;prex=edge[prex].pre)
	{
		if (!dfn[edge[prex].to])
		{
			Tarjan(edge[prex].to);
			low[now]=min(low[now],low[edge[prex].to]);
		}
		else if (inst[edge[prex].to]) low[now]=min(low[now],dfn[edge[prex].to]);
	}
	
	if (dfn[now]==low[now])
	{
		int cac_c; sccnum++;
		do
		{
			cac_c=sta[hd--];
			bel[cac_c]=sccnum;
			nnv[sccnum]+=nodev[cac_c];
			inst[cac_c]=0;
		}while (cac_c!=now);
	}
}

void Shrink()
{
	for (int i=1;i<=n;i++)
		for (int prex=ptr[i];prex;prex=edge[prex].pre)
			if (bel[i]!=bel[edge[prex].to]) Is2(bel[i],bel[edge[prex].to]);
}

int DP(int now)
{
	if (dp[now]) return dp[now];
	for (int prex=ptr2[now];prex;prex=ed2[prex].pre)
		dp[now]=max(dp[now],dp[ed2[prex].to]);
	dp[now]+=nnv[now];
	return dp[now];
}

int main()
{
	readx(n); readx(m); int fx,tx;
	for (int i=1;i<=n;i++) readx(nodev[i]);
	for (int i=1;i<=m;i++) 
	{
		readx(fx); readx(tx);
		Is(fx,tx);
	}
	for (int i=1;i<=n;i++) if (!dfn[i]) Tarjan(i);
	Shrink();
	for (int i=1;i<=sccnum;i++) if (!dp[i]) DP(i);
	for (int i=1;i<=sccnum;i++) dp[0]=max(dp[0],dp[i]);
	printf("%d\n",dp[0]);
}
