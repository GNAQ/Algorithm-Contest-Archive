#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
struct ed
{
	int pre,to,w;
}edge[400110]={0};
int nodenum,edgenum,fx,tx,wx,at=0,pointer[200110]={0};
int dis[200110]={0};
bool vis[200110]={0},ans=0;

inline void readx(int& x)
{
	x=0;
	register char ch=0; int k=1;
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

inline void Insert2()
{
	at++;
	edge[at].pre=pointer[fx];
	edge[at].to=tx;
	edge[at].w=wx;
	pointer[fx]=at;
	at++;
	edge[at].pre=pointer[tx];
	edge[at].to=fx;
	edge[at].w=wx;
	pointer[tx]=at;
}

void SPFA(int nownode)
{
	vis[nownode]=true;
	int prex=pointer[nownode];
	while (prex)
	{
		if (dis[edge[prex].to]>dis[nownode]+edge[prex].w)
		{
			if (vis[edge[prex].to] || ans)
			{
				ans=true;
				break;
			}
			dis[edge[prex].to]=dis[nownode]+edge[prex].w;
			SPFA(edge[prex].to);
		}
		prex=edge[prex].pre;
	}
	vis[nownode]=false;
}

int main()
{
	readx(nodenum); readx(edgenum);
	for (int i=1;i<=edgenum;i++)
	{
		readx(fx); readx(tx); readx(wx);
		if (wx>=0) Insert2();
		else Insert();
	}
	
	for (int i=1;i<=nodenum;i++)
	{
		SPFA(i);
		if (ans) break;
	}
	if (ans) printf("YE5\n");
	else printf("N0\n");
	return 0;
}
