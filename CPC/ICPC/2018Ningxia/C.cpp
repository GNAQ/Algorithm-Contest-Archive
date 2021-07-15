#include<iostream>
#include<cstdio>
#include<queue>
using namespace std;
const int MAXN=3e5+100;
struct E{
	int to;
	int next;
}e[MAXN<<1];
queue<int>line;
int head[MAXN],d[MAXN],pre_d[MAXN],dp[MAXN],u[MAXN],v[MAXN],tot;
void add_edge(int u,int v)
{
	e[++tot].next=head[u];
	e[tot].to=v;
	head[u]=tot;
}
int main()
{
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&u[i],&v[i]);
		u[i]++;v[i]++;
		//add_edge(u,v);
		//add_edge(v,u);
		pre_d[u[i]]++;
		pre_d[v[i]]++;
	}
	for(int i=1;i<=m;i++)
	{
		if(pre_d[u[i]]<pre_d[v[i]])
		{
			d[v[i]]++;
			add_edge(u[i],v[i]);
		}
		if(pre_d[u[i]]>pre_d[v[i]])
		{
			d[u[i]]++;
			add_edge(v[i],u[i]);
		}
	}
	for(int i=1;i<=n;i++)
		if(!d[i])
			line.push(i);
	while(!line.empty())
	{
		int x=line.front();
		line.pop();
		for(int i=head[x];i;i=e[i].next)
		{
			int to=e[i].to;
			d[to]--;
			dp[to]=max(dp[to],dp[x]+1);
			if(!d[to])
				line.push(to);
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++)
		ans=max(ans,dp[i]);
	cout<<ans+1;
}