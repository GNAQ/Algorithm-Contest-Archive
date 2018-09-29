#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<queue>
#include<cstdlib>
#include<algorithm>
#include<iterator>
#include<vector>
using namespace std;

struct ed { int pre,to,w; } edge[1000010]={0};
int nodenum,edgenum,at=0,pointer[10010]={0},fx,tx,wx,ss;

queue<int> que;
bool vis[10010]={0};
int dis[10010];

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
	edge[at].w=wx;
	pointer[fx]=at;
}

inline void SPFA()
{
	fill(dis,dis+nodenum+8,2147483647); int cache1;
	que.push(ss); dis[ss]=0;
	while (!que.empty())
	{
		cache1=que.front(); que.pop(); vis[cache1]=false;
		for (int prex=pointer[cache1];prex;prex=edge[prex].pre)
			if (dis[edge[prex].to]>dis[cache1]+edge[prex].w)
			{
				dis[edge[prex].to]=dis[cache1]+edge[prex].w;
				if (!vis[edge[prex].to])
				{
					vis[edge[prex].to]=true;
					que.push(edge[prex].to);
				}
			}
	}
}

int main()
{
	freopen("dat.in","r",stdin);
	freopen("2.out","w",stdout);
	
	readx(nodenum); readx(edgenum); readx(ss);
	for (int i=1;i<=edgenum;i++)
	{
		readx(fx); readx(tx); readx(wx);
		Insert();
	}
	SPFA();
	for (int i=1;i<=nodenum;i++) printf("%d ",dis[i]); printf("\n");
	return 0;
}
