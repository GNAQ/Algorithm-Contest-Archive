#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<string>
#include<iterator>
#include<cstdlib>
#include<queue>
#include<vector>
using namespace std;

struct nodexx 
{
	int code,dis;
	int operator < (const nodexx& a) const { return dis>a.dis; }
};
priority_queue<nodexx> pque; 
struct ed { int pre,to,w; } edge[1000010]={0};
int nodenum,edgenum,at=0,pointer[10010]={0},fx,wx,tx,ss;

int dis[10010]={0}; bool vis[10010]={0};

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

inline void Dijkstra()
{
	nodexx cache1,cache2; cache1.code=ss; cache1.dis=0;
	fill(dis,dis+nodenum+8,2147483647); dis[ss]=0; pque.push(cache1);
	while (!pque.empty())
	{
		cache1=pque.top(); pque.pop();
		if (vis[cache1.code]) continue;
		vis[cache1.code]=true;
		for (int prex=pointer[cache1.code];prex;prex=edge[prex].pre)
		{
			if (dis[edge[prex].to]>dis[cache1.code]+edge[prex].w)
			{
				dis[edge[prex].to]=dis[cache1.code]+edge[prex].w;
				cache2.code=edge[prex].to; cache2.dis=dis[edge[prex].to]; pque.push(cache2);
			}
		}
	}
}

int main()
{
	freopen("dat.in","r",stdin);
	freopen("1.out","w",stdout);
	
	readx(nodenum); readx(edgenum); readx(ss);
	for (int i=1;i<=edgenum;i++)
	{
		readx(fx); readx(tx); readx(wx);
		Insert();
	}
	Dijkstra();
	for (int i=1;i<=nodenum;i++) printf("%d ",dis[i]); printf("\n");
	return 0;
}
