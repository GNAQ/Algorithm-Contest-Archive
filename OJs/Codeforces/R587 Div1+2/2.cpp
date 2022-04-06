#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

bool sw[10010];
int n;
int ai[10010], bi[10010];

int main()
{
	// 30000 periods
	string stmp;
	cin >> n >> stmp;
	for (int i=1;i<=n;i++)
		cin >> ai[i] >> bi[i];
	for (int i=0;i<n;i++)
		sw[i+1] = stmp[i] - '0';
	
	int ans = 0;
	for (int i=1;i<=60000;i++)
	{
		int cnt = 0;
		for (int j=1;j<=n;j++)
			cnt += sw[j];
		ans = max(ans, cnt);
		for (int j=1;j<=n;j++)
			if (i == bi[j])
			{
				sw[j] ^= 1;
				bi[j] += ai[j];
			}
	}
	printf("%d\n", ans);
	return 0;
}