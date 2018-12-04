#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<cmath>
#include<queue>
#define ll long long
using namespace std;

struct ed
{
	int pre,to; ll w;
}edge[400010];
int at,ptr[100010],n,m;

template<typename int_t>
void readx(int_t& x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

void Is(int fx,int tx,ll wx)
{
	edge[++at].pre=ptr[fx];
	edge[at].to=tx;
	edge[at].w=wx;
	ptr[fx]=at;
}

struct _Node
{
	ll dis; int cod;
	bool operator < (const _Node& B) const { return dis>B.dis; }
};
priority_queue<_Node> que;
ll dis[100010]; bool vis[100010];

void Dijkstra(int src)
{
	_Node cac1,cac2;
	memset(vis,0,sizeof vis); memset(dis,0x3f,sizeof dis);
	dis[src]=cac1.dis=0; cac1.cod=src; que.push(cac1);
	while (!que.empty())
	{
		cac1=que.top(); que.pop();
		if (vis[cac1.cod]) continue;
		vis[cac1.cod]=1;
		for (int prex=ptr[cac1.cod];prex;prex=edge[prex].pre)
		{
			int v=edge[prex].to;
			if (dis[v]>dis[cac1.cod]+edge[prex].w)
			{
				dis[v]=dis[cac1.cod]+edge[prex].w;
				cac2.cod=v; cac2.dis=dis[v]; que.push(cac2);
			}
		}
	}
}

int main()
{
	int ss,fx,tx; ll wx;
	readx(n); readx(m); readx(ss);
	for (int i=1;i<=m;i++)
	{
		readx(fx); readx(tx); readx(wx);
		Is(fx,tx,wx);
	}
	Dijkstra(ss);
	for (int i=1;i<=n;i++) printf("%lld%c",dis[i]," \n"[i==n]);
}
