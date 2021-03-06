#include<iostream>
#include<cstdio>
#include<queue>
#include<map>
using namespace std;
const int MAXN=1e3+100;
const int MAXM=4e6+100;
const int mod=1e9+7;
struct E{
	int to;
	int next;
}e[MAXM];
queue<int>line;
int n,m,tot,sum,num[MAXN][MAXN],dx[10],dy[10],in_d[MAXM],out_d[MAXM],head[MAXM],h[MAXM],dp[MAXM][5],ans;
int id(int x,int y)
{
	return (x-1)*m+y;
}
void add_edge(int u,int v)
{
	e[++tot].next=head[u];
	e[tot].to=v;
	head[u]=tot;
}
int main()
{
	cin>>n>>m;
	dx[1]=dx[2]=0;
	dx[3]=1;dx[4]=-1;
	dy[1]=-1;dy[2]=1;
	dy[3]=dy[4]=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%d",&num[i][j]);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			int now=id(i,j),tx,ty,to;
			for(int k=1;k<=4;k++)
			{
				tx=i+dx[k];
				ty=j+dy[k];
				if(tx<1||tx>n||ty<1||ty>m)
					continue;
				if((num[i][j]+1)!=num[tx][ty])
					continue;
				to=id(tx,ty);
				in_d[to]++;
				out_d[now]++;
				add_edge(now,id(tx,ty));
			}
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(!in_d[id(i,j)])
			{
				dp[id(i,j)][1]=1; 
				line.push(id(i,j));
			}
	while(!line.empty())
	{
		int x=line.front();
		line.pop();
		if(!out_d[x]) 
		{
			ans+=dp[x][4];
			ans%=mod;
		}
		for(int i=head[x];i;i=e[i].next)
		{
			int to=e[i].to;
			dp[to][2]+=dp[x][1];
			dp[to][2]%=mod;
			dp[to][3]+=dp[x][2];
			dp[to][3]%=mod;
			dp[to][4]+=dp[x][3];
			dp[to][4]%=mod;
			dp[to][4]+=dp[x][4];
			dp[to][4]%=mod;
			in_d[to]--;
			if(!in_d[to])
				line.push(to);
		}
	}
	cout<<ans;
}
