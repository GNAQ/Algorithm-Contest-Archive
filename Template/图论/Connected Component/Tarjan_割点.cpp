#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<utility>
#include<algorithm>
#include<iterator>
using namespace std;

struct ed
{
	int pre,to;
}edge[220010]={0};
int nodenum,edgenum,at,fx,tx,pointer[100010]={0};
//Tarjan
int dfn[100010]={0},low[100010]={0},tstamp=0;
bool ap[100010]={0};

void Insert()
{
	at++;
	edge[at].pre=pointer[fx];
	edge[at].to=tx;
	pointer[fx]=at;
	at++;
	edge[at].pre=pointer[tx];
	edge[at].to=fx;
	pointer[tx]=at;
}

void Tarjan(int u,int fatherx)
{
	low[u]=dfn[u]=++tstamp;
	int chnum=0,prex=pointer[u];
	while (prex)
	{
		if (!dfn[edge[prex].to])
		{
			chnum++;
			Tarjan(edge[prex].to,u);
			low[u]=min(low[u],low[edge[prex].to]);
			if (low[edge[prex].to]>=dfn[u]) ap[u]=true;
		}
		else if (edge[prex].to!=fatherx) low[u]=min(low[u],dfn[edge[prex].to]);
		prex=edge[prex].pre;
	}
	if (fatherx==-1 && chnum==1) ap[u]=0;
}

int main()
{
	scanf("%d%d",&nodenum,&edgenum);
	for (int i=1;i<=edgenum;i++)
	{
		scanf("%d%d",&fx,&tx);
		Insert();
	}
	
	for (int i=1;i<=nodenum;i++) if (!dfn[i]) Tarjan(i,-1);
	
	int ans=0;
	for (int i=1;i<=nodenum;i++) if (ap[i]) ans++;
	printf("%d\n",ans);
	for (int i=1;i<=nodenum;i++) if (ap[i]) printf("%d ",i);
	printf("\n");
	return 0;
}
