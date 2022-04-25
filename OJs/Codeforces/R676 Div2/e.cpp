#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int n, ai[200010];
ll dp[200010][3][3][2];

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
	readx(n);
	for (int i=1;i<=n;i++)
		readx(ai[i]);
	
	if (n == 1)
	{
		printf("%d\n", ai[1]);
		return 0;
	}
	if (n == 2)
	{
		printf("%d\n", -ai[1]-ai[2]);
		return 0;
	}
	
	for (int i=0;i<3;i++)
		for (int j=0;j<3;j++)
			dp[0][i][j][0] = dp[0][i][j][1] = -1e16;
	dp[0][0][0][0] = 0;
	for (int i=1;i<=n;i++)
		for (int j=0;j<3;j++)
			for (int k=0;k<3;k++)
			{
				if (i % 2)
				{
					dp[i][j][k][0] = max(dp[i - 1][(j + 2) % 3][k][0] + ai[i], dp[i - 1][j][(k + 2) % 3][0] - ai[i]);
					dp[i][j][k][1] = max(dp[i - 1][(j + 2) % 3][k][1] + ai[i], dp[i - 1][j][(k + 2) % 3][1] - ai[i]);
					dp[i][j][k][1] = max(dp[i][j][k][1], dp[i - 1][j][(k + 2) % 3][0] - ai[i]);
				}
				else
				{
					dp[i][j][k][0] = max(dp[i - 1][(j + 2) % 3][k][0] + ai[i], dp[i - 1][j][(k + 2) % 3][0] - ai[i]);
					dp[i][j][k][1] = max(dp[i - 1][(j + 2) % 3][k][1] + ai[i], dp[i - 1][j][(k + 2) % 3][1] - ai[i]);
					dp[i][j][k][1] = max(dp[i][j][k][1], dp[i - 1][(j + 2) % 3][k][0] + ai[i]);
				}
			}
	
	printf("%lld\n", dp[n][2 - n % 3][((n % 3) - (2 - n % 3) + 6) % 3][1]);
}