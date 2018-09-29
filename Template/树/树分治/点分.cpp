#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<queue>
#include<vector>
#include<iterator>
#include<cstdlib>
#include<set>
#include<map>
#define ll long long
using namespace std;

struct ed
{
	int pre,to,w;
}edge[100010]={0};
int nodenum,edgenum,ptr[50010]={0},at=0,fx,tx,wx,kx;

int tsiz[50010]={0},hson[50010]={0};
bool vis[50010]={0};
int subsiz,hpt;

int ans=0,dis[50010]={0},dist=0,plen;

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

inline void initx(int now,int fa,int nowdis)
{
	dis[++dist]=nowdis;
	for (int prex=ptr[now];prex;prex=edge[prex].pre) if (edge[prex].to!=fa && (!vis[edge[prex].to]))
		initx(edge[prex].to,now,nowdis+edge[prex].w);
}

inline int solve(int now)
{
	dist=0; initx(now,0,plen);
	sort(dis+1,dis+dist+1);
	int ret=0,lp=1,rp=dist;
	
	while (lp<=rp)
	{
		if (dis[rp]+dis[lp]<=kx) { ret+=rp-lp; lp++; }
		else rp--;
	}
	return ret;
}

inline void getHr(int now,int fa)
{
	tsiz[now]=1;
	for (int prex=ptr[now];prex;prex=edge[prex].pre) if (edge[prex].to!=fa && (!vis[edge[prex].to]))
	{
		getHr(edge[prex].to,now);
		tsiz[now]+=tsiz[edge[prex].to];
		hson[now]=max(hson[now],tsiz[edge[prex].to]);
	}
	hson[now]=max(hson[now],subsiz-tsiz[now]);
	if (hson[now]<hson[hpt]) hpt=now; 
}

inline void divs(int now)
{
	plen=0; ans+=solve(now); vis[now]=true;
	for (int prex=ptr[now];prex;prex=edge[prex].pre) if (!vis[edge[prex].to])
	{
		plen=edge[prex].w; ans-=solve(edge[prex].to);
		
		subsiz=tsiz[edge[prex].to]; hpt=0;
		getHr(edge[prex].to,0);
		
		divs(hpt);
	}
}

int main()
{
	readx(nodenum);
	for (int i=1;i<nodenum;i++)
	{
		readx(fx); readx(tx); readx(wx);
		Insert();
	}
	readx(kx);
	hpt=0; hson[0]=2*1e9; subsiz=nodenum;
	
	getHr(1,0);
	divs(hpt); 
	printf("%d\n",ans);
	return 0;
}
