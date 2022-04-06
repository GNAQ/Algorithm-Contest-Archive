#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int n, ai[100010], sol[100010];

int main()
{
	scanf("%d", &n);
	for (int i=1;i<=n;i++)
		scanf("%d", &ai[i]);
	
	sort(ai+1, ai+n+1);
	int ans = 0;
	for (int i=1;i<=n;i++) if (!sol[i])
	{
		sol[i] = ++ans;
		for (int j=i+1;j<=n;j++)
		{
			if (!(ai[j] % ai[i]))
				sol[j] = sol[i];
		}
	}
	
	printf("%d\n", ans);
	return 0;
}