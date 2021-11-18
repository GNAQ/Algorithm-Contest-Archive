#include<bits/stdc++.h>
using namespace std;
const int maxn=1500;
vector<int>pre[maxn],pre_id[maxn];
int n,m,tot,w[maxn],head[maxn],in[maxn],dis[maxn],cnt[maxn],ans[maxn],vis[maxn];
struct node{
	int to;
	int val;
	int next;
}e[maxn];
queue<int>line;
void add_edge(int u,int v,int val)
{
	e[++tot].next=head[u];
	e[tot].to=v;
	e[tot].val=val;
	head[u]=tot;
}
void dfs(int x,int sum)
{
	ans[x]=min(ans[x],sum);
	for(int i=head[x];i;i=e[i].next)
	{
		int to=e[i].to;
		if(dis[to]!=dis[x]+1) continue;
		cnt[e[i].val]++;
		dfs(to,sum+cnt[e[i].val]*w[e[i].val]);
		cnt[e[i].val]--;
	}
}
void solve()
{
	line.push(1);dis[1]=0;
	for(int i=2;i<=n;i++) dis[i]=ans[i]=1e9;
	while(!line.empty())
	{
		int x=line.front();line.pop();
		for(int i=head[x];i;i=e[i].next)
		{
			int to=e[i].to;
			if(dis[to]<=dis[x]+1)
				continue;
			dis[to]=dis[x]+1;
			line.push(to);
		}
	}
//	for(int i=1;i<=n;i++)
//		cout<<dis[i]<<" ";
//	cout<<endl;
	dfs(1,0);
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
		scanf("%d",&w[i]);
	for(int i=1;i<=m;i++)
	{
		int u,v,c;
		scanf("%d%d%d",&u,&v,&c);
		add_edge(u,v,c);
		add_edge(v,u,c);
	}
	solve();
	for(int i=2;i<=n;i++)
		printf("%d\n",ans[i]);
}
