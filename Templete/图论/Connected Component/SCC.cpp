#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<algorithm>
#include<iterator>
#include<cmath>
#include<cstdlib>
#include<queue>
#include<vector>
using namespace std;

struct ed { int pre,to; } edge[100010]={0};
int nodenum,edgenum,at=0,pointer[100010]={0},fx,tx;
int nodev[100010]={0},dfn[100010]={0},low[100010]={0},stackx[100010]={0},headx=0,tstamp=0;
bool inst[100010]={0};

int ctr1=0,cache1,cache2;
int belong[100010]={0};

int dp[100010]={0};
ed edgex[100010]={0}; int atx=0,pox[100010]={0},nodes[100010]={0};

inline void readx(int& x)
{
	x=0; int k=1; register char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

inline void Insert()
{
	at++;
	edge[at].pre=pointer[fx];
	edge[at].to=tx;
	pointer[fx]=at;
}
inline void Insert2()
{
	atx++;
	edgex[atx].pre=pox[fx];
	edgex[atx].to=tx;
	pox[fx]=atx;
}

inline void tarjan(int u)
{
	low[u]=dfn[u]=++tstamp; stackx[++headx]=u; inst[u]=true;
	for (int prex=pointer[u];prex;prex=edge[prex].pre)
	{
		if (!dfn[edge[prex].to])
		{
			tarjan(edge[prex].to);
			low[u]=min(low[u],low[edge[prex].to]);
		}
		else if (inst[edge[prex].to]) low[u]=min(low[u],dfn[edge[prex].to]);
	}
	
	if (low[u]==dfn[u])
	{
		ctr1++;
		do
		{
			cache1=stackx[headx--];
			belong[cache1]=ctr1;
			nodes[ctr1]+=nodev[cache1];
			inst[cache1]=false;
		} while (cache1!=u);
	}
}

inline void Shrink()
{
	for (int i=1;i<=nodenum;i++)
	{
		fx=belong[i];
		for (int prex=pointer[i];prex;prex=edge[prex].pre)
		{
			if (fx!=belong[edge[prex].to])
			{
				tx=belong[edge[prex].to];
				Insert2();
			}
		}
	}
}

inline void dpx(int nownode)
{
	inst[nownode]=true;
	for (int prex=pox[nownode];prex;prex=edgex[prex].pre)
	{
		if (!inst[edgex[prex].to]) dpx(edgex[prex].to);
		dp[nownode]=max(dp[nownode],dp[edgex[prex].to]);
	}
	dp[nownode]+=nodes[nownode];
}

int main()
{
	readx(nodenum); readx(edgenum);
	for (int i=1;i<=nodenum;i++) readx(nodev[i]);
	for (int i=1;i<=edgenum;i++)
	{
		readx(fx); readx(tx); Insert();
	}
	
	for (int i=1;i<=nodenum;i++) if (!dfn[i]) tarjan(i);
	Shrink(); memset(inst,0,sizeof(inst));
	
	for (int i=1;i<=nodenum;i++) if (!inst[i]) dpx(i);
	for (int i=1;i<=nodenum;i++) dp[1]=max(dp[1],dp[i]);
	printf("%d\n",dp[1]);
	return 0;
}
