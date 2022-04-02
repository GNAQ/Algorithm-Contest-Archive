#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

ll dp[1 << 21];
int n, ai[400010];
ll shown[22], cost[22][22];

void init()
{
	memset(dp, 0x3f, sizeof(dp));
	dp[0] = 0;
	for (int i=1;i<=n;i++)
	{
		shown[ai[i]]++;
		for (int j=1;j<=20;j++) if (ai[i] != j)
			cost[ai[i]][j] += shown[j];
	}
}

int main()
{
	scanf("%d", &n);
	for (int i=1;i<=n;i++)
		scanf("%d", ai+i);
	
	init();
	int ansbit = 0;
	for (int i=1;i<=20;i++) 
		ansbit |= ((shown[i] > 0) << (i - 1));
	
	for (int i=1;i<(1<<20);i++) if ((i | ansbit) == ansbit)
	{
		for (int j=1;j<=20;j++) if ( (1 << (j - 1)) & i)
		{
			int i2 = i ^ (1 << (j - 1));
			long long tcost = 0;
			for (int k=1;k<=20;k++) if (((1 << (k - 1)) & i2) == 0)
				tcost += cost[j][k];
			dp[i] = min(dp[i], dp[i2] + tcost);
		}
	}
	
	printf("%lld\n", dp[ansbit]);
	return 0;
}