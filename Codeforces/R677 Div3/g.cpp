#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<vector>
#include<queue>
typedef long long ll;
using namespace std;

int G[1010][1010];
int tdis[1010][1010];
int n,m,k;
vector<int> des[1010];

vector< pair<int,int> > ed;

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}


struct _Node
{
	int dis; int cod;
	bool operator < (const _Node& B) const { return dis>B.dis; }
};
priority_queue<_Node> que;
int dis[1010]; bool vis[1010];

void Dijkstra(int src)
{
	_Node cac1,cac2;
	int u;
	memset(vis,0,sizeof vis); 
	memset(dis,0x3f,sizeof dis);
	
	dis[src]=cac1.dis=0; 
	cac1.cod=src; 
	que.push(cac1);
	
	while (!que.empty())
	{
		cac1=que.top(); que.pop();
		u=cac1.cod;
		
		if (vis[u]) continue;
		vis[u]=1;
		for (int v=1;v<=n;v++) if (v!=u)
		{
			if (dis[v]>dis[u]+G[u][v])
			{
				dis[v]=dis[u]+G[u][v];
				cac2.cod=v; cac2.dis=dis[v]; que.push(cac2);
			}
		}
	}
	
	for (int i=1;i<=n;i++) 
		tdis[src][i]=dis[i];
}

int main()
{
	memset(G,0x3f,sizeof G);
	readx(n); readx(m); readx(k);
	
	ll ans2=1000000000000000000LL;
	int u,v,w;
	
	for (int i=1;i<=m;i++)
	{
		readx(u); readx(v); readx(w);
		G[u][v]=G[v][u]=w;
		ed.push_back( make_pair(u,v) );
	}
	for (int i=1;i<=k;i++)
	{
		readx(u); readx(v);
		if (u==v) continue;
		des[u].push_back(v);
	}
	
	for (int i=1;i<=n;i++)
		Dijkstra(i);
	
	for (auto e:ed)
	{
		int fi=e.first, se=e.second;
		ll ans=0;
		
		for (int i=1;i<=n;i++)
			for (auto vv:des[i])
			{
				u=i; v=vv;
				ans+=(ll) min(tdis[u][v], min(tdis[u][fi]+tdis[se][v], tdis[u][se]+tdis[fi][v]));
			}
		
		ans2=min(ans2,ans);
	}
	
	cout<<ans2<<endl;
	return 0;
}