#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<queue>
#define ll long long
using namespace std;

struct ed
{
	int pre,to,w;
}edge[2000010];
int at,ptr[1000010],n,m,ss;

template<typename int_t>
void readx(int_t& x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

void Is(int fx,int tx,int wx)
{
	edge[++at].pre=ptr[fx];
	edge[at].to=tx;
	edge[at].w=wx;
	ptr[fx]=at;
}

bool vis[100010];
queue<int> que;
int dis[100010];
void SPFA(int src)
{
	memset(dis,0x3f,sizeof dis);
	memset(vis,0,sizeof vis);
	dis[src]=0; que.push(src); int cac;
	while (!que.empty())
	{
		cac=que.front(); que.pop(); vis[cac]=0;
		for (int prex=ptr[cac];prex;prex=edge[prex].pre)
		{
			if (dis[edge[prex].to]>dis[cac]+edge[prex].w)
			{
				dis[edge[prex].to]=dis[cac]+edge[prex].w;
				if (!vis[edge[prex].to])
				{
					vis[edge[prex].to]=1;
					que.push(edge[prex].to);
				}
			}
		}
	}
}

int main()
{
	readx(n); readx(m); readx(ss); int fx,tx,wx;
	for (int i=1;i<=m;i++)
	{
		readx(fx); readx(tx); readx(wx);
		Is(fx,tx,wx);
	}
	SPFA(ss);
	for (int i=1;i<=n;i++) printf("%d%c",(dis[i]>=0x3f3f3f3f?2147483647:dis[i])," \n"[i==n]);
}
