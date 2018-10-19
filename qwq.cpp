#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<iterator>
#include<cstdlib>
#include<queue>
#include<vector>
#include<set>
#include<map>
#define ll long long
using namespace std;

int n,G[20][20],m;

int dp[10010][20][20];
bool can[20];

template<typename int_t>
void readx(int_t& x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

void Floyd()
{
	for (int k=1;k<=n;k++)
		for (int i=1;i<=n;i++)
			for (int j=1;j<=n;j++) G[i][j]=min(G[i][j],G[i][k]+G[k][j]);
}

void Decod(int val)
{
	for (int i=1;i<=n;i++) can[i]=0;
	for (int i=1;i<=n;i++) can[i]=val&(1<<(i-1));
}


int main()
{
	readx(n); readx(m); int fx,tx,wx;
	memset(G,0x3f,sizeof G); for (int i=1;i<=n;i++) G[i][i]=0;
	for (int i=1;i<=m;i++) 
	{
		readx(fx); readx(tx); readx(wx);
		if (G[fx][tx]>wx) G[fx][tx]=G[tx][fx]=wx;
	}
	// Floyd();
	
	int lim=(1<<n); int onum;
	memset(dp,0x3f,sizeof dp); dp[0][0][0]=0;
	for (int sta=1;sta<lim;sta++)
	{
		Decod(sta); onum=0;
		for (int i=1;i<=n;i++) onum+=can[i];
		if (onum==1)
		{
			for (int i=1;i<=n;i++) if (can[i])
			{
				dp[sta][i][1]=0;
				break;
			}
			continue;
		} 
		
		for (int i=1;i<=n;i++) if (can[i])
		{
			for (int w=2;w<=onum;w++)
			{
				for (int j=1;j<=n;j++) if (can[j] && j!=i)
				{
					int pre=sta^(1<<(j-1));
					dp[sta][i][w]=min(dp[sta][i][w],dp[pre][j][w-1]+G[j][i]*w);
				}
			}
		}
	}
	
	int ans=2*1e9;
	for (int i=1;i<=n;i++)
		for (int j=2;j<=n;j++) ans=min(ans,dp[lim-1][i][j]);
	printf("%d\n",ans);
	return 0;
}