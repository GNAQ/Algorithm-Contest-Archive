#include<iostream>
#include<cstdio>
using namespace std;
int vis[1000][1000],ans;
void dfs(int i,int j)
{
	ans++;vis[i][j]=0;
	if(vis[i+1][j]) dfs(i+1,j);
	if(vis[i][j+1]) dfs(i,j+1);
}
int main()
{
	int T;cin>>T;
	while(T--)
	{
		int n,m,k;
		cin>>n>>m>>k;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				vis[i][j]=1;
		for(int i=1;i<=k;i++)
		{
			int x,y;
			cin>>x>>y;
			vis[x][y]=0;
		}
		dfs(1,1);
		cout<<ans;
	}
}
