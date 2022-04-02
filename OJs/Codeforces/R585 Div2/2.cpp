#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

ll dp[200010];
ll ev,od, anse, anso;
ll ai[200010];

int main()
{
	int n; scanf("%d", &n);
	for (int i=1;i<=n;i++)
		scanf("%lld", ai + i);
	
	for (int i=1;i<=n;i++)
	{
		if (ai[i] < 0)
		{
			swap(ev, od);
			od++;
		}
		else
		{
			ev++;
		}
		anse += ev;
		anso += od;
	}
	
	printf("%lld %lld\n", anso, anse);
	return 0;
}