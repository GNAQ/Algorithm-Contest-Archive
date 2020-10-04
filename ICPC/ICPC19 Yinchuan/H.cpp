#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<queue>
#include<set>
#define ll long long
using namespace std;

struct ed
{
	int pre,to,w;
} edge[1000010];
int at,ptr[40010];

int n,m1,m2,ss;
vector<int> vset[40010], actv[40010];
int cor[40010],cors;

vector< pair<int,int> > e[40010];

int ind[40010];

struct _Node
{
	ll dis; int cod;
	bool operator < (const _Node& B) const { return dis>B.dis; }
};
ll dis[40010]; bool vis[40010];

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

void Color(int u,int fx)
{
	for (int v=ptr[u];v;v=edge[v].pre)
		if (!cor[ edge[v].to ])
		{
			cor[ edge[v].to ]=fx;
			vset[fx].push_back(edge[v].to);
			Color(edge[v].to,fx);
		}
}

void Dijkstra(vector<int> &src)
{
	priority_queue<_Node> que;
	_Node cac1,cac2; 
	// memset(vis,0,sizeof vis);
	
	int size = src.size();
	for (int i=0;i<size;i++)
	{
		cac1.dis=dis[src[i]];
		cac1.cod=src[i];
		que.push(cac1);
	}
	
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
	readx(n); readx(m1); readx(m2); readx(ss); int fx,tx,wx;
	for (int i=1;i<=m1;i++) 
	{
		readx(fx); readx(tx); readx(wx);
		Is(fx,tx,wx);
		Is(tx,fx,wx);
	}
	
	for (int i=1;i<=n;i++) if (!cor[i])
	{
		cor[i]=++cors;
		vset[cors].push_back(i);
		Color(i,cors);
	}
	
	for (int i=1;i<=m2;i++)
	{
		readx(fx); readx(tx); readx(wx);
		e[fx].push_back( make_pair(tx,wx) );
		ind[cor[tx]]++;
	} 
	
	for (int i=0;i<=n;i++) dis[i]=2*1e9;
	dis[ss]=0;
	
	queue<int> que;
	for (int i=1;i<=cors;i++) if (!ind[i])
		que.push(i);
	
	while (!que.empty())
	{
		int nowc,u,v,w;
		int siz1, siz2;
		nowc=que.front(); que.pop(); siz1=vset[nowc].size();
		
		for (int i=0;i<siz1;i++)
		{
			u=vset[nowc][i];
			if (dis[u]<=1000000000) 
				actv[nowc].push_back(u);
		}
		
		if (actv[nowc].size()) 
		{
			// reset vis
			for (auto v:vset[nowc]) vis[v]=0;
			Dijkstra(actv[nowc]);
		}
		
		for (int i=0;i<siz1;i++)
		{
			u=vset[nowc][i];
			if (e[u].size())
			{
				siz2=e[u].size();
				for (int j=0;j<siz2;j++)
				{
					v=e[u][j].first; w=e[u][j].second;
					dis[v]=min(dis[v],dis[u]+w);
					ind[ cor[v] ]--;
					if (!ind[ cor[v] ]) que.push(cor[v]);
				}
			}
		}
	}
	
	for (int i=1;i<=n;i++)
	{
		if (dis[i]>1000000000) printf("NO PATH\n");
		else printf("%lld\n",dis[i]);
	}
	
	return 0;
}