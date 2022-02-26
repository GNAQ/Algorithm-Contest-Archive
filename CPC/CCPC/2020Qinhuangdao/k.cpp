#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+100;
int dp[maxn][2],n;
vector<int>e[maxn];
void add_edge(int u,int v)
{
	e[u].push_back(v);
	e[v].push_back(u);
}
void dfs(int x,int f,int d)
{
	dp[x][0]=0;
	if(e[x].size()==1) dp[x][1]=d;
	else dp[x][1]=1e9;
	for(int i=0;i<e[x].size();i++)
	{
		int to=e[x][i];
		if(to==f) continue;
		dfs(to,x,d+1);
		int pre_1=dp[x][1],pre_0=dp[x][0];
		//cout<<"!!!!"<<x<<" "<<to<<" "<<pre_0<<" "<<pre_1<<endl;
		dp[x][1]=min(pre_1+dp[to][0]+2,min(pre_1+dp[to][1],pre_0+dp[to][1]));
		dp[x][0]=pre_0+dp[to][0]+2;
	}
	//cout<<x<<" "<<dp[x][0]<<" "<<dp[x][1]<<endl;
}
int main()
{
	int T;cin>>T;
	for(int ii=1;ii<=T;ii++)
	{
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
			e[i].clear();
		for(int i=2;i<=n;i++)
		{
			int x;
			scanf("%d",&x);
			add_edge(x,i);
		}
		dfs(1,-1,0);
		printf("Case #%d: %d\n",ii,dp[1][1]);
	}
}