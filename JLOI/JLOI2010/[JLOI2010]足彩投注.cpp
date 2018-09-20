#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<iterator>
#include<cstdlib>
#include<map>
#include<vector>
#include<set>
#include<queue>
#define ll long long
using namespace std;

int n,N,M,U;
long double p[10010][5]={0},q[10010][5]={0},a[10010][5]={0};
long double dp[10010][20][20]={0};

inline void readx(int& x)
{
	x=0; int k=1; register char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

inline bool cmp1(long double a,long double b) { return a>b; }

int main()
{
	readx(n); readx(N); readx(M); readx(U);
	for (int i=1;i<=n;i++)
	{
		for (int j=0;j<=2;j++) scanf("%Lf",&p[i][j]);
		for (int j=0;j<=2;j++) scanf("%Lf",&q[i][j]);
		for (int j=0;j<=2;j++) a[i][j]=p[i][j]/q[i][j];
		sort(a[i],a[i]+3,cmp1);
	}
	
	dp[0][0][0]=1.0;
	for (int i=1;i<=n;i++)
		for (int j=0;j<=19;j++)
			for (int k=0;k<=9;k++) if (pow(2,j)*pow(3,k)<=(long double)U+1e-6)
			{
				dp[i][j][k]=dp[i-1][j][k]*a[i][0];
				if (j) dp[i][j][k]=max(dp[i][j][k],dp[i-1][j-1][k]*(a[i][0]+a[i][1]));
				if (k) dp[i][j][k]=max(dp[i][j][k],dp[i-1][j][k-1]*(a[i][0]+a[i][1]+a[i][2]));
			}
	long double ans=0.0;
	for (int j=0;j<=19;j++)
		for (int k=0;k<=9;k++)
			ans=max(ans,dp[n][j][k]);
	printf("%.3Lf\n",log(ans/N*M));
	return 0;
}