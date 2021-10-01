#include<iostream>
#include<cstdio>
using namespace std;
const int MAXN=210;
const int inf=1e9;
char ch[MAXN];
int bouns[MAXN][MAXN],point[MAXN][MAXN];
int dp[MAXN][MAXN][2];
int main()
{
	int T;cin>>T;
	while(T--)
	{
		int n,m,k;
		scanf("%d%d%d",&n,&m,&k);
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
			{
				scanf("%d%s",&point[i][j],ch+1);
				if(ch[1]=='Y') bouns[i][j]=1;
				else bouns[i][j]=0;
			}		
		for(int i=0;i<=m;i++)
			for(int j=0;j<=k;j++)
				dp[i][j][0]=dp[i][j][1]=-inf;
		dp[0][0][0]=0;
		for(int i=1;i<=m;i++)
		{
			int cost=0,val=0,need=0,white=0;
			for(int j=0;j<=k;j++)
			{
				dp[i][j][0]=dp[i-1][j][0];
				dp[i][j][1]=dp[i-1][j][1];
			}				
			for(int j=n;j>=1;j--)
			{
				if(bouns[j][i]==1)
				{
					need=1;
					white=0;
				}
				else {
					need=0;
					cost++;
					white=1;
				}
				val+=point[j][i];
				for(int kk=k;kk>=cost;kk--)
				{
					if(need&&(kk==k))
						dp[i][kk][1]=max(dp[i][kk][1],dp[i-1][kk-cost][1]+val);
					else {
						dp[i][kk][1]=max(dp[i][kk][1],dp[i-1][kk-cost][1]+val);
						if(white)  dp[i][kk][1]=max(dp[i][kk][1],max(dp[i-1][kk-cost][0],dp[i-1][kk-cost][1])+val);
						if(!white) dp[i][kk][0]=max(dp[i][kk][0],dp[i-1][kk-cost][0]+val);
					}
				}	
			}
		}
		int res=-1e9;
		for(int i=0;i<=k;i++)
			res=max(res,max(dp[m][i][0],dp[m][i][1]));
		printf("%d\n",res);
	}
}

