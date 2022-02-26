#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int n;
ll a[8080], dp[8010][8010];
stack<pair<ll, ll>> stk;

const ll INF = 1e16;

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
		readx(a[i]);
	
	memset(dp, 0x3f, sizeof(dp));
	for (int i=1;i<=n;i++) // parts of array
	{
		while (!stk.empty()) stk.pop();
		for (int j=i;j<=n;j++)
		{
			ll minv = (j == 1 ? 0 : dp[i-1][j-1]);
			while ((!stk.empty()) && a[stk.top().first] < a[j])
			{
				minv = min(minv, stk.top().second);
				stk.pop();
			}
			if (!stk.empty())
				dp[i][j] = min(dp[i][j], dp[i][stk.top().first]);
			// else
			// 	minv = 0;
			
			// printf("I = %d, J = %d, minv = %lld\n", i, j, minv);
			dp[i][j] = min(dp[i][j], minv + a[j]);
			stk.push({j, minv});
		}
		
		// for (int j=1;j<=n;j++)
		// 	printf("%lld%c", dp[i][j], " \n"[j==n]);
	}
	
	sort(a+1, a+n+1);
	for (int i=n-1;i>=1;i--)
		a[i] += a[i+1];
	
	for (int i=1;i<=n;i++)
		printf("%lld %lld\n", dp[i][n], a[n+1-i]);
}