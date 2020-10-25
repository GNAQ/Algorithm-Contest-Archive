#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<vector>
typedef long long ll;
using namespace std;

int n,m,K;
int a[80][80];
ll ans;
int dp[80][80][80];
int dp2[80][80];

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}


int main()
{
	readx(n); readx(m); readx(K);
	int lim=m/2;
	
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			readx(a[i][j]);
	
	for (int i=1;i<=n;i++)
		for (int j=0;j<=lim;j++)
			for (int k=0;k<K;k++)
				dp[i][j][k]= -1 * 1e9;
	
	// dp[行数][选择个数][余数]
	
	for (int i=0;i<=n;i++)
		dp[i][0][0]=0;
	
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=m;j++) // 当前考虑 (i,j)
		{
			for (int k=lim;k>0;k--) // 选择个数
			{
				for (int l=0;l<K;l++) // 余数
				{
					int l1=(l+a[i][j])%K;
					dp[i][k][l1]=max(dp[i][k][l1], dp[i][k-1][l]+a[i][j]);
				}
			}
		}
	}
	
	for (int i=0;i<=n;i++)
		for (int j=0;j<K;j++) dp2[i][j]= -1 * 1e9;
	dp2[0][0]=0;
	// dp2[行][余数]
	for (int i=1;i<=n;i++)
	{
		for (int j=0;j<K;j++) // 当前余数
		{
			for (int k=0;k<=lim;k++) // 该行选几个
			{
				for (int l=0;l<K;l++) // 该行选了之后行之和的余数
				{
					int j2=(j+l)%K;
					dp2[i][j2]=max(dp2[i][j2], dp2[i-1][j]+dp[i][k][l]);
				}
			}
		}
	}
	
	printf("%d\n", max(0,dp2[n][0]));
	return 0;
}