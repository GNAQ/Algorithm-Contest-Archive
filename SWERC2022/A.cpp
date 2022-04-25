#include <bits/stdc++.h>
using namespace std;

int b[20];

void Solve()
{
	memset(b,-1,sizeof(b));
	int n;
	scanf("%d", &n);
	int bi, di;
	for (int i=1;i<=n;i++)
	{
		scanf("%d%d", &bi, &di);
		b[di] = max(b[di], bi);
	}
	int ans = 0;
	for (int i=1;i<=10;i++)
	{
		if (b[i] == -1)
		{
			puts("MOREPROBLEMS");
			return;
		}
		ans += b[i];
	}
	
	printf("%d\n", ans);
	return;
}


int main()
{
	int t; scanf("%d", &t);
	for (int i=1;i<=t;i++)
	{
		Solve();
	}
	
	
}