#include<bits/stdc++.h>

using namespace std;

long double dp[52][52][2510];

int main()
{
	int T;
	cin>>T;
	while(T--)
	{
		int m,n;
		cin>>m>>n;
		for(int i=0;i<=m;i++)
		{
			for(int j=0;j<=n;j++)
			{
				for(int k=0;k<=m*n;k++)
				{
					dp[i][j][k]=100000;
				}
			}
		}
		for(int i=max(m,n);i<=m*n;i++)
		{
			dp[m][n][i]=0;
		}
		for(int i=m;i>=0;i--)
		{
			for(int j=n;j>=0;j--)
			{
				if(i==m&&j==n) continue;
				for(int k=m*n-1;k>=0;k--)
				{
					if(i==m)
					{
						dp[i][j][k]=dp[i][j+1][k+1]*i*(n-j)
							       +dp[i][j][k+1]*(i*j-k);
					}
					else if(j==n)
					{
						dp[i][j][k]=dp[i+1][j][k+1]*(m-i)*j
							       +dp[i][j][k+1]*(i*j-k);
					}
					else 
					{
						dp[i][j][k]=dp[i+1][j][k+1]*(m-i)*j
					           	   +dp[i][j+1][k+1]*i*(n-j)
							       +dp[i+1][j+1][k+1]*(m-i)*(n-j)
							       +dp[i][j][k+1]*(i*j-k);
					}
					dp[i][j][k]/=(m*n-k);
					dp[i][j][k]++;
				}
			}
		}
		cout<<setprecision(11)<<fixed
			<<dp[0][0][0]<<'\n';
	}
}