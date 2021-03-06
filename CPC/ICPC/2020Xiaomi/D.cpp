#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<utility>
#include<algorithm>
#include<iterator>
#include<map>
using namespace std;

struct ed
{
	int pre,to;
}edge[600010];
int n,m,at,fx,tx,ptr[300010];
//Tarjan
int dfn[300010],low[300010],tstamp=0;
bool ap[300010];

bool vis[300010];

int ans[300010], sonnum[300010];

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

void Insert()
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

void Tarjan(int u,int fa)
{
	low[u]=dfn[u]=++tstamp;
	
	for (int v=ptr[u];v;v=edge[v].pre)
	{
		if (!dfn[edge[v].to])
		{
			sonnum[u]++;
			Tarjan(edge[v].to,u);
			low[u]=min(low[u],low[edge[v].to]);
			if (low[edge[v].to]>=dfn[u]) 
			{
				ap[u]=true;
				ans[u]++;
			}
		}
		else if (edge[v].to!=fa) low[u]=min(low[u],dfn[edge[v].to]);
	}
	if (fa==-1 && sonnum[u]==1) ap[u]=0;
}

int main()
{
	readx(n); readx(m);
	for (int i=1;i<=m;i++)
	{
		readx(fx); readx(tx);
		Insert();
	}
	
	int tot=0;
	for (int i=1;i<=n;i++) if (!dfn[i]) 
	{
		tot++;
		Tarjan(i,-1);
		if (sonnum[i]>1) ans[i]=sonnum[i];
		else ans[i]=1;
		vis[i]=1;
	}
	
	for (int i=1;i<=n;i++) if (!vis[i]) ans[i]++;
	
	for (int i=1;i<=n;i++)
	{
		ans[i]+=tot-1;
		if (!ptr[i]) ans[i]=tot-1;
	}
	
	for (int i=1;i<=n;i++)
		printf("%d%c", ans[i], " \n"[i==n]);
	
	
	return 0;
}