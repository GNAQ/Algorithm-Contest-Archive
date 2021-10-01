#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
const ll MAXN = 1e7 + 100;
ll n, q, mx_pos = -1;
ll dat[MAXN], dp[MAXN];
int main()
{
	cin >> n >> q;
	for (int i = 1; i <= 1e6 + 2000; i++)
		dp[i] = 1e18;
	for (int i = 1; i <= n; i++)
		scanf("%lld", &dp[i]);
		
	vector<int> pot;
	for (ll i = 1; i <= n; i++)
	{
		int flag = -1;
		for (ll j = 1; j <= n; j++)
			if (dp[i] * j > dp[j] * i)
			{
				flag = 1;
				break;
			}
		if (flag == -1)
		{
			mx_pos = i;
			pot.push_back(i);
		}
	}
	for (ll i = 1; i <= n; i++)
		for (ll j = n + 1; j <= 1e6 + 1000; j++)
			dp[j] = min(dp[j], dp[j - i] + dp[i]);
	

	for (ll i = 1; i <= q; i++)
	{
		ll k;
		scanf("%lld", &k);
		if (k <= 1e6 + 1000)
			printf("%lld\n", dp[k]);
		else
		{
			ll ans = 1e18;
			for (auto mp: pot)
			{
				ll delt = (k - 1e6 - 1) / mp + 1;
				// printf("%lld\n", delt * dp[mp] + dp[k - delt * mp]);
				ans = min(ans, delt * dp[mp] + dp[k - delt * mp]);
			}
			printf("%lld\n", ans);
		}
	}
}
