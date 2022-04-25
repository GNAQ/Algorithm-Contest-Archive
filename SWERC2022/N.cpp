#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int n, a[2010][2010];
ll ans;

int rc[2010], lc[2010];

struct ni
{
	int x, y, val;
	bool operator < (const ni &b) const
		{ return this->val > b.val; }
}b[1510 * 1510];

int main()
{
	scanf("%d", &n);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
		{
			scanf("%d", &a[i][j]);
			b[(i - 1) * n + j] = (ni){i, j, a[i][j]};
		}
	
	sort(b + 1, b + n * n + 1);
	
	ll X = 1LL * n * n * (n - 1) * (n - 1) / 4, Y = 0; 
	for (int i=1;i<=n*n;i++)
	{
		Y += rc[b[i].x] * lc[b[i].y];
		rc[b[i].x]++;
		lc[b[i].y]++;
	}
	
	printf("%lld\n", 2 * X - Y);
	return 0;
}